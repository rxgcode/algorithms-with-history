// Conjetura de Goldbach (carta a Euler, 1742): todo número par mayor que 2 es la suma de dos primos.
// Uso: ./goldbach 28        → todas las formas de escribir 28 como p + q (p ≤ q, ambos primos)
//      ./goldbach 28 --cuenta → solo cuántas formas hay
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define VERDE "\x1b[1;32m"
#define VIOLETA "\x1b[1;35m"
#define FIN "\x1b[0m"

bool primo(long long n) {
    if (n < 2) return false;
    for (long long d = 2; d * d <= n; d++)
        if (n % d == 0) return false;
    return true;
}

int main(int argc, char** argv) {
    long long n = argc > 1 ? atoll(argv[1]) : 28;
    bool solo = argc > 2 && strcmp(argv[2], "--cuenta") == 0;
    if (n <= 2 || n % 2) { printf("n debe ser par y mayor que 2\n"); return 1; }
    int formas = 0;
    for (long long p = 2; p <= n / 2; p++)
        if (primo(p) && primo(n - p)) {
            formas++;
            if (!solo) printf("%lld = " VIOLETA "%lld" FIN " + " VIOLETA "%lld" FIN "\n", n, p, n - p);
        }
    printf(VERDE "%d forma%s" FIN "\n", formas, formas == 1 ? "" : "s");
    return 0;
}
