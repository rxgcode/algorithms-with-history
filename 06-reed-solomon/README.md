# 06 · Reed-Solomon: cómo se reparan pedazos enteros

**Parte 2 de «Números que se corrigen solos».** Un CD rayado, un QR con un logo encima y una foto desde Urano usan el mismo truco de 1960: convertir los bytes en una curva, evaluarla en más puntos de los necesarios y mandar los puntos. Con los que lleguen bien se reconstruye la curva.

## Archivos

| Archivo | Qué hace |
|---|---|
| `rs.cpp` | Codificador y decodificador Reed-Solomon completos sobre GF(256) (polinomio `0x11D`, el del estándar QR): paridad con el polinomio generador, síndromes, Berlekamp–Massey, búsqueda de Chien y Forney, con soporte de borrados (posiciones conocidas). Demo: un mensaje de 22 bytes con 10 de paridad sobrevive a 10 bytes borrados seguidos y a 5 bytes cambiados al azar; con 6 lo detecta y avisa. `--prueba`: 2000 mensajes con 6 errores. |
| `intercalado.cpp` | Por qué un rayón largo no destruye ningún bloque entero: 28 bloques de 28 bytes; con y sin intercalar, cuántos bytes pierde el peor bloque. |

## Ejecutar

```bash
make
./rs
./rs --prueba
./intercalado 112
```

```
$ ./rs
mensaje  (22 bytes): Este mensaje sobrevive
paridad  (10 bytes): B6 DD 44 07 4A 4E 6E 5B 99 B9 

rayón: se pierden 10 bytes seguidos (posiciones conocidas)
   leído:    Est??????????sobrevive
   reparado: Este mensaje sobrevive  ✓ igual al original

ruido: 5 bytes cambiados sin saber cuáles
   leído:    Este mens;je sobr?vi,e
   reparado: Este mensaje sobrevive  ✓ 5 errores corregidos

ruido: 6 bytes cambiados
   leído:    E)te men)a0e s5brevive
   reparado: ✗ no se puede: demasiados errores

$ ./rs --prueba
con 6 errores (uno más del límite), 2000 mensajes:
  detectado 2000/2000 · corregido mal sin avisar 0/2000

$ ./intercalado 112
SIN intercalar:  rayón de 112 bytes → toca 5 bloques
    el peor pierde 28 de 28 bytes  ✗ irreparable
CON intercalado: rayón de 112 bytes → toca 28 bloques
    el peor pierde 4 de 28 bytes  ✓ reparable · límite 4
```

## Lo que muestran los números

- Con **P** bytes de paridad, Reed-Solomon repara hasta **P borrados** (se sabe qué posiciones fallaron) o **P/2 errores** (no se sabe cuáles). Con P = 10: 10 borrados ✓, 5 errores ✓, 6 errores → lo detecta y no entrega basura.
- `./rs --prueba` usa una semilla fija, así que el resultado (`detectado 2000/2000 · corregido mal sin avisar 0/2000`) es reproducible.
- En el CD, los bytes de cada bloque se reparten a lo largo de más de 100 cuadros (intercalado): un rayón de 112 bytes seguidos, que sin intercalar destruye 5 bloques, intercalado le quita solo 4 bytes a cada uno, y 4 sí se reparan.
- La paridad de `rs.cpp` coincide byte a byte con la librería `reedsolo` (Python) para el mismo polinomio y los mismos parámetros (`fcr = 0`, generador α = 2).

## Fuentes

- I. S. Reed y G. Solomon, «Polynomial Codes over Certain Finite Fields», *J. SIAM* 8(2), 1960, pp. 300–304.
- E. R. Berlekamp, *Algebraic Coding Theory* (1968); J. L. Massey, «Shift-register synthesis and BCH decoding» (1969).
- K. A. S. Immink, «Reed-Solomon codes and the compact disc» (CIRC: C1 (32,28) y C2 (28,24), ráfaga corregible de 4000 bits ≈ 2,5 mm).
- ISO/IEC 18004 (QR): niveles L/M/Q/H; versión 6-H = 4 bloques × (15 datos + 28 paridad).
- R. J. McEliece y L. Swanson (JPL), «Reed-Solomon codes and the exploration of the Solar System»: RS(255,223) con intercalado 4 en Voyager 2; decodificador operativo para Urano (1986).

Vídeo: *(pendiente de publicar)*
