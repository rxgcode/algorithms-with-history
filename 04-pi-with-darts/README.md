# 04 · π con dardos

**La idea:** pon una diana redonda (radio 1) dentro de un cuadrado de lado 2 y lanza dardos al azar. El círculo ocupa π/4 del área del cuadrado, así que:

```
dentro / total ≈ π / 4    →    π ≈ 4 × dentro / total
```

Versión simplificada, la que se ve en el vídeo (en `dardos.cpp`, `azar` es un generador `mt19937_64` con semilla fija):

```cpp
for (long long i = 0; i < total; i++) {
    double x = azar(), y = azar();          // número entre -1 y 1
    if (x*x + y*y <= 1) dentro++;           // cayó en la diana
}
double pi = 4.0 * dentro / total;
```

Funciona… pero despacio: el error baja con √N, así que **cada cifra correcta nueva cuesta unas 100 veces más dardos**.

## Archivos

| Archivo | Qué hace |
|---|---|
| `dardos.cpp` | Lanza N dardos (semilla fija 196, resultados reproducibles) y muestra π en cada potencia de 10; cifras correctas en verde. |
| `puntos.cpp` | Exporta las coordenadas de los primeros dardos (los 100 que se ven caer en el vídeo). |

## Ejecutar

```bash
make
./dardos 1000000000      # ≈ 4 s
```

```
          100 dardos  π ≈ 3.040000
        1 000 dardos  π ≈ 3.088000
       10 000 dardos  π ≈ 3.108000
      100 000 dardos  π ≈ 3.133960
    1 000 000 dardos  π ≈ 3.141008
   10 000 000 dardos  π ≈ 3.141615
  100 000 000 dardos  π ≈ 3.141685
1 000 000 000 dardos  π ≈ 3.141611
```

De un millón a mil millones de dardos (mil veces más) no se gana ni una cifra segura.

## Historia

- **1733 / 1777** · Georges-Louis Leclerc, conde de Buffon, plantea el problema de la aguja: dejar caer agujas sobre un suelo de tablas permite estimar π.
- **1901** · Mario Lazzarini afirma haber obtenido 355/113 (seis decimales correctos) con 3408 lanzamientos; hoy se considera un resultado amañado.
- **1946** · Stanislaw Ulam, convaleciente y jugando solitarios, propone simular muchas veces en lugar de calcular. Nicholas Metropolis lo bautiza **Monte Carlo**, por el casino. En la primavera de 1948 se ejecutan en la ENIAC los primeros cálculos Monte Carlo automáticos (Los Álamos).

Fuentes: Wikipedia, "Monte Carlo method" y "Buffon's needle problem". Ejercicio inspirado en el 3.14 "Aproximación hacia π con dardos" del libro de ejercicios de C++ de profesores de la UCM.

## Vídeo

[Ver el short en YouTube](https://youtube.com/shorts/zHRd2ayBlxk)
