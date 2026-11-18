# 15 · El triángulo de Reuleaux (rueda como un círculo)

**Cómo se construye:** un triángulo equilátero de lado L y tres arcos de radio L, cada uno con centro en un vértice y que une los otros dos.

**Por qué rueda:** tiene **ancho constante**. Pon la figura entre dos rectas paralelas que la toquen: gire como gire, la distancia entre las rectas es siempre el lado L, igual que pasa con un círculo y su diámetro. Por eso una tabla apoyada sobre rodillos de Reuleaux avanza sin subir ni bajar.

**Lo que sí se mueve es el centro:** al rodar, el centro sube y baja (por eso no sirve como rueda con eje fijo). Lo que no cambia es la altura de lo que lleva encima.

**El programa** mide el ancho en 1 000 direcciones entre 0° y 180°, para un triángulo normal y para el de Reuleaux, y lo hace rodar por el suelo:

```
$ ./reuleaux
lado del triángulo = 1
ancho entre 2 rectas paralelas, 1000 direcciones:
  triángulo normal: de 0.866025 a 1.000000
  Reuleaux:         de 1.000000000000 a 1.000000000000
  |ancho - lado| < 1e-12 en 1000 de 1000 ✓
al rodar por el suelo:
  altura del centro: de 0.4226 a 0.5774
  altura de la tabla: 1.000000000000 siempre
```

- El triángulo normal mide entre √3/2 ≈ 0,866 (su altura, con las rectas paralelas a un lado) y 1 (el lado, con las rectas perpendiculares a un lado).
- El de Reuleaux mide 1 en las 1 000 direcciones.
- Al rodar, el centro va de 1 − 1/√3 ≈ 0,4226 a 1/√3 ≈ 0,5774 veces el lado; la tabla, siempre a 1.

Para cada dirección, el programa busca el punto de la figura que toca la recta: un vértice o un punto de uno de los tres arcos.

Con `--rueda N` saca una tabla de N poses del rodillo rodando (ángulo girado, distancia avanzada y posición del centro), y con `--cuadrado N` la del triángulo girando dentro de un cuadrado de lado 1, tocando los cuatro lados (la idea de la broca de Watts). En una vuelta completa avanza π · L, lo mismo que un círculo de diámetro L:

```
$ ./reuleaux --rueda 6
0.000000000 0.000000000 0.000000000 0.422649731
1.047197551 0.523598776 0.523598776 0.577350269
2.094395102 1.047197551 1.047197551 0.422649731
3.141592654 1.570796327 1.570796327 0.577350269
4.188790205 2.094395102 2.094395102 0.422649731
5.235987756 2.617993878 2.617993878 0.577350269
6.283185307 3.141592654 3.141592654 0.422649731
```

## Dónde se usa

- **Motor Wankel** (Mazda RX-7 y RX-8): el rotor se parece a un triángulo de Reuleaux, aunque con los lados menos curvos (no tiene ancho constante). Su centro gira en círculo alrededor del eje de salida, al que mueve mediante una excéntrica: una vuelta del rotor por cada tres del eje.
- **La broca de Watts:** Harry J. Watts patentó una broca basada en el triángulo de Reuleaux (patente US 1,241,176, solicitada en 1916 y concedida el 25/09/1917). Con una guía y un portabrocas flotante hace agujeros casi cuadrados, con las esquinas algo redondeadas.
- **Monedas británicas de 20 y 50 peniques:** son heptágonos de Reuleaux (de siete lados curvos), con diámetro constante para que las máquinas las midan igual en cualquier posición. La de 50p circula desde 1969 y la de 20p, desde 1982.

## El reto del vídeo

¿Por qué no existe un «cuadrado de Reuleaux»? La respuesta, en los comentarios del vídeo.

## Compilar y ejecutar

```bash
make
./reuleaux                 # ancho en 1000 direcciones y altura al rodar
./reuleaux --rueda 360     # 360 poses del rodillo rodando por el suelo
./reuleaux --cuadrado 360  # 360 poses del triángulo girando dentro de un cuadrado
```

## Historia

- **Franz Reuleaux (1829–1905)**, ingeniero mecánico alemán, autor de *Theoretische Kinematik* (1875; en inglés, *The Kinematics of Machinery*, 1876). Reunió unos 800 modelos de mecanismos, varios con este triángulo. La figura lleva su nombre no porque la inventara, sino porque fue el primero en generalizarla a otras curvas de ancho constante.

## Fuentes

- Wikipedia, «Reuleaux triangle»: https://en.wikipedia.org/wiki/Reuleaux_triangle
- Wikipedia, «Wankel engine»: https://en.wikipedia.org/wiki/Wankel_engine
- Wikipedia, «Watts Brothers Tool Works»: https://en.wikipedia.org/wiki/Watts_Brothers_Tool_Works
- Patente US 1,241,176 (H. J. Watts, «Drill or Boring Member», 1917): https://patents.google.com/patent/US1241176A
- Royal Mint, «Twenty pence coin»: https://www.royalmint.com/discover/uk-coins/coin-design-and-specifications/twenty-pence-coin/
- Royal Mint, «The science behind the shape of the 50p»: https://www.royalmint.com/collect/decimalisation/the-science-behind-the-shape-of-the-50p/
- Wikipedia, «Fifty pence (British coin)»: https://en.wikipedia.org/wiki/Fifty_pence_(British_coin)
- Cornell University Library, colección KMODDL (modelos de Reuleaux): https://digital.library.cornell.edu/collections/kmoddl/about
- Wikipedia, «Franz Reuleaux»: https://en.wikipedia.org/wiki/Franz_Reuleaux

## Vídeo

▶️ Este triángulo rueda como un círculo (y lo programé) · *pendiente*
