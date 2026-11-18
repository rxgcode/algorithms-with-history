# 12 · El 0,1 que dejó pasar un misil (Patriot, 1991)

**Qué pasó:** el 25 de febrero de 1991, en Dhahran (Arabia Saudita), un misil Scud cayó sobre un cuartel del Ejército de EE. UU. y murieron 28 soldados. La batería Patriot que debía derribarlo no lo rastreó. Según el informe del GAO, la causa fue un error de redondeo en el reloj del sistema.

**El error:** el reloj contaba el tiempo en décimas de segundo y, para pasarlo a segundos, multiplicaba por 0,1. Pero 0,1 en binario no termina nunca:

```
0,1 = 0,000110011001100110011001100110011…  (el bloque 0011 se repite para siempre)
```

En el cálculo del Patriot se guardaban 23 cifras después de la coma (registro de 24 bits); el resto se cortaba. Cada décima se perdían ≈ 0,0000000954 s. Con la batería encendida unas 100 horas seguidas, el error acumulado llegó a 0,34 s: a la velocidad de un Scud (≈ 1 676 m/s), más de medio kilómetro. El radar buscó el misil donde ya no estaba.

```
$ ./patriot
0,1 en binario:  0,00011001100110011001100...
lo que se guarda: 0.0999999046
error por décima: 0.0000000954 s

horas   error (s)   el Scud avanza (m)
    1      0.0034          6
    8      0.0275         46
   20      0.0687        115
   48      0.1648        276
   72      0.2472        414
  100      0.3433        575
```

Los errores coinciden con la tabla del apéndice II del informe del GAO (que imprime 0,0025 en la fila de 8 horas: es una errata, el valor es 0,0275). El GAO calcula además que la «ventana» del radar se corrió 687 m a las 100 horas.

## El reto del vídeo

¿Desde cuántas horas encendido el error pasa de una décima de segundo? El programa lo calcula si le pasas el error buscado:

```
$ ./patriot 0.1
...
error de 0.10 s tras 29.1 horas encendido
```

(Son exactamente 2²⁰ décimas: cada décima pierde 0,1 · 2⁻²⁰ s.)

## Compilar y ejecutar

```bash
make
./patriot          # tabla de errores
./patriot 0.1      # ¿cuántas horas para un error de 0,1 s?
```

## Fuentes

- U.S. GAO, «Patriot Missile Defense: Software Problem Led to System Failure at Dhahran, Saudi Arabia», GAO/IMTEC-92-26 (04/02/1992): https://www.gao.gov/products/imtec-92-26
- R. Skeel, «Roundoff Error and the Patriot Missile», SIAM News 25(4), 1992.
- D. N. Arnold, «The Patriot Missile Failure»: https://www-users.cse.umn.edu/~arnold/disasters/patriot.html
