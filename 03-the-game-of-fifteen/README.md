# 03 · El juego de sumar quince

**El juego:** por turnos, cada jugador elige un número del 1 al 9 sin repetir. Gana quien junte **tres números que sumen 15**.

Parece un juego de cuentas… pero es **el tres en raya disfrazado**. En el cuadrado mágico Lo Shu cada fila, columna y diagonal suma 15:

```
4 9 2
3 5 7
8 1 6
```

Hay exactamente 8 tríos del 1 al 9 que suman 15, y son justo las 8 líneas del tablero. Elegir un número es marcar su casilla.

## Archivos

| Archivo | Qué hace |
|---|---|
| `quince.h` | La idea: el cuadrado mágico, `casilla(n)`, y el algoritmo que nunca pierde (minimax) sobre el tablero traducido. |
| `trios.cpp` | Fuerza bruta: lista los tríos que suman 15 y comprueba que cada uno es una línea. |
| `quince.cpp` | Partida interactiva contra el algoritmo (`./quince`, o `./quince algoritmo` para que empiece él). |
| `prueba.cpp` | El algoritmo juega contra todas las respuestas posibles del rival. |

## Ejecutar

```bash
make
./trios      # 8 tríos · 8 líneas del tres en raya
./prueba     # 613 partidas: gana el algoritmo 450, empates 163, ganas tú 0
./quince     # juega tú
```

## Historia

- **Lo Shu:** según la leyenda china, salió del río Luo en el caparazón de una tortuga; el cuadrado 3×3 ya se conocía hacia el 190 a. C.
- **1967** · John A. Michon, "The Game of JAM: An Isomorph of Tic-Tac-Toe", *American Journal of Psychology* 80(1).
- **1969** · Herbert A. Simon, *The Sciences of the Artificial* (MIT Press), lo llama "Number Scrabble": resolver un problema es representarlo de forma que la solución se vuelva transparente.
- **1978** · Martin Gardner, *Aha! Insight* ("¡Ajá! Inspiración"), lo divulga como "Fifteen".

Ejercicio inspirado en el 4.14 "El juego de sumar quince" del libro de ejercicios de C++ de profesores de la UCM.
