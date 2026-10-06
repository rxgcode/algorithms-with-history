// El juego de sumar quince, programado SIN tablero.
// El cuadrado mágico sirve para que una persona vea que es el tres en raya;
// al programa le basta con los números.
#pragma once
#include <algorithm>

enum Player { NOBODY = 0, HUMAN = 1, CPU = 2 };

// owner[n] = quién tiene el número n (1..9): NOBODY, HUMAN o CPU.

// Los 8 tríos que suman 15 (= las 8 líneas del tres en raya; trios.cpp lo comprueba).
const int TRIPLES[8][3] = {
  {2,7,6}, {9,5,1}, {4,3,8}, {2,9,4},
  {7,5,3}, {6,1,8}, {2,5,8}, {4,5,6} };

// ¿Los tres números del trío son de este jugador?
bool ownsTriple(const int triple[3], const int owner[10], int player) {
  return owner[triple[0]] == player &&
         owner[triple[1]] == player &&
         owner[triple[2]] == player;
}

// ¿Alguien juntó tres que sumen 15?
bool wins(const int owner[10], int player) {
  for (auto& triple : TRIPLES)
    if (ownsTriple(triple, owner, player)) return true;
  return false;
}

// ¿cuánto vale la partida para quien juega?
// positivo = gana · 0 = empate · negativo = pierde
// (ambos juegan perfecto; ganar antes vale más)
int score(int owner[10], int me, int rival,
          int depth) {
  if (wins(owner, rival)) return depth - 10;
  int best = -100;
  for (int n = 1; n <= 9; n++) {
    if (owner[n] != NOBODY) continue;
    owner[n] = me;                       // pruebo
    // le toca al rival: su ganancia es mi pérdida
    int value = -score(owner, rival, me, depth + 1);
    owner[n] = NOBODY;                   // deshago
    best = std::max(best, value);
  }
  return best == -100 ? 0 : best;        // empate
}

// El algoritmo: prueba cada número libre y se queda con el de mejor score.
// Si empatan, prefiere el 5, luego los pares (las esquinas del cuadrado).
const int ORDER[9] = { 5, 2, 4, 6, 8, 1, 3, 7, 9 };
int bestMove(int owner[10]) {
  int best = -100, chosen = 0;
  for (int n : ORDER) {
    if (owner[n] != NOBODY) continue;
    owner[n] = CPU;
    int value = -score(owner, HUMAN, CPU, 1);
    owner[n] = NOBODY;
    if (value > best) { best = value; chosen = n; }
  }
  return chosen;
}
