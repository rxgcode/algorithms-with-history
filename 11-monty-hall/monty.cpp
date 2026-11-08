// El problema de Monty Hall (S. Selvin, 1975; M. vos Savant, 1990): tres puertas, un auto, dos cabras.
// Eliges una; el presentador, que sabe dónde está el auto, abre otra con cabra. ¿Te quedas o cambias?
// Uso: ./monty 1000000            → un millón de partidas: cuántas gana quedarse y cuántas cambiar
//      ./monty 1000000 100        → con 100 puertas (el presentador abre 98 con cabra)
//      ./monty 1000000 3 --azar   → el presentador NO sabe: abre al azar (se descartan las partidas en que sale el auto)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>

#define VERDE "\x1b[1;32m"
#define VIOLETA "\x1b[1;35m"
#define FIN "\x1b[0m"

int main(int argc, char** argv) {
    long long n = argc > 1 ? atoll(argv[1]) : 1000000;
    int puertas = argc > 2 ? atoi(argv[2]) : 3;
    bool azar = argc > 3 && strcmp(argv[3], "--azar") == 0;
    std::mt19937_64 rng(1990);                       // semilla fija: siempre el mismo resultado
    std::uniform_int_distribution<int> dado(0, puertas - 1);
    long long jugadas = 0, ganaQuedarse = 0, ganaCambiar = 0;
    for (long long i = 0; i < n; i++) {
        int auto_ = dado(rng), elegida = dado(rng);
        if (azar) {
            // el presentador abre una de las otras puertas al azar; si aparece el auto, la partida no cuenta
            int abre; do abre = dado(rng); while (abre == elegida);
            if (abre == auto_) continue;
            int otra; do otra = dado(rng); while (otra == elegida || otra == abre);   // (con 3 puertas, la única que queda)
            jugadas++;
            if (elegida == auto_) ganaQuedarse++;
            if (otra == auto_) ganaCambiar++;
        } else {
            // el presentador sabe: abre todas menos tu puerta y otra (que es el auto, si no lo elegiste tú)
            jugadas++;
            if (elegida == auto_) ganaQuedarse++;
            else ganaCambiar++;
        }
    }
    printf("%lld partidas · %d puertas%s\n", jugadas, puertas, azar ? " · el presentador abre al azar" : "");
    printf("  quedarse: " VIOLETA "%lld" FIN " victorias (%.1f %%)\n", ganaQuedarse, 100.0 * ganaQuedarse / jugadas);
    printf("  cambiar:  " VERDE "%lld" FIN " victorias (%.1f %%)\n", ganaCambiar, 100.0 * ganaCambiar / jugadas);
    return 0;
}
