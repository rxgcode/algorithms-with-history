// La rutina de Kaprekar con 2, 3, 5 y 6 cifras: ¿hay un único número final?
// Uso: ./otras 3   → a dónde caen todos los números de 3 cifras
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

long long paso(long long n, int c) {
    std::string s = std::to_string(n); s = std::string(c - s.size(), '0') + s;
    std::string mayor(s), menor(s);
    std::sort(mayor.begin(), mayor.end(), std::greater<char>());
    std::sort(menor.begin(), menor.end());
    return std::stoll(mayor) - std::stoll(menor);
}

int main(int argc, char** argv) {
    int c = argc > 1 ? atoi(argv[1]) : 3;
    long long a = 1, b = 1; for (int i = 1; i < c; i++) a *= 10; b = a * 10 - 1;
    std::map<std::vector<long long>, int> finales;   // ciclo final (empezando por su menor) → cuántos caen
    for (long long n = a; n <= b; n++) {
        if (paso(n, c) == 0) continue;
        std::vector<long long> camino; long long x = n;
        while (std::find(camino.begin(), camino.end(), x) == camino.end()) { camino.push_back(x); x = paso(x, c); }
        std::vector<long long> ciclo(std::find(camino.begin(), camino.end(), x), camino.end());
        std::rotate(ciclo.begin(), std::min_element(ciclo.begin(), ciclo.end()), ciclo.end());
        finales[ciclo]++;
    }
    printf("%d cifras: %zu final%s\n", c, finales.size(), finales.size() == 1 ? "" : "es");
    for (auto& [ciclo, k] : finales) {
        printf("  ");
        for (size_t i = 0; i < ciclo.size(); i++) printf("%0*lld%s", c, ciclo[i], i + 1 < ciclo.size() ? " → " : "");
        printf(ciclo.size() == 1 ? "  (fijo)" : " → …  (ciclo)");
        printf("  · %d números\n", k);
    }
    return 0;
}
