# 09 · El cifrado César

**La idea:** correr cada letra k lugares en el alfabeto. Con k = 3, la A se escribe D, la B se escribe E… y al pasar la Z se vuelve al inicio (X → A, Y → B, Z → C). «ATACAR AL AMANECER» → «DWDFDU DO DPDQHFHU».

```cpp
std::string cifrar(std::string texto, int k) {
    for (char& c : texto)
        if (c >= 'A' && c <= 'Z')
            c = 'A' + (c - 'A' + k) % 26;
    return texto;
}
```

**Cómo se rompe:** solo hay 25 claves. El programa las prueba todas y elige la que deja un texto más parecido al español: cuenta cuántas veces aparece cada letra y lo compara con la frecuencia normal del español (distancia χ²). Es el análisis de frecuencias, descrito por al-Kindi en el siglo IX.

## Ejecutar

```bash
make
./cesar                                          # rompe «DWDFDU DO DPDQHFHU» → clave 3 → ATACAR AL AMANECER
./cesar "DWDFDU DO DPDQHFHU" --distancias        # la distancia al español de cada clave (clave 3: 18)
./cesar "DT WPPD PDEZ JL AFPOPD CZXAPC L NPDLC"  # el reto del vídeo (spoiler)
```

El tiempo que imprime es el promedio de 1000 rondas de búsqueda (las 25 claves), para que la medida sea estable: unos 2 microsegundos en una Mac con Apple Silicon.

## Historia

- **Julio César** usaba un desplazamiento de 3: Suetonio, *Vida de los doce césares*, «Julio» 56. **Augusto** corría solo 1 y, en vez de volver al inicio, escribía AA por X («Augusto» 88).
- **Al-Kindi (siglo IX)** dejó el registro más antiguo del análisis de frecuencias (S. Singh, *The Code Book*, 2000).
- **1915:** el ejército ruso lo usó porque sus tropas no dominaban cifrados más complicados; los alemanes y austriacos leían sus mensajes sin dificultad (D. Kahn, *The Codebreakers*, 1967).
- **2006:** Bernardo Provenzano, jefe de la mafia siciliana, usaba una variante con números (A = 4, B = 5…); descifrar sus notas ayudó a la investigación que terminó con su arresto ([The Register, 19/04/2006](https://www.theregister.com/2006/04/19/mafia_don_clueless_crypto/)).
- El ejemplo usa el alfabeto moderno A–Z (26 letras, sin Ñ); el latino de César no tenía J, U ni W.
