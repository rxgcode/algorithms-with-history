// Juega a sumar quince contra la CPU, que nunca pierde (minimax).
// Uso: ./quince        (empiezas tú)
//      ./quince cpu    (empieza la CPU)
#include <cstdio>
#include <cstring>
#include "quince.h"

int dueno[10];

void mostrar() {
  printf("   ");
  for (int n = 1; n <= 9; n++)
    printf(dueno[n] == TU ? "\033[35m%d\033[0m " : dueno[n] == CPU ? "\033[32m%d\033[0m " : "\033[90m%d\033[0m ", n);
  printf("\n");
}

void trio(int jugador) {
  for (int a = 1; a <= 9; a++)
    for (int b = a + 1; b <= 9; b++) {
      int c = 15 - a - b;
      if (c > b && c <= 9 && dueno[a] == jugador && dueno[b] == jugador && dueno[c] == jugador) {
        printf("%d + %d + %d = 15\n", a, b, c);
        return;
      }
    }
}

int main(int argc, char* argv[]) {
  int turno = (argc > 1 && !strcmp(argv[1], "cpu")) ? CPU : TU;
  for (int jugada = 0; jugada < 9; jugada++) {
    if (turno == CPU) {
      int n = mejorJugada(dueno);
      dueno[n] = CPU;
      printf("\033[32mCPU: %d\033[0m", n);
      mostrar();
    } else {
      int n;
      printf("tu número: ");
      fflush(stdout);
      if (scanf("%d", &n) != 1) return 0;
      if (n < 1 || n > 9 || dueno[n] != NADIE) { printf("ese no vale\n"); jugada--; continue; }
      dueno[n] = TU;
      if (gana(dueno, TU) || jugada == 8) { printf("      "); mostrar(); }
    }
    if (gana(dueno, turno)) {
      printf(turno == CPU ? "\033[32mGana la CPU: " : "\033[35mGanas tú: ");
      trio(turno);
      printf("\033[0m");
      return 0;
    }
    turno = (turno == CPU) ? TU : CPU;
  }
  printf("\033[33mEmpate.\033[0m\n");
}
