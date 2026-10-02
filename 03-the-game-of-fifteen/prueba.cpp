// Prueba exhaustiva: la IA juega contra TODAS las partidas posibles.
#include <cstdio>
#include "quince.h"

long long partidas = 0, ganaIA = 0, empates = 0, ganasTu = 0;

void jugar(int t[9], int turno, int libres) {
  int ganador = tresEnRaya(t, IA) ? IA : tresEnRaya(t, TU) ? TU : 0;
  if (ganador || libres == 0) {
    partidas++;
    if (ganador == IA) ganaIA++; else if (ganador == TU) ganasTu++; else empates++;
    return;
  }
  if (turno == IA) {                     // la IA siempre elige su mejor jugada
    int c = mejorJugada(t);
    t[c] = IA; jugar(t, TU, libres - 1); t[c] = LIBRE;
  } else {                               // tú pruebas todos los números libres
    for (int c = 0; c < 9; c++) {
      if (t[c] != LIBRE) continue;
      t[c] = TU; jugar(t, IA, libres - 1); t[c] = LIBRE;
    }
  }
}

int main() {
  int t[9] = {0};
  jugar(t, TU, 9);                       // empiezas tú
  jugar(t, IA, 9);                       // empieza la IA
  printf("%lld partidas posibles\n", partidas);
  printf("\033[32mgana la IA: %lld\033[0m\n", ganaIA);
  printf("\033[33mempates:    %lld\033[0m\n", empates);
  printf("%sganas tú:   %lld\033[0m\n", ganasTu ? "\033[31m" : "\033[35m", ganasTu);
}
