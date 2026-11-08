# 11 · El problema de Monty Hall

**El juego:** tres puertas; detrás de una hay un auto y detrás de las otras dos, cabras. Eliges una. El presentador, que **sabe** dónde está el auto, abre otra de las puertas y siempre sale una cabra. ¿Te quedas con tu puerta o cambias a la que queda?

**Cambiar gana 2 de cada 3 veces.** Caso por caso (eliges la 1):

| Detrás de tu puerta | El presentador abre | Si te quedas | Si cambias |
|---|---|---|---|
| el auto | una de las cabras | ganas | pierdes |
| la cabra A | la cabra B (no puede abrir el auto) | pierdes | ganas |
| la cabra B | la cabra A | pierdes | ganas |

Con 100 puertas se ve más claro: eliges una, el presentador abre 98 con cabra y queda una. Cambiar gana el 99 %.

```
$ ./monty 1000000
1000000 partidas · 3 puertas
  quedarse: 333734 victorias (33.4 %)
  cambiar:  666266 victorias (66.6 %)
```

## El reto del vídeo

¿Y si el presentador **no sabe** dónde está el auto, abre una puerta al azar y justo sale una cabra? Entonces da igual: 50 % y 50 %. Lo que cambia todo es que el presentador sepa y nunca pueda abrir el auto. La simulación descarta las partidas en que sale el auto:

```
$ ./monty 1000000 3 --azar
666520 partidas · 3 puertas · el presentador abre al azar
  quedarse: 332904 victorias (49.9 %)
  cambiar:  333616 victorias (50.1 %)
```

## Ejecutar

```bash
make
./monty 1000000              # quedarse 33.4 %, cambiar 66.6 %
./monty 1000000 100          # 100 puertas: cambiar 99.0 %
./monty 1000000 3 --azar     # el presentador abre al azar: 49.9 % / 50.1 %
```

La semilla es fija (1990), así que siempre salen los mismos números.

## Historia

- **1975:** Steve Selvin plantea el problema en dos cartas a *The American Statistician* (febrero y agosto); en la segunda lo llama «Monty Hall problem», por el presentador de *Let's Make a Deal*.
- **1990:** Marilyn vos Savant responde en su columna «Ask Marilyn» (*Parade*, 9 de septiembre) que hay que cambiar. Según ella, le escribieron unas 10 000 personas, casi 1 000 con doctorado, la mayoría diciendo que se equivocaba.
- Paul Erdős no se convenció hasta ver una simulación por computadora (lo contó Andrew Vázsonyi).
- **2008:** sale en la película *21*: un profesor del MIT se lo plantea a un alumno en clase.
- **2010:** Herbranson y Schroeder muestran que unas palomas aprenden a cambiar casi siempre; las personas, con el mismo entrenamiento, no tanto.
- Fuentes: [Wikipedia, «Monty Hall problem»](https://en.wikipedia.org/wiki/Monty_Hall_problem) · J. Tierney, «Behind Monty Hall's Doors: Puzzle, Debate and Answer?», *The New York Times* (21/07/1991) · W. Herbranson y J. Schroeder, [«Are birds smarter than mathematicians?»](https://pmc.ncbi.nlm.nih.gov/articles/PMC3086893/), *J. Comparative Psychology* 124 (2010).
