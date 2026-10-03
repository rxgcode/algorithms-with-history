# 01 · El misterio del 196

**El juego:** toma un número, súmale su reverso y repite hasta obtener un palíndromo (un número que se lee igual al derecho y al revés).

```
59 + 95 = 154 → 154 + 451 = 605 → 605 + 506 = 1111   (3 pasos)
```

Casi todos los números llegan… pero con el **196** nadie lo ha logrado. Es el menor candidato a **número de Lychrel**: nadie ha demostrado que nunca llegue, pero tampoco nadie ha encontrado su palíndromo.

## Archivos

| Archivo | Qué hace |
|---|---|
| `palindromo.cpp` | Versión con `long long`. Con el 196 se desborda en el paso 40 y el número sale negativo. |
| `palindromo_grande.cpp` | Suma dígito a dígito guardando el número como texto: sin límite de tamaño. |

## Ejecutar

```bash
make
./palindromo 59              # palíndromo en 3 pasos
./palindromo 89              # palíndromo en 24 pasos (8813200023188)
./palindromo 196             # se desborda en el paso 40
./palindromo_grande 196 50000
```

Salida de la última orden (≈ 2 s):

```
después de 50000 pasos: 20779 dígitos
ningún palíndromo
```

## Historia

- **1967** · Charles W. Trigg, "Palindromes by Addition", *Mathematics Magazine* 40, pp. 26–28: revisa los números menores de 10 000 y encuentra 249 que no llegan; el 196 es el menor.
- **1987–1990** · John Walker lo deja calculando casi tres años en una Sun 3/260: 2 415 836 iteraciones, un millón de dígitos, sin palíndromo.
- **2006** · Wade VanLandingham llega a 300 millones de dígitos y populariza el nombre *Lychrel* (anagrama aproximado de Cheryl).
- **2015** · Romain Dolbeau alcanza mil millones de dígitos. Nada.

Fuentes: Wikipedia, "Lychrel number"; Trigg (1967). Ejercicio inspirado en el 3.15 "Conjetura para la formación de palíndromos" del libro de ejercicios de C++ de profesores de la UCM.

## Vídeo

[Ver el short en YouTube](https://youtube.com/shorts/MyjG1hMHh3I)
