// El juego de sumar quince = tres en raya disfrazado.
// La idea: cada número del 1 al 9 tiene su casilla en el cuadrado mágico (Lo Shu).
#pragma once

const int CUADRADO[9] = { 4, 9, 2,
                          3, 5, 7,
                          8, 1, 6 };

const int LINEAS[8][3] = { {0,1,2}, {3,4,5}, {6,7,8},     // filas
                           {0,3,6}, {1,4,7}, {2,5,8},     // columnas
                           {0,4,8}, {2,4,6} };            // diagonales

enum { LIBRE = 0, TU = 1, ALGORITMO = 2 };

// casilla(5) → 4 (el centro)
int casilla(int n) {
  for (int c = 0; c < 9; c++)
    if (CUADRADO[c] == n) return c;
  return -1;
}

// ¿Tiene este jugador tres en raya? (= tres números que suman 15)
int tresEnRaya(const int t[9], int jugador) {
  for (auto& l : LINEAS)
    if (t[l[0]] == jugador && t[l[1]] == jugador && t[l[2]] == jugador) return 1;
  return 0;
}

// Minimax: +10 si gana el algoritmo, -10 si ganas tú (antes = mejor), 0 empate.
int valor(int t[9], int turno, int prof) {
  if (tresEnRaya(t, ALGORITMO)) return 10 - prof;
  if (tresEnRaya(t, TU)) return prof - 10;
  int mejor = (turno == ALGORITMO) ? -100 : 100, hay = 0;
  for (int c = 0; c < 9; c++) {
    if (t[c] != LIBRE) continue;
    hay = 1;
    t[c] = turno;
    int v = valor(t, turno == ALGORITMO ? TU : ALGORITMO, prof + 1);
    t[c] = LIBRE;
    if (turno == ALGORITMO ? v > mejor : v < mejor) mejor = v;
  }
  return hay ? mejor : 0;
}

// La mejor casilla para el algoritmo. Si empatan, prefiere el 5, luego pares (esquinas).
const int ORDEN[9] = { 5, 2, 4, 6, 8, 1, 3, 7, 9 };
int mejorJugada(int t[9]) {
  int mejor = -100, elegido = -1;
  for (int n : ORDEN) {
    int c = casilla(n);
    if (t[c] != LIBRE) continue;
    t[c] = ALGORITMO;
    int v = valor(t, TU, 1);
    t[c] = LIBRE;
    if (v > mejor) { mejor = v; elegido = c; }
  }
  return elegido;
}
