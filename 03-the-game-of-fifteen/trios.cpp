// ¿Cuántos tríos del 1 al 9 suman 15? ¿Y son justo las líneas del cuadrado mágico?
#include <cstdio>
#include "quince.h"

int main() {
  int total = 0, enLinea = 0;
  for (int a = 1; a <= 9; a++)
    for (int b = a + 1; b <= 9; b++)
      for (int c = b + 1; c <= 9; c++) {
        if (a + b + c != 15) continue;
        total++;
        int t[9] = {0};
        t[casilla(a)] = t[casilla(b)] = t[casilla(c)] = TU;
        int linea = tresEnRaya(t, TU);
        enLinea += linea;
        printf("%d + %d + %d = 15   %s\n", a, b, c,
               linea ? "\033[32m✓ es una línea\033[0m" : "\033[31m✗\033[0m");
      }
  printf("\033[35m%d tríos · %d líneas del tres en raya\033[0m\n", total, enLinea);
}
