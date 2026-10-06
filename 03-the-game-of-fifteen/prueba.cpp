// Prueba exhaustiva: la CPU juega contra TODAS las partidas posibles.
#include <cstdio>
#include "quince.h"

long long partidas = 0, ganaCPU = 0, empates = 0, ganasTu = 0;

void jugar(int dueno[10], int turno, int libres) {
  int ganador = gana(dueno, CPU) ? CPU : gana(dueno, TU) ? TU : NADIE;
  if (ganador || libres == 0) {
    partidas++;
    if (ganador == CPU) ganaCPU++; else if (ganador == TU) ganasTu++; else empates++;
    return;
  }
  if (turno == CPU) {                    // la CPU siempre elige su mejor jugada
    int n = mejorJugada(dueno);
    dueno[n] = CPU; jugar(dueno, TU, libres - 1); dueno[n] = NADIE;
  } else {                               // tú pruebas todos los números libres
    for (int n = 1; n <= 9; n++) {
      if (dueno[n] != NADIE) continue;
      dueno[n] = TU; jugar(dueno, CPU, libres - 1); dueno[n] = NADIE;
    }
  }
}

int main() {
  int dueno[10] = {0};
  jugar(dueno, TU, 9);                   // empiezas tú
  jugar(dueno, CPU, 9);                  // empieza la CPU
  printf("%lld partidas posibles\n", partidas);
  printf("\033[32mgana la CPU: %lld\033[0m\n", ganaCPU);
  printf("\033[33mempates:     %lld\033[0m\n", empates);
  printf("%sganas tú:    %lld\033[0m\n", ganasTu ? "\033[31m" : "\033[35m", ganasTu);
}
