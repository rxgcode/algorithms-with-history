// El juego de sumar quince, programado SIN tablero.
// El cuadrado mágico sirve para que una persona vea que es el tres en raya;
// a la computadora le basta con los números: solo busca tres que sumen 15.
#pragma once

enum Jugador { NADIE = 0, TU = 1, CPU = 2 };

// dueno[n] = de quién es el número n (1..9): NADIE, TU o CPU.

// ¿alguien juntó tres que sumen 15?
int gana(const int dueno[10], int jugador) {
  for (int a = 1; a <= 9; a++)
    for (int b = a + 1; b <= 9; b++) {
      int c = 15 - a - b;   // el tercero
      if (c > b && c <= 9 &&
          dueno[a] == jugador &&
          dueno[b] == jugador &&
          dueno[c] == jugador) return 1;
    }
  return 0;
}

// Minimax: +10 si gana la CPU, -10 si ganas tú (antes = mejor), 0 empate.
int valor(int dueno[10], int turno, int prof) {
  if (gana(dueno, CPU)) return 10 - prof;
  if (gana(dueno, TU)) return prof - 10;
  int mejor = (turno == CPU) ? -100 : 100, hay = 0;
  for (int n = 1; n <= 9; n++) {
    if (dueno[n] != NADIE) continue;
    hay = 1;
    dueno[n] = turno;
    int v = valor(dueno, turno == CPU ? TU : CPU, prof + 1);
    dueno[n] = NADIE;
    if (turno == CPU ? v > mejor : v < mejor) mejor = v;
  }
  return hay ? mejor : 0;
}

// El algoritmo: prueba cada número libre y se queda con el mejor.
// Si empatan, prefiere el 5, luego los pares (las esquinas del cuadrado).
const int ORDEN[9] = { 5, 2, 4, 6, 8, 1, 3, 7, 9 };
int mejorJugada(int dueno[10]) {
  int mejor = -100, elegido = -1;
  for (int n : ORDEN) {
    if (dueno[n] != NADIE) continue;
    dueno[n] = CPU;              // pruebo n
    int v = valor(dueno, TU, 1); // el futuro
    dueno[n] = NADIE;            // deshago
    if (v > mejor) { mejor = v; elegido = n; }
  }
  return elegido;
}
