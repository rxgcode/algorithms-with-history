# 05 · Números que se corrigen solos

**El primer vídeo largo de la serie.** Del dígito que *avisa* de un error (tu DNI, tu tarjeta, los libros) a los códigos que *lo arreglan* solos (Hamming, Reed-Solomon en CDs, sondas espaciales y códigos QR).

## Archivos

| Archivo | Qué hace |
|---|---|
| `digito.cpp` | Dígito verificador del DNI de Perú (pesos 3·2·7·6·5·4·3·2, módulo 11 y tabla de conversión). Comprueba un número bien escrito, uno con un dígito cambiado y uno con dos vecinos volteados. |
| `luhn.cpp` | Algoritmo de Luhn (tarjetas). Incluye el único punto ciego: `09 ↔ 90`. |
| `hamming.cpp` | Código de Hamming (7,4): 4 bits de datos + 3 de paridad (los "tres círculos"). Voltea un bit y lo encuentra y corrige. |
| `simulacion.cpp` | Prueba 1,44 millones de errores de un dígito y ~126 000 de vecinos volteados sobre DNIs al azar: cuántos se le escapan al dígito numérico (tabla que repite el 1) y cuántos a la versión antigua con letras. |

## Ejecutar

```bash
make
./digito
./luhn
./hamming
./simulacion
```

```
$ ./digito
Digito de 45108273: 1

45108273-1  ->  ✓ correcto
45108278-1  ->  ✗ no cuadra
41508273-1  ->  ✗ no cuadra

$ ./luhn
4111111111111111  ->  ✓ pasa
4111111111111121  ->  ✗ error
4111111111111911  ->  ✗ error
4111111111091115  ->  ✓ pasa
4111111111901115  ->  ✓ pasa      ← "09" volteado a "90": se le escapa

$ ./hamming
enviado:   0110011
recibido:  0110111
error en el bit 5
corregido: 0110011  ✓ igual al original

$ ./simulacion
errores de un numero:   1440000
  se escapan (numeros): 1.87 %
  se escapan (letras):  0.00 %
vecinos volteados:      125977
  se escapan (numeros): 1.89 %
```

Todos los números de ejemplo son **inventados** o **de prueba**: `45108273` no es el DNI de nadie y `4111 1111 1111 1111` es el número de prueba de Visa que publican las pasarelas de pago.

## El QR que sobrevive aunque lo rompas

No hace falta código propio: se usan dos herramientas libres.

```bash
# macOS: brew install qrencode zbar   ·   Debian/Ubuntu: sudo apt install qrencode zbar-tools
qrencode -l H -s 12 -m 4 -o qr.png "Este mensaje sobrevive aunque rompas el código"   # nivel H: hasta ~30 %
# tapa el centro con un cuadrado negro (en el vídeo, 16×16 módulos) y léelo:
zbarimg -q --raw -Sbinary qr-roto.png; echo
```

Con el mismo mensaje, el nivel **L** da un QR de 29 × 29 módulos y el **H** uno de 41 × 41: más corrección, más cuadritos.

## Datos y notas

- **DNI de Perú.** RENIEC no publica el cálculo. Los pesos y la tabla (`6 7 8 9 0 1 1 2 3 4 5`, letras `K A B … J` antes del 14/08/2007) coinciden con la librería libre [python-stdnum](https://github.com/arthurdejong/python-stdnum) (`stdnum.pe.cui`) y con varias fuentes que lo documentan. Sobre el cambio de letra a número: nota de RENIEC, Resolución 692-2007.
- **Por qué 11.** Es el primo más pequeño mayor que 10: cualquier dígito cambiado y casi cualquier par de vecinos volteados cambian lo que sobra. Con 7, cambiar un 0 por un 7 no se notaría.
- **Chile (RUT)**, **ISBN-10** (la `X`) y el DNI usan módulo 11; las tarjetas usan Luhn (módulo 10) y los códigos de barras EAN-13 pesos 1·3.

## Historia y fuentes

- **1954** · Hans Peter Luhn (IBM) patenta su método (US 2,950,048, concedida en 1960). Hoy está en el estándar ISO/IEC 7812.
- **1947–1950** · Richard Hamming, en los laboratorios Bell, harto de que la máquina de relés abandonara sus trabajos del fin de semana por un solo error, inventa los códigos que se corrigen solos. *"Error detecting and error correcting codes"*, Bell System Technical Journal, 1950.
- **1960** · Irving Reed y Gustave Solomon publican los códigos Reed-Solomon, que hoy protegen CDs, DVDs, las sondas Voyager y los códigos QR (niveles L/M/Q/H, ISO/IEC 18004).

## Vídeo

[Ver el vídeo en YouTube](https://www.youtube.com/watch?v=vuo-ulqw0Wo)
