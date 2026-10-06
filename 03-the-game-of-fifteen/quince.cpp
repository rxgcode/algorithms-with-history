// Juega a sumar quince contra un algoritmo que nunca pierde (minimax).
// Uso: ./quince        (empiezas tú)
//      ./quince algoritmo     (empieza el algoritmo)
#include <cstdio>
#include <cstring>
#include "quince.h"

int t[9];

void mostrar() {
  printf("   ");
  for (int n = 1; n <= 9; n++) {
    int q = t[casilla(n)];
    printf(q == TU ? "\033[35m%d\033[0m " : q == ALGORITMO ? "\033[32m%d\033[0m " : "\033[90m%d\033[0m ", n);
  }
  printf("\n");
}

void trio(int jugador) {
  for (auto& l : LINEAS)
    if (t[l[0]] == jugador && t[l[1]] == jugador && t[l[2]] == jugador) {
      int a = CUADRADO[l[0]], b = CUADRADO[l[1]], c = CUADRADO[l[2]], x;
      if (a > b) { x = a; a = b; b = x; }
      if (b > c) { x = b; b = c; c = x; }
      if (a > b) { x = a; a = b; b = x; }
      printf("%d + %d + %d = 15\n", a, b, c);
      return;
    }
}

int main(int argc, char* argv[]) {
  int turno = (argc > 1 && !strcmp(argv[1], "algoritmo")) ? ALGORITMO : TU;
  for (int jugada = 0; jugada < 9; jugada++) {
    if (turno == ALGORITMO) {
      int c = mejorJugada(t);
      t[c] = ALGORITMO;
      printf("\033[32malgoritmo: %d\033[0m", CUADRADO[c]);
      mostrar();
    } else {
      int n;
      printf("tu número: ");
      fflush(stdout);
      if (scanf("%d", &n) != 1) return 0;
      if (n < 1 || n > 9 || t[casilla(n)] != LIBRE) { printf("ese no vale\n"); jugada--; continue; }
      t[casilla(n)] = TU;
      if (tresEnRaya(t, TU) || jugada == 8) { printf("            "); mostrar(); }
    }
    if (tresEnRaya(t, turno)) {
      printf(turno == ALGORITMO ? "\033[32mGana el algoritmo: " : "\033[35mGanas tú: ");
      trio(turno);
      printf("\033[0m");
      return 0;
    }
    turno = (turno == ALGORITMO) ? TU : ALGORITMO;
  }
  printf("\033[33mEmpate.\033[0m\n");
}
