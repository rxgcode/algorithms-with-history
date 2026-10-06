// ¿Cuántos tríos del 1 al 9 suman 15? ¿Son justo los de TRIPLES? ¿Y las líneas del cuadrado mágico?
// (La parte "humana" del truco: el juego no necesita el cuadrado, pero aquí se comprueba.)
#include <cstdio>
#include "quince.h"

const int SQUARE[9] = { 4, 9, 2,
                        3, 5, 7,
                        8, 1, 6 };

const int LINES[8][3] = { {0,1,2}, {3,4,5}, {6,7,8},     // filas
                          {0,3,6}, {1,4,7}, {2,5,8},     // columnas
                          {0,4,8}, {2,4,6} };            // diagonales

bool same(int a, int b, int c, const int t[3]) {
  int hits = 0;
  for (int k = 0; k < 3; k++) hits += (t[k] == a) + (t[k] == b) + (t[k] == c);
  return hits == 3;
}

int main() {
  int total = 0, inLine = 0, inTable = 0;
  for (int a = 1; a <= 9; a++)
    for (int b = a + 1; b <= 9; b++)
      for (int c = b + 1; c <= 9; c++) {
        if (a + b + c != 15) continue;
        total++;
        bool line = false, table = false;
        for (auto& l : LINES) {
          int t[3] = { SQUARE[l[0]], SQUARE[l[1]], SQUARE[l[2]] };
          if (same(a, b, c, t)) line = true;
        }
        for (auto& t : TRIPLES) if (same(a, b, c, t)) table = true;
        inLine += line; inTable += table;
        printf("%d + %d + %d = 15   %s\n", a, b, c,
               line && table ? "\033[32m✓ es una línea\033[0m" : "\033[31m✗\033[0m");
      }
  printf("\033[35m%d tríos · %d líneas del tres en raya · %d en TRIPLES\033[0m\n", total, inLine, inTable);
}
