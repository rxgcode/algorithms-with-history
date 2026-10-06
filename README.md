# Algorithms with History · Algoritmos con historia

Código real de la serie de shorts **"Algoritmos con historia"** del canal **regCode** en YouTube.
Cada vídeo resuelve un problema clásico en C++ y lo ejecuta de verdad: los resultados que ves en pantalla salen de este código.

| # | Problema | Carpeta | Vídeo |
|---|---|---|---|
| 1 | El misterio del 196 (números de Lychrel) | [`01-the-196-mystery`](01-the-196-mystery) | [Ver short](https://youtube.com/shorts/MyjG1hMHh3I) |
| 2 | La persona famosa (*celebrity problem*) | [`02-the-celebrity-problem`](02-the-celebrity-problem) | [Ver short](https://youtube.com/shorts/AN2vD0AXbfQ) |
| 3 | El juego de sumar quince | [`03-the-game-of-fifteen`](03-the-game-of-fifteen) | _próximamente_ |
| 4 | π con dardos (Monte Carlo) | [`04-pi-with-darts`](04-pi-with-darts) | [Ver short](https://youtube.com/shorts/zHRd2ayBlxk) |

## Compilar y ejecutar

Necesitas un compilador de C++17 (`g++` o `clang++`) y `make`.

```bash
make                     # compila todo
cd 04-pi-with-darts
./dardos 1000000         # π con un millón de dardos
```

Cada `push` compila todo y comprueba en GitHub Actions que los resultados coinciden con los que se ven en los vídeos.

## Fuentes

Los problemas 1–4 están inspirados en ejercicios de un libro de ejercicios de programación en C++ de profesores de la Universidad Complutense de Madrid; los datos históricos se citan en el README de cada carpeta. Los enunciados están reescritos con nuestras palabras.

## Licencia

[MIT](LICENSE) · regCode
