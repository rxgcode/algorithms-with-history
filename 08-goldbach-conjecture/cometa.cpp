// El cometa de Goldbach: cuántas formas hay de escribir cada par n como p + q (p ≤ q, ambos primos).
// Imprime "n formas" para todos los pares de 4 a N (para graficar).
// Uso: ./cometa 20000
#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int argc, char** argv) {
    long long N = argc > 1 ? atoll(argv[1]) : 20000;
    std::vector<bool> compuesto(N + 1, false);              // criba de Eratóstenes
    compuesto[0] = compuesto[1] = true;
    for (long long i = 2; i * i <= N; i++)
        if (!compuesto[i]) for (long long j = i * i; j <= N; j += i) compuesto[j] = true;
    for (long long n = 4; n <= N; n += 2) {
        int formas = 0;
        for (long long p = 2; p <= n / 2; p++)
            if (!compuesto[p] && !compuesto[n - p]) formas++;
        printf("%lld %d\n", n, formas);
    }
    return 0;
}
