# 02 · La persona famosa

**El problema:** en una fiesta hay una persona famosa: **todos la conocen y ella no conoce a nadie**. Solo puedes preguntar "¿A conoce a B?". ¿Cuántas preguntas necesitas para encontrarla?

- **Fuerza bruta:** preguntar a cada uno por cada uno → n·(n−1) preguntas. Con 1000 invitados, 999 000.
- **Por descarte:** cada respuesta elimina a alguien. Si A conoce a B, A no es famosa; si no lo conoce, B no lo es. Queda un solo candidato y se comprueba → como máximo 3·(n−1) preguntas. Con 1000 invitados, 2 997.

```cpp
int candidato = 0;
for (int i = 1; i < n; i++)
    if (pregunta(candidato, i)) candidato = i;   // si conoce a i, no es famoso
// después: comprobar al que quedó (ver eliminacion() en famoso.cpp)
```

## Archivos

| Archivo | Qué hace |
|---|---|
| `famoso.cpp` | Genera una fiesta (semilla fija) y compara fuerza bruta contra eliminación. |
| `prueba.cpp` | 5000 fiestas aleatorias (con y sin famoso): ambas soluciones deben coincidir. |

## Ejecutar

```bash
make
./famoso 1000
./prueba
```

```
1000 invitados (famoso: #700)
fuerza bruta: #700 en 999 000 preguntas
por descarte: #700 en 2 997 preguntas
pruebas: 5000/5000 coinciden (y eliminacion <= 3(n-1) preguntas)
```

## Historia

K. N. King y B. Smith-Thomas, "An optimal algorithm for sink-finding", *Information Processing Letters* 14(3), 1982.

Ejercicio inspirado en el 4.19 "Búsqueda de la persona famosa en una reunión" del libro de ejercicios de C++ de profesores de la UCM.
