// Rutina de Kaprekar (D. R. Kaprekar, 1949): ordena las cifras de mayor a menor, réstale
// el mismo número con las cifras de menor a mayor y repite. Con 4 cifras siempre cae en 6174.
// Uso: ./kaprekar 1998              → los pasos hasta 6174
//      ./kaprekar 2111 --sin-ceros  → el error típico: tratar 0999 como 999 (de 3 cifras)
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>

#define VERDE "\x1b[1;32m"
#define ROJO "\x1b[1;31m"
#define VIOLETA "\x1b[1;35m"
#define FIN "\x1b[0m"

// Un paso de la rutina. Con `ceros`, el número siempre tiene 4 cifras (999 → "0999").
int paso(int n, bool ceros, std::string& mayor, std::string& menor) {
    std::string s = std::to_string(n);
    if (ceros) s = std::string(4 - s.size(), '0') + s;
    mayor = menor = s;
    std::sort(mayor.begin(), mayor.end(), std::greater<char>());
    std::sort(menor.begin(), menor.end());
    return std::stoi(mayor) - std::stoi(menor);
}

int main(int argc, char** argv) {
    int n = argc > 1 ? atoi(argv[1]) : 1998;
    bool ceros = !(argc > 2 && strcmp(argv[2], "--sin-ceros") == 0);
    if (n < 1000 || n > 9999) { printf("n debe tener 4 cifras\n"); return 1; }
    std::string mayor, menor;
    for (int pasos = 1; pasos <= 10; pasos++) {
        int r = paso(n, ceros, mayor, menor);
        char rs[8]; snprintf(rs, sizeof rs, ceros ? "%04d" : "%d", r);
        printf("%s − %s = %s%s" FIN "\n", mayor.c_str(), menor.c_str(), r == 6174 ? VERDE : r == 0 ? ROJO : VIOLETA, rs);
        if (r == 6174) { printf(VERDE "6174 en %d paso%s" FIN "\n", pasos, pasos == 1 ? "" : "s"); return 0; }
        if (r == 0) { printf(ROJO "atascado en 0" FIN "\n"); return 0; }
        n = r;
    }
    return 0;
}
