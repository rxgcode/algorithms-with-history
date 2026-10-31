// Cifrado César: corre cada letra k lugares en el alfabeto (A–Z, 26 letras).
// Rompe un mensaje probando las 25 claves y eligiendo la que más se parece al español.
#include <chrono>
#include <cstdio>
#include <string>

std::string cifrar(std::string texto, int k) {
    for (char& c : texto)
        if (c >= 'A' && c <= 'Z')
            c = 'A' + (c - 'A' + k) % 26;
    return texto;
}

// descifrar = restar k = avanzar 26 - k
std::string descifrar(std::string texto, int k) {
    return cifrar(texto, 26 - k);
}

// Frecuencia de cada letra en español, en % (A..Z, sin Ñ).
const double ES[26] = {12.53, 1.42, 4.68, 5.86, 13.68, 0.69, 1.01, 0.70, 6.25, 0.44, 0.02, 4.97, 3.15,
                       6.71, 8.68, 2.51, 0.88, 6.87, 7.98, 4.63, 3.93, 0.90, 0.01, 0.22, 0.90, 0.52};

// Qué tan lejos está un texto del español (chi cuadrado): cuanto más bajo, más «español».
double distancia(const std::string& t) {
    int n[26] = {0}, total = 0;
    for (char c : t)
        if (c >= 'A' && c <= 'Z') n[c - 'A']++, total++;
    double d = 0;
    for (int i = 0; i < 26; i++) {
        double esperado = ES[i] / 100 * total;
        d += (n[i] - esperado) * (n[i] - esperado) / esperado;
    }
    return d;
}

int main(int argc, char** argv) {
    std::string secreto = argc > 1 ? argv[1] : "DWDFDU DO DPDQHFHU";
    if (argc > 2 && std::string(argv[2]) == "--distancias") {   // qué tan lejos del español queda cada clave
        for (int k = 1; k <= 25; k++)
            std::printf("clave %2d → %s  distancia %.0f\n", k, descifrar(secreto, k).c_str(), distancia(descifrar(secreto, k)));
        return 0;
    }
    // Busca la clave más «española»; se repite 1000 veces para medir un tiempo estable (promedio por ronda).
    const int RONDAS = 1000;
    int mejor = 1;
    auto t0 = std::chrono::steady_clock::now();
    for (int r = 0; r < RONDAS; r++) {
        mejor = 1;
        for (int k = 1; k <= 25; k++)
            if (distancia(descifrar(secreto, k)) < distancia(descifrar(secreto, mejor))) mejor = k;
    }
    auto t1 = std::chrono::steady_clock::now();
    for (int k = 1; k <= 25; k++)
        std::printf("clave %2d → %s%s\n", k, descifrar(secreto, k).c_str(), k == mejor ? "   ← español" : "");
    std::printf("25 claves en %.0f microsegundos\n",
                std::chrono::duration<double, std::micro>(t1 - t0).count() / RONDAS);
}
