// ¿Cuántos errores se le escapan al dígito del DNI de Perú?
// Prueba TODOS los errores de un dígito y de vecinos volteados sobre DNIs al azar
// y compara la versión con números (tabla que repite el 1) con la antigua de letras.
#include <iostream>
#include <random>
#include <string>

const int pesos[8] = {3, 2, 7, 6, 5, 4, 3, 2};
const char numeros[11] = {'6','7','8','9','0','1','1','2','3','4','5'};
const char letras[11]  = {'K','A','B','C','D','E','F','G','H','I','J'};

int posicion(const std::string& dni) {
    int suma = 0;
    for (int i = 0; i < 8; i++) suma += (dni[i] - '0') * pesos[i];
    int k = 11 - suma % 11;
    return k == 11 ? 0 : k;
}

int main() {
    std::mt19937 rng(1);                                  // semilla fija: siempre el mismo resultado
    std::uniform_int_distribution<int> dig(0, 9);
    long total = 0, escapanNum = 0, escapanLet = 0, vecinos = 0, escapanVec = 0;
    for (int n = 0; n < 20000; n++) {
        std::string dni(8, '0');
        for (auto& c : dni) c = char('0' + dig(rng));
        int p = posicion(dni);
        for (int i = 0; i < 8; i++)                       // cambiar un número por otro
            for (char c = '0'; c <= '9'; c++) {
                if (c == dni[i]) continue;
                std::string e = dni; e[i] = c;
                int q = posicion(e);
                total++;
                if (numeros[q] == numeros[p]) escapanNum++;
                if (letras[q] == letras[p]) escapanLet++;
            }
        for (int i = 0; i < 7; i++) {                     // voltear dos vecinos
            if (dni[i] == dni[i + 1]) continue;
            std::string e = dni; std::swap(e[i], e[i + 1]);
            vecinos++;
            if (numeros[posicion(e)] == numeros[p]) escapanVec++;
        }
    }
    std::cout.setf(std::ios::fixed); std::cout.precision(2);
    std::cout << "errores de un numero:   " << total << "\n"
              << "  se escapan (numeros): " << 100.0 * escapanNum / total << " %\n"
              << "  se escapan (letras):  " << 100.0 * escapanLet / total << " %\n"
              << "vecinos volteados:      " << vecinos << "\n"
              << "  se escapan (numeros): " << 100.0 * escapanVec / vecinos << " %\n";
}
