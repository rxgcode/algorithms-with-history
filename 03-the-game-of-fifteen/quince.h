// El juego de sumar quince, programado SIN tablero.
// El cuadrado mágico sirve para que una persona vea que es el tres en raya;
// al programa le basta con los números.
#pragma once

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

// Minimax: +10 si gana la CPU, -10 si ganas tú (antes = mejor), 0 empate.
int score(int owner[10], int turn, int depth) {
  if (wins(owner, CPU)) return 10 - depth;
  if (wins(owner, HUMAN)) return depth - 10;
  int best = (turn == CPU) ? -100 : 100;
  bool moved = false;
  for (int n = 1; n <= 9; n++) {
    if (owner[n] != NOBODY) continue;
    moved = true;
    owner[n] = turn;
    int value = score(owner, turn == CPU ? HUMAN : CPU, depth + 1);
    owner[n] = NOBODY;
    if (turn == CPU ? value > best : value < best) best = value;
  }
  return moved ? best : 0;
}

// El algoritmo: prueba cada número libre y se queda con el mejor.
// Si empatan, prefiere el 5, luego los pares (las esquinas del cuadrado).
const int ORDER[9] = { 5, 2, 4, 6, 8, 1, 3, 7, 9 };
int bestMove(int owner[10]) {
  int best = -100, chosen = -1;
  for (int n : ORDER) {
    if (owner[n] != NOBODY) continue;
    owner[n] = CPU;                     // pruebo
    int value = score(owner, HUMAN, 1); // futuro
    owner[n] = NOBODY;                  // deshago
    if (value > best) { best = value; chosen = n; }
  }
  return chosen;
}
