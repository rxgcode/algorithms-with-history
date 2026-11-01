// Prueba la rutina de Kaprekar con TODOS los números de 4 cifras (1000–9999, siempre con 4 cifras).
// Uso: ./verifica              → cuántos llegan a 6174 y en cuántos pasos
//      ./verifica 1900 2026    → solo ese rango (p. ej. años de nacimiento)
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <string>

#define VERDE "\x1b[1;32m"
#define VIOLETA "\x1b[1;35m"
#define FIN "\x1b[0m"

int paso(int n) {
    char s[5]; snprintf(s, sizeof s, "%04d", n);
    std::string mayor(s), menor(s);
    std::sort(mayor.begin(), mayor.end(), std::greater<char>());
    std::sort(menor.begin(), menor.end());
    return std::stoi(mayor) - std::stoi(menor);
}

int main(int argc, char** argv) {
    int a = argc > 2 ? atoi(argv[1]) : 1000, b = argc > 2 ? atoi(argv[2]) : 9999;
    int cuenta[9] = {0}, total = 0, repetidos = 0, llegan = 0, peor = -1;
    std::string con7;
    for (int n = a; n <= b; n++) {
        if (paso(n) == 0) { repetidos++; continue; }   // 1111, 2222… : todas las cifras iguales
        total++;
        int x = n, k = 0;
        while (x != 6174 && k < 8) { x = paso(x); k++; }
        if (x == 6174) llegan++;
        cuenta[k]++;
        if (k > peor) { peor = k; con7.clear(); }
        if (k == peor && con7.size() < 60) con7 += (con7.empty() ? "" : " ") + std::to_string(n);
    }
    printf("números del %d al %d: %d (sin contar %d con todas las cifras iguales)\n", a, b, total, repetidos);
    for (int k = 0; k <= 7; k++) printf("  %d paso%s: " VIOLETA "%5d" FIN "\n", k, k == 1 ? " " : "s", cuenta[k]);
    printf(VERDE "llegan a 6174: %d de %d ✓" FIN "\n", llegan, total);
    printf("el que más tarda: %d pasos (%s%s)\n", peor, con7.c_str(), cuenta[peor] > 12 ? " …" : "");
    return 0;
}
