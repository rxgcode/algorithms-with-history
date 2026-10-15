# 07 · La conjetura de Collatz (3n + 1)

**La regla:** toma un número. Si es par, divídelo entre 2; si es impar, multiplícalo por 3 y súmale 1. Repite.
Todos los números que se han probado terminan en 1… pero **nadie ha demostrado que pase siempre**.

```cpp
int pasos(long long n) {
    int k = 0;
    while (n != 1) {
        if (n % 2 == 0) n = n / 2;       // par: la mitad
        else            n = 3 * n + 1;   // impar: el triple más uno
        k++;
    }
    return k;
}
```

## Archivos

| Archivo | Qué hace |
|---|---|
| `collatz.cpp` | Muestra el camino de un número, sus pasos y su máximo. `--lista` imprime todos los valores (para graficar). |
| `verifica.cpp` | Comprueba todos los números de 1 a N y busca el que tarda más. |

## Ejecutar

```bash
make
./collatz 6              # 6 → 3 → 10 → 5 → 16 → 8 → 4 → 2 → 1 · 8 pasos
./collatz 27             # 111 pasos · máximo 9232 (paso 77)
./verifica 10000000      # todos llegan a 1 · el más largo: 8 400 511 (685 pasos)
```

Ojo: si algún número no llegara nunca a 1, `pasos()` no terminaría jamás. Por eso comprobar números no es demostrar la conjetura: siempre quedan infinitos por probar.

## Historia

- **1937:** Lothar Collatz plantea el problema.
- **Paul Erdős:** «Mathematics may not be ready for such problems» (citado en R. Guy, *Unsolved Problems in Number Theory*, E16).
- **2019:** Terence Tao demuestra que casi todas las órbitas alcanzan valores casi acotados (en densidad logarítmica) — [arXiv:1909.03562](https://arxiv.org/abs/1909.03562). «Casi todos» no es «todos».
- **2025:** D. Bařina comprueba la conjetura hasta 2⁷¹ ≈ 2,36 × 10²¹ con supercomputadoras — *The Journal of Supercomputing* 81 (2025), [doi:10.1007/s11227-025-07337-0](https://link.springer.com/article/10.1007/s11227-025-07337-0).
- Se les llama **números granizo** (*hailstone numbers*): suben y bajan como el granizo dentro de una nube.

## Vídeo

▶️ [La conjetura de Collatz: una regla de niño que nadie ha podido demostrar](https://youtube.com/shorts/ObevqFQaGUI)
