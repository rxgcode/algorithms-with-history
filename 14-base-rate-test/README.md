# 14 · Das positivo en un test que acierta el 99 % (Bayes y la tasa base)

**El problema:** una enfermedad la tiene 1 de cada 1 000 personas. Un test acierta el 99 %: detecta al 99 % de los enfermos (**sensibilidad**) y solo da positivo al 1 % de los sanos (**falsos positivos**; especificidad del 99 %). Das positivo. ¿Qué probabilidad hay de que estés enfermo?

**Cerca del 9 %.** Se ve contando personas, sin fórmulas:

| De 1 000 personas | | Dan positivo |
|---|---|---|
| 1 enferma | el test la detecta (99 %) | ≈ 1 |
| 999 sanas | el 1 % da positivo | ≈ 10 |
| | **total** | **≈ 11, y solo 1 enfermo** |

1 de cada 11 positivos ≈ 9 %. Hay tantos sanos que su 1 % de error pesa más que todos los enfermos juntos: es la **falacia de la tasa base**. Con la fórmula de Bayes: 0,001 · 0,99 / (0,001 · 0,99 + 0,999 · 0,01) = 9,02 %.

**El programa** simula 1 000 000 de personas, cada una con su enfermedad (o no) y su test al azar:

```
$ ./test99
1 000 000 personas · 1 025 enfermas
sensibilidad 99 % · falsos positivos 1 %

dieron positivo:      11 052
enfermos de verdad:    1 014
→ solo el 9,2 % de los positivos
```

Son las «11 y 1» de la tabla, multiplicadas por unas 1 000.

## Ojo: si tienes síntomas, todo cambia

«Probablemente no lo tienes» vale para un test de rutina. Si te lo hacen porque tienes síntomas, la probabilidad de partida es mucho mayor. Por ejemplo, si 1 de cada 100 personas con esos síntomas lo tiene (el segundo número es ese «1 de cada…»):

```
$ ./test99 1 100
1 000 000 personas · 9 854 enfermas
sensibilidad 99 % · falsos positivos 1 %

dieron positivo:      19 704
enfermos de verdad:    9 751
→ solo el 49,5 % de los positivos
```

(La fórmula da 50 %.)

## El reto del vídeo

Si das positivo **dos veces seguidas**, ¿qué probabilidad hay de que estés enfermo? El programa lo simula con `./test99 2`, suponiendo que los errores de los dos tests son independientes. La respuesta, en los comentarios del vídeo.

## Compilar y ejecutar

```bash
make
./test99            # un test a cada persona: 9,2 %
./test99 1 100      # con síntomas: 1 de cada 100 lo tiene → 49,5 %
./test99 2          # el reto: positivo 2 veces seguidas
```

Uso: `./test99 [tests] [1 de cada…]`, con 1 a 3 tests (por defecto 1) y la enfermedad en 1 de cada 1 000 personas (por defecto).

La semilla es fija (1982), así que siempre salen los mismos números. Para que salgan iguales en cualquier compilador no se usa `std::uniform_real_distribution` (cada biblioteca la implementa distinto): el número al azar en [0, 1) se saca de los 53 bits altos de `std::mt19937_64`, cuya secuencia fija el estándar. Cada persona tira siempre los mismos 4 números (enfermedad + 3 tests), así que con 1, 2 o 3 tests es la misma población.

## Historia

- **1982:** David M. Eddy publica «Probabilistic reasoning in clinical medicine» en *Judgment under Uncertainty* (Kahneman, Slovic y Tversky, eds.). Con un caso de mamografía (probabilidad previa del 1 %, sensibilidad ≈ 80 %, falsos positivos 9,6 %), unos **95 de cada 100 médicos** estimaron la probabilidad de cáncer tras un positivo en torno al **75 %**; la respuesta correcta era ≈ **7,7 %**. Fue una muestra informal y con otros números que los de este test, pero era el mismo tipo de pregunta.
- **1995:** Gerd Gigerenzer y Ulrich Hoffrage muestran que con **frecuencias naturales** («de 1 000 personas, 10 dan positivo…»), justo el método de la tabla de arriba, el razonamiento bayesiano mejora mucho sin enseñar fórmulas.
- **2007:** Gigerenzer cuenta en *APS Observer* que, al hacer el mismo tipo de pregunta a 160 ginecólogos, la respuesta más frecuente fue 90 %, cuando lo correcto era ≈ 10 %.

## Fuentes

- D. M. Eddy, «Probabilistic reasoning in clinical medicine: Problems and opportunities», en D. Kahneman, P. Slovic y A. Tversky (eds.), *Judgment under Uncertainty: Heuristics and Biases*, Cambridge University Press, 1982, pp. 249–267: https://www.cambridge.org/core/books/abs/judgment-under-uncertainty/probabilistic-reasoning-in-clinical-medicine-problems-and-opportunities/661E12D1ECD669EDB5B410407A4BB570
- G. Gigerenzer y U. Hoffrage, «How to improve Bayesian reasoning without instruction: Frequency formats», *Psychological Review* 102(4), 684–704, 1995: https://pages.ucsd.edu/~scoulson/203/GG_How_1995.pdf
- G. Gigerenzer, «Helping Physicians Understand Screening Tests Will Improve Health Care», *APS Observer*, noviembre de 2007: https://www.psychologicalscience.org/observer/helping-physicians-understand-screening-tests-will-improve-health-care
- T. Krynski y J. Tenenbaum, «The Role of Causal Models in Reasoning Under Uncertainty», *CogSci* 25, 2003: https://escholarship.org/uc/item/82d1f0wr

## Vídeo

▶️ Das positivo en un test que acierta el 99 %… y probablemente no lo tienes · *pendiente*
