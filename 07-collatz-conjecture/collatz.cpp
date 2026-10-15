// Conjetura de Collatz (3n + 1): si n es par, divídelo entre 2; si es impar, multiplícalo por 3 y súmale 1.
// ¿Llega siempre a 1? Nadie lo ha demostrado (Lothar Collatz, 1937).
// Uso: ./collatz 6     → muestra el camino completo, los pasos y el máximo
//      ./collatz 27    → camino resumido si es largo
//      ./collatz 27 --lista → todos los valores, uno por línea (para graficar)
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

#define VERDE "\x1b[1;32m"
#define VIOLETA "\x1b[1;35m"
#define GRIS "\x1b[90m"
#define FIN "\x1b[0m"

// El algoritmo, tal cual se ve en el vídeo.
int pasos(long long n) {
    int k = 0;
    while (n != 1) {
        if (n % 2 == 0) n = n / 2;       // par: la mitad
        else            n = 3 * n + 1;   // impar: el triple más uno
        k++;
    }
    return k;
}

int main(int argc, char** argv) {
    long long n = argc > 1 ? atoll(argv[1]) : 27;
    if (n < 1) { printf("n debe ser positivo\n"); return 1; }
    std::vector<long long> camino{n};
    for (long long x = n; x != 1;) { x = x % 2 == 0 ? x / 2 : 3 * x + 1; camino.push_back(x); }
    if (argc > 2 && strcmp(argv[2], "--lista") == 0) { for (long long v : camino) printf("%lld\n", v); return 0; }
    long long maximo = n; size_t en = 0;
    for (size_t i = 0; i < camino.size(); i++) if (camino[i] > maximo) { maximo = camino[i]; en = i; }

    // Camino: completo si es corto; si no, el principio y el final.
    const size_t corto = 12;
    int col = 0;
    for (size_t i = 0; i < camino.size(); i++) {
        if (camino.size() > corto && i == 6) { printf(GRIS " → …" FIN); col += 4; i = camino.size() - 4; }
        char buf[32]; int len = snprintf(buf, sizeof buf, "%lld", camino[i]);
        if (i > 0) { if (col + len + 3 > 34) { printf("\n"); col = 0; } printf(GRIS " → " FIN); col += 3; }
        printf("%s%s" FIN, camino[i] == 1 ? VERDE : "", buf); col += len;
    }
    printf("\n");
    printf(VERDE "%d pasos" FIN " · máximo " VIOLETA "%lld" FIN, pasos(n), maximo);
    if (camino.size() > corto) printf(GRIS " (paso %zu)" FIN, en);
    printf("\n");
    return 0;
}
