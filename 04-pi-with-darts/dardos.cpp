// π con dardos (Monte Carlo): lanza N dardos al azar en el cuadrado [-1,1]x[-1,1]
// y cuenta cuántos caen dentro de la diana de radio 1. π ≈ 4 · dentro / total.
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <random>
#include <string>

// 1000000 -> "1 000 000"
std::string miles(long long n) {
    std::string s = std::to_string(n), r;
    for (int i = 0; i < (int)s.size(); i++) { if (i && (s.size() - i) % 3 == 0) r += ' '; r += s[i]; }
    return r;
}

int main(int argc, char** argv) {
    long long total = argc > 1 ? atoll(argv[1]) : 1000000;
    std::mt19937_64 gen(196);                        // semilla fija: resultados reproducibles
    std::uniform_real_distribution<double> azar(-1.0, 1.0);

    long long dentro = 0, siguiente = 100;
    for (long long i = 1; i <= total; i++) {
        double x = azar(gen), y = azar(gen);
        if (x * x + y * y <= 1.0) dentro++;          // ¿cayó en la diana?
        if (i == siguiente || i == total) {
            double pi = 4.0 * dentro / i;
            int ok = 0;                               // cifras correctas de π
            char a[32], b[32];
            snprintf(a, sizeof a, "%.6f", pi); snprintf(b, sizeof b, "%.6f", M_PI);
            while (a[ok] && a[ok] == b[ok]) ok++;
            printf("%13s dardos  π ≈ \033[32m%.*s\033[0m\033[90m%s\033[0m\n", miles(i).c_str(), ok, a, a + ok);
            siguiente *= 10;
        }
    }
}
