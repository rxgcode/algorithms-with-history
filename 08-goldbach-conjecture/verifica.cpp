// Comprueba Goldbach para todos los pares de 4 a N con una criba de Eratóstenes.
// Para cada par busca un primo p tal que n - p también sea primo; si alguno fallara, lo diría.
// Uso: ./verifica 100000000
#include <cstdio>
#include <cstdlib>
#include <vector>

#define VERDE "\x1b[1;32m"
#define VIOLETA "\x1b[1;35m"
#define FIN "\x1b[0m"

const char* miles(long long v, char* out) {
    char t[32]; int n = snprintf(t, sizeof t, "%lld", v), j = 0;
    for (int i = 0; i < n; i++) { if (i && (n - i) % 3 == 0) out[j++] = ' '; out[j++] = t[i]; }
    out[j] = 0; return out;
}

int main(int argc, char** argv) {
    long long N = argc > 1 ? atoll(argv[1]) : 100000000;
    std::vector<bool> compuesto(N + 1, false);              // criba de Eratóstenes
    compuesto[0] = compuesto[1] = true;
    for (long long i = 2; i * i <= N; i++)
        if (!compuesto[i]) for (long long j = i * i; j <= N; j += i) compuesto[j] = true;
    std::vector<int> primos;
    for (long long i = 2; i <= N; i++) if (!compuesto[i]) primos.push_back((int)i);

    long long revisados = 0;
    for (long long n = 4; n <= N; n += 2) {
        bool ok = false;                                   // ¿hay un primo p tal que n - p también es primo?
        for (int p : primos) { if (p > n / 2) break; if (!compuesto[n - p]) { ok = true; break; } }
        if (!ok) { printf("¡%lld no es suma de dos primos!\n", n); return 1; }
        revisados++;
    }
    char a[32], b[32];
    printf("pares del 4 al %s: %s\n", miles(N, a), miles(revisados, b));
    printf(VERDE "todos son suma de dos primos ✓" FIN "\n");
    return 0;
}
