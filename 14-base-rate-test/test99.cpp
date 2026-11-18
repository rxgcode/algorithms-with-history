// Das positivo en un test que acierta el 99 %... ¿qué probabilidad hay de que estés enfermo?
// (teorema de Bayes / falacia de la tasa base; D. Eddy, 1982; G. Gigerenzer, conteos naturales)
// Simula 1 000 000 de personas: 1 de cada 1 000 tiene la enfermedad; el test detecta al 99 % de los
// enfermos (sensibilidad) y da positivo al 1 % de los sanos (falsos positivos; especificidad 99 %).
// Uso: ./test99        → un test a cada persona: cuántos positivos y cuántos están enfermos de verdad
//      ./test99 2      → reto: solo cuenta a quien da positivo 2 veces seguidas (tests independientes)
//      ./test99 1 100  → si ya tienes síntomas y 1 de cada 100 personas como tú lo tiene (probabilidad previa)
// Compilar: g++ -std=c++17 -O2 -o test99 test99.cpp
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <random>

#define VERDE "\x1b[1;32m"
#define ROJO "\x1b[1;31m"
#define FIN "\x1b[0m"

// 10980 → "10 980" (miles con espacio, como en el vídeo)
static const char* miles(long long v, char* buf) {
    char tmp[32]; int n = snprintf(tmp, sizeof tmp, "%lld", v), j = 0;
    for (int i = 0; i < n; i++) { if (i > 0 && (n - i) % 3 == 0) buf[j++] = ' '; buf[j++] = tmp[i]; }
    buf[j] = 0; return buf;
}

int main(int argc, char** argv) {
    int tests = argc > 1 ? atoi(argv[1]) : 1;
    int unoDeCada = argc > 2 ? atoi(argv[2]) : 1000;   // la enfermedad la tiene 1 de cada ... (por defecto, 1 000)
    const long long PERSONAS = 1000000;
    const int MAX_TESTS = 3;
    const double PREVALENCIA = 1.0 / unoDeCada, SENSIBILIDAD = 0.99, FALSO_POSITIVO = 0.01;
    std::mt19937_64 rng(1982);                       // semilla fija: siempre el mismo resultado
    // Un número al azar en [0, 1). No usamos std::uniform_real_distribution porque cada biblioteca la
    // implementa distinto (macOS y Linux darían otros resultados con la misma semilla): los 53 bits
    // altos del generador, multiplicados por 2^-53, dan lo mismo en cualquier compilador.
    auto azar = [&]() { return (rng() >> 11) * 0x1.0p-53; };

    if (tests < 1 || tests > MAX_TESTS) { fprintf(stderr, "tests: de 1 a %d\n", MAX_TESTS); return 1; }
    long long enfermos = 0, positivos = 0, positivosEnfermos = 0;
    for (long long i = 0; i < PERSONAS; i++) {
        bool enfermo = azar() < PREVALENCIA;
        enfermos += enfermo;
        bool positivo = true;                        // positivo en TODOS los tests que se le hacen
        for (int t = 0; t < MAX_TESTS; t++) {        // siempre se tiran los mismos dados: la misma gente con 1, 2 o 3 tests
            bool sale = azar() < (enfermo ? SENSIBILIDAD : FALSO_POSITIVO);
            if (t < tests && !sale) positivo = false;
        }
        if (positivo) { positivos++; positivosEnfermos += enfermo; }
    }
    char a[32], b[32], c[32];
    printf("%s personas · %s enfermas\n", miles(PERSONAS, a), miles(enfermos, b));
    printf("sensibilidad 99 %% · falsos positivos 1 %%\n\n");
    if (tests == 1) printf("dieron positivo:     %7s\n", miles(positivos, c));
    else            printf("positivo %d veces:    %7s\n", tests, miles(positivos, c));
    printf("enfermos de verdad:  " ROJO "%7s" FIN "\n", miles(positivosEnfermos, a));
    double pct = 100.0 * positivosEnfermos / positivos;
    snprintf(b, sizeof b, "%.1f", pct); for (char* p = b; *p; p++) if (*p == '.') *p = ',';   // coma decimal
    printf(tests == 1 ? "→ solo el " VERDE "%s %%" FIN " de los positivos\n" : "→ el " VERDE "%s %%" FIN " de los positivos\n", b);
    return 0;
}
