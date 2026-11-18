// El error del Patriot (Dhahran, 25/02/1991): 0,1 guardado en un registro de 24 bits.
// Fuente: GAO/IMTEC-92-26, apéndice II. Compilar: g++ -O2 -o patriot patriot.cpp
#include <cstdio>
#include <cstdint>
#include <cstdlib>

int main(int argc, char** argv) {
    // 0,1 en binario: 0,0001100110011001100110011001100... (no termina)
    // El registro es de 24 bits; en el cálculo del Patriot quedan 23 después de la coma
    // (0,00011001100110011001100, como en el análisis del GAO). Lo demás se corta.
    const int BITS = 23;
    uint32_t guardado = (uint32_t)(0.1 * (1u << BITS));   // corta, no redondea
    double tenth = (double)guardado / (1u << BITS);
    double error_tick = 0.1 - tenth;

    printf("0,1 en binario:  0,");
    for (int i = 1; i <= BITS; i++) printf("%d", (guardado >> (BITS - i)) & 1);
    printf("...\n");
    printf("lo que se guarda: %.10f\n", tenth);
    printf("error por décima: %.10f s\n\n", error_tick);

    const double SCUD = 1676.0;   // m/s, unas 5 veces la velocidad del sonido (GAO: Mach 5)
    int horas[] = {1, 8, 20, 48, 72, 100};
    printf("horas   error (s)   el Scud avanza (m)\n");
    for (int h : horas) {
        long long decimas = (long long)h * 3600 * 10;
        double err = decimas * error_tick;
        printf("%5d   %9.4f   %8.0f\n", h, err, err * SCUD);
    }
    if (argc > 1) {   // reto: ¿cuántas horas para un error de X segundos?
        double objetivo = atof(argv[1]);
        double horas_obj = objetivo / error_tick / 10 / 3600;
        printf("\nerror de %.2f s tras %.1f horas encendido\n", objetivo, horas_obj);
    }
}
