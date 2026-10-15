# 08 · La conjetura de Goldbach

**El enunciado:** todo número par mayor que 2 es la suma de dos números primos. 28 = 5 + 23 = 11 + 17.
Christian Goldbach se lo planteó a Leonhard Euler en 1742 y nadie lo ha podido demostrar.

```cpp
for (long long p = 2; p <= n / 2; p++)
    if (primo(p) && primo(n - p))
        formas++;   // n = p + (n − p)
```

## Archivos

| Archivo | Qué hace |
|---|---|
| `goldbach.cpp` | Todas las formas de escribir un par como p + q (`--cuenta`: solo cuántas). |
| `verifica.cpp` | Comprueba todos los pares de 4 a N con una criba de Eratóstenes. |
| `cometa.cpp` | Imprime `n formas` para cada par hasta N: el «cometa de Goldbach». |

## Ejecutar

```bash
make
./goldbach 28                 # 28 = 5 + 23 · 28 = 11 + 17 · 2 formas
./goldbach 1000 --cuenta      # 28 formas
./verifica 100000000          # 49 999 999 pares: todos son suma de dos primos (< 1 s)
./cometa 20000 > cometa.txt   # datos para graficar
```

## Historia

- **7 de junio de 1742:** carta de Goldbach a Euler. **30 de junio:** Euler responde que es «ein ganz gewisses Theorema, ungeachtet ich dasselbe nicht demonstriren kann» (un teorema completamente cierto, aunque no lo puede demostrar).
- **2013:** Harald Helfgott presenta una demostración de la versión débil (todo impar mayor que 5 es suma de tres primos), [arXiv:1312.7748](https://arxiv.org/abs/1312.7748).
- **2014:** T. Oliveira e Silva, S. Herzog y S. Pardi publican la verificación hasta 4 × 10¹⁸ (*Mathematics of Computation* 83).
- La versión con dos primos sigue abierta.

## Vídeo

▶️ [La conjetura de Goldbach: una apuesta de 1742 que nadie ha podido demostrar](https://youtube.com/shorts/Yg6Hu66eWj0)
