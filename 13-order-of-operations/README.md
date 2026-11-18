# 13 · 12 ÷ 2 × 3: ¿18 o 2? (orden de las operaciones)

**La regla:** multiplicar y dividir tienen la misma prioridad y se resuelven de izquierda a derecha. Así que 12 ÷ 2 × 3 = (12 ÷ 2) × 3 = 6 × 3 = **18**. Es también la regla de C++ y de Python: `*` y `/` tienen la misma precedencia y se agrupan por la izquierda (`python3 -c "print(12 / 2 * 3)"` da `18.0`).

**De dónde sale el 2:** de hacer primero 2 × 3 (12 ÷ 6 = 2). Con el signo × eso no sigue la regla. Pero con la **multiplicación implícita** (sin signo: 2(3), 2A, a/bc) hay convenciones que la hacen antes que × y ÷. *Concrete Mathematics*, de Graham, Knuth y Patashnik, lo dice así: «a/bc means the same as a/(bc)».

**El programa:** un evaluador mínimo de expresiones (descenso recursivo) que arma el árbol de la operación, lo escribe con todos sus paréntesis y lo calcula de abajo hacia arriba, paso a paso. Lo que queda más abajo en el árbol se calcula primero: aquí, la división.

```
$ ./evalua "12 / 2 * 3"
árbol:  ((12 / 2) * 3)
paso 1: 12 / 2 = 6
paso 2: 6 * 3 = 18
resultado: 18
```

Con `--implicita`, la multiplicación sin signo `2(3)` va antes que × y ÷ (la convención de algunos libros y calculadoras). Sin la opción, `2(3)` es una multiplicación más, con la misma prioridad que × y ÷:

```
$ ./evalua "12 / 2(3)"
árbol:  ((12 / 2)(3))
paso 1: 12 / 2 = 6
paso 2: 6 * 3 = 18
resultado: 18

$ ./evalua --implicita "12 / 2(3)"
árbol:  (12 / (2(3)))
paso 1: 2 * 3 = 6
paso 2: 12 / 6 = 2
resultado: 2
```

## Las calculadoras tampoco se ponen de acuerdo

Según sus manuales oficiales, con multiplicación implícita (12 ÷ 2A, con A = 3 en la memoria):

- **Casio fx-82MS:** la multiplicación implícita («2π, 3e, 5A…») está en el nivel 5 de prioridad y × ÷ en el nivel 9 → 12 ÷ 2A = 12 ÷ 6 = **2**.
- **Texas Instruments:** en las TI-80, TI-81, TI-82 y TI-85 la implícita tenía más prioridad, pero desde la familia TI-83 y TI-84 Plus «implied and explicit multiplication is given the same priority» → 12 ÷ 2A = 6 × 3 = **18**.

## El reto del vídeo

¿Cuánto da **8 ÷ 2(2+2)**? Se hizo viral en 2019 y llegó a *The New York Times*. Puedes probarlo con el programa, con y sin `--implicita`. La respuesta, en los comentarios del vídeo.

## Compilar y ejecutar

```bash
make
./evalua "12 / 2 * 3"                # izquierda a derecha: 18
./evalua --implicita "12 / 2(3)"     # la implícita primero: 2
```

Las comillas hacen falta para que la terminal no interprete el `*` ni los paréntesis. Acepta `+`, `-`, `*`, `/`, paréntesis y números con decimales.

## Historia y fuentes

- La regla de «izquierda a derecha» para × y ÷ es la convención actual; la de dar más prioridad a la multiplicación implícita aparece en algunos libros y guías de estilo (por ejemplo, la de *Physical Review*), pero no es universal.
- **2019:** la operación 8 ÷ 2(2+2) se hace viral y el matemático Steven Strogatz le dedica un artículo en *The New York Times*, «The Math Equation That Tried to Stump the Internet» (02/08/2019).
- Wikipedia, «Order of operations»: https://en.wikipedia.org/wiki/Order_of_operations
- S. Strogatz, «The Math Equation That Tried to Stump the Internet», *The New York Times*, 02/08/2019: https://www.nytimes.com/2019/08/02/science/math-equation-pedmas-bemdas-bedmas.html
- Casio, manual fx-82MS/85MS/220PLUS/300MS/350MS, «Calculation Priority Sequence»: https://support.casio.com/global/en/calc/manual/fx-82MS_85MS_220PLUS_300MS_350MS_en/technical_informatoin/sequence.html
- Texas Instruments, «Solution 11773: Implied Multiplication Versus Explicit Multiplication on TI Graphing Calculators»: https://education.ti.com/en/customer-support/knowledge-base/ti-83-84-plus-family/product-usage/11773
- R. L. Graham, D. E. Knuth, O. Patashnik, *Concrete Mathematics*, 2.ª ed., Addison-Wesley, 1994, p. xi.

## Vídeo

▶️ 12 ÷ 2 × 3: ¿18 o 2? La respuesta, programada en C++ · ▶️ [12 ÷ 2 × 3: ¿18 o 2? La respuesta, programada en C++](https://youtube.com/shorts/_zBu0mbBvYk)
