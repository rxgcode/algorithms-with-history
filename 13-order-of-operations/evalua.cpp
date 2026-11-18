// 12 ÷ 2 × 3: ¿18 o 2? Un evaluador mínimo de expresiones que arma el árbol y muestra los pasos.
// Regla actual: × y ÷ tienen la misma prioridad y se agrupan de izquierda a derecha (igual que C++ y Python).
// Con --implicita, la multiplicación sin signo, 2(3), va antes que × y ÷ (la convención de algunos libros y calculadoras).
// Compilar: g++ -std=c++17 -O2 -o evalua evalua.cpp
// Uso:      ./evalua "12 / 2 * 3"        ./evalua --implicita "12 / 2(3)"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>

struct Nodo {
    char op;                       // '+', '-', '*', '/', '.' (multiplicación sin signo) o 0 si es un número
    double val;
    std::unique_ptr<Nodo> izq, der;
};
using P = std::unique_ptr<Nodo>;

static const char* s;              // cursor sobre la expresión
static bool implicita = false;     // ¿2(3) va antes que × y ÷?
static int paso = 0;

static void blancos() { while (*s == ' ') s++; }
static bool ve(char c) { blancos(); return *s == c; }
static char toma() { blancos(); return *s++; }

static P suma();
static P hoja(double v) { return P(new Nodo{0, v, nullptr, nullptr}); }
static P une(char op, P a, P b) { return P(new Nodo{op, 0, std::move(a), std::move(b)}); }

static P numero() {                // un número o un paréntesis
    if (ve('(')) { toma(); P e = suma(); toma(); return e; }
    blancos();
    char* fin; double v = std::strtod(s, &fin); s = fin;
    return hoja(v);
}

static P pegado() {                // 2(3): multiplicación sin signo
    P izq = numero();
    while (implicita && ve('(')) izq = une('.', std::move(izq), numero());
    return izq;
}

// multiplicar y dividir: misma prioridad,
// de izquierda a derecha
static P termino() {
    P izq = pegado();
    while (ve('*') || ve('/') || (!implicita && ve('('))) {
        char op = ve('(') ? '.' : toma();
        izq = une(op, std::move(izq), pegado());
    }
    return izq;
}

static P suma() {
    P izq = termino();
    while (ve('+') || ve('-')) { char op = toma(); izq = une(op, std::move(izq), termino()); }
    return izq;
}

static std::string num(double v) { char b[32]; std::snprintf(b, sizeof b, "%g", v); return b; }

static std::string texto(const Nodo* n) {      // el árbol escrito con todos sus paréntesis
    if (!n->op) return num(n->val);
    if (n->op == '.') return "(" + texto(n->izq.get()) + "(" + texto(n->der.get()) + "))";
    return "(" + texto(n->izq.get()) + " " + n->op + " " + texto(n->der.get()) + ")";
}

static double calcula(const Nodo* n) {         // de abajo hacia arriba: primero los hijos
    if (!n->op) return n->val;
    double a = calcula(n->izq.get()), b = calcula(n->der.get()), r = 0;
    switch (n->op) {
        case '+': r = a + b; break;
        case '-': r = a - b; break;
        case '*': case '.': r = a * b; break;
        case '/': r = a / b; break;
    }
    char op = n->op == '.' ? '*' : n->op;
    std::printf("paso %d: %s %c %s = %s\n", ++paso, num(a).c_str(), op, num(b).c_str(), num(r).c_str());
    return r;
}

int main(int argc, char** argv) {
    int k = 1;
    if (argc > 1 && !std::strcmp(argv[1], "--implicita")) { implicita = true; k++; }
    if (k >= argc) { std::fprintf(stderr, "uso: %s [--implicita] \"12 / 2 * 3\"\n", argv[0]); return 1; }
    s = argv[k];
    P arbol = suma();
    std::printf("árbol:  %s\n", texto(arbol.get()).c_str());
    double r = calcula(arbol.get());
    std::printf("resultado: %s\n", num(r).c_str());
}
