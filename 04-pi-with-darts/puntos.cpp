// Exporta los primeros N dardos del mismo generador que dardos.cpp (para dibujarlos o analizarlos).
#include <cstdio>
#include <cstdlib>
#include <random>
int main(int argc, char** argv) {
    int n = argc > 1 ? atoi(argv[1]) : 100;
    std::mt19937_64 gen(196);
    std::uniform_real_distribution<double> azar(-1.0, 1.0);
    printf("[");
    for (int i = 0; i < n; i++) { double x = azar(gen), y = azar(gen); printf("%s[%.4f,%.4f]", i ? "," : "", x, y); }
    printf("]\n");
}
