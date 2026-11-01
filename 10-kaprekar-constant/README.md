# 10 · El 6174 (constante de Kaprekar)

**La regla:** toma un número de 4 cifras que no tenga las cuatro iguales. Ordena sus cifras de mayor a menor, réstale el mismo número con las cifras de menor a mayor y repite con el resultado. En 7 pasos o menos siempre llegas al **6174**, y de ahí ya no sales: 7641 − 1467 = 6174.

```
1998 → 9981 − 1899 = 8082
     → 8820 − 0288 = 8532
     → 8532 − 2358 = 6174
```

El detalle que rompe la primera versión del programa: el resultado se trata **siempre con 4 cifras**. 2111 − 1112 = 999 hay que leerlo como 0999; si se lee como 999 (3 cifras), 999 − 999 = 0 y se atasca.

```cpp
std::string s = std::to_string(n);
if (ceros) s = std::string(4 - s.size(), '0') + s;   // 999 → "0999"
```

## Archivos

| Archivo | Qué hace |
|---|---|
| `kaprekar.cpp` | Los pasos de un número hasta 6174 (`--sin-ceros`: el error de leer 0999 como 999). |
| `verifica.cpp` | Prueba todos los números de 4 cifras (o un rango) y cuenta en cuántos pasos llega cada uno. |
| `otras.cpp` | La misma regla con 2, 3, 5 o 6 cifras: a qué número o ciclo caen todos. |

## Ejecutar

```bash
make
./kaprekar 1998               # 6174 en 3 pasos
./kaprekar 2111 --sin-ceros   # atascado en 0
./kaprekar 2111               # 6174 en 5 pasos
./verifica                    # 8 991 de 8 991 llegan; el máximo es 7 pasos
./verifica 1900 2026          # años: 18 tardan los 7 pasos (1949 es uno)
./otras 3                     # todos caen en 495
./otras 2                     # ciclo 09 → 81 → 63 → 27 → 45
```

## Historia

- **1946–1949:** Dattatreya Ramchandra Kaprekar (1905–1986), profesor de matemáticas de colegio en Devlali (India), encuentra la propiedad y la presenta en 1949 en la Madras Mathematical Conference.
- **1975:** Martin Gardner la da a conocer en su columna «Mathematical Games» de *Scientific American* (marzo).
- Fuentes: [MacTutor, St Andrews](https://mathshistory.st-andrews.ac.uk/Biographies/Kaprekar/) · Y. Nishiyama, [«Mysterious number 6174»](https://plus.maths.org/content/mysterious-number-6174), *Plus Magazine* (2006).
