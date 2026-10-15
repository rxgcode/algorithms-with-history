// Comprueba la conjetura de Collatz para todos los números de 1 a N y busca el que tarda más pasos.
// Si algún número no llegara nunca a 1, este programa no terminaría: por eso un programa no puede demostrarla.
// Uso: ./verifica 10000000
#include <cstdio>
#include <cstdlib>

#define VERDE "\x1b[1;32m"
#define VIOLETA "\x1b[1;35m"
#define FIN "\x1b[0m"

int pasos(long long n) {
    int k = 0;
    while (n != 1) {
        if (n % 2 == 0) n = n / 2;
        else            n = 3 * n + 1;
        k++;
    }
    return k;
}

// Miles con espacio: 10000000 → "10 000 000"
const char* miles(long long v, char* out) {
    char t[32]; int n = snprintf(t, sizeof t, "%lld", v), j = 0;
    for (int i = 0; i < n; i++) { if (i && (n - i) % 3 == 0) out[j++] = ' '; out[j++] = t[i]; }
    out[j] = 0; return out;
}

int main(int argc, char** argv) {
    long long N = argc > 1 ? atoll(argv[1]) : 10000000;
    long long record = 1; int maxPasos = 0;
    for (long long n = 1; n <= N; n++) {
        int k = pasos(n);
        if (k > maxPasos) { maxPasos = k; record = n; }
    }
    char a[32], b[32];
    printf("del 1 al %s:\n", miles(N, a));
    printf(VERDE "todos llegan a 1 ✓" FIN "\n");
    printf("el más largo: " VIOLETA "%s" FIN "\n", miles(record, b));
    printf("con " VIOLETA "%d pasos" FIN "\n", maxPasos);
    return 0;
}
