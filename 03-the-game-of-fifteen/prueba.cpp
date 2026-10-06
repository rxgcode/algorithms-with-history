// Prueba exhaustiva: la CPU juega contra TODAS las partidas posibles.
#include <cstdio>
#include "quince.h"

long long games = 0, cpuWins = 0, draws = 0, humanWins = 0;

void play(int owner[10], int turn, int free) {
  int winner = wins(owner, CPU) ? CPU : wins(owner, HUMAN) ? HUMAN : NOBODY;
  if (winner || free == 0) {
    games++;
    if (winner == CPU) cpuWins++; else if (winner == HUMAN) humanWins++; else draws++;
    return;
  }
  if (turn == CPU) {                     // la CPU siempre elige su mejor jugada
    int n = bestMove(owner);
    owner[n] = CPU; play(owner, HUMAN, free - 1); owner[n] = NOBODY;
  } else {                               // tú pruebas todos los números libres
    for (int n = 1; n <= 9; n++) {
      if (owner[n] != NOBODY) continue;
      owner[n] = HUMAN; play(owner, CPU, free - 1); owner[n] = NOBODY;
    }
  }
}

int main() {
  int owner[10] = {0};
  play(owner, HUMAN, 9);                 // empiezas tú
  play(owner, CPU, 9);                   // empieza la CPU
  printf("%lld partidas posibles\n", games);
  printf("\033[32mgana la CPU: %lld\033[0m\n", cpuWins);
  printf("\033[33mempates:     %lld\033[0m\n", draws);
  printf("%sganas tú:    %lld\033[0m\n", humanWins ? "\033[31m" : "\033[35m", humanWins);
}
