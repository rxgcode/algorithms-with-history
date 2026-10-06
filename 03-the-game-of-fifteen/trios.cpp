// ¿Cuántos tríos del 1 al 9 suman 15? ¿Y son justo las líneas del cuadrado mágico?
// (La parte "humana" del truco: el juego no lo necesita, pero aquí se comprueba.)
#include <cstdio>

const int CUADRADO[9] = { 4, 9, 2,
                          3, 5, 7,
                          8, 1, 6 };

const int LINEAS[8][3] = { {0,1,2}, {3,4,5}, {6,7,8},     // filas
                           {0,3,6}, {1,4,7}, {2,5,8},     // columnas
                           {0,4,8}, {2,4,6} };            // diagonales

int casilla(int n) {
  for (int c = 0; c < 9; c++)
    if (CUADRADO[c] == n) return c;
  return -1;
}

int esLinea(int a, int b, int c) {
  for (auto& l : LINEAS) {
    int x = casilla(a), y = casilla(b), z = casilla(c), hits = 0;
    for (int k = 0; k < 3; k++) hits += (l[k] == x) + (l[k] == y) + (l[k] == z);
    if (hits == 3) return 1;
  }
  return 0;
}

int main() {
  int total = 0, enLinea = 0;
  for (int a = 1; a <= 9; a++)
    for (int b = a + 1; b <= 9; b++)
      for (int c = b + 1; c <= 9; c++) {
        if (a + b + c != 15) continue;
        total++;
        int linea = esLinea(a, b, c);
        enLinea += linea;
        printf("%d + %d + %d = 15   %s\n", a, b, c,
               linea ? "\033[32m✓ es una línea\033[0m" : "\033[31m✗\033[0m");
      }
  printf("\033[35m%d tríos · %d líneas del tres en raya\033[0m\n", total, enLinea);
}
