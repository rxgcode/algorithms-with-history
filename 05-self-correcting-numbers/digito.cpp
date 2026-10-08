// Dígito verificador de un documento: DNI de Perú (módulo 11).
#include <iostream>
#include <string>

char digitoDNI(const std::string& dni) {
    const int pesos[8] = {3, 2, 7, 6, 5, 4, 3, 2};
    const char tabla[11] = {'6','7','8','9','0','1','1','2','3','4','5'};
    int suma = 0;
    for (int i = 0; i < 8; i++) suma += (dni[i] - '0') * pesos[i];
    int k = 11 - suma % 11;
    return tabla[k == 11 ? 0 : k];
}

void revisar(const std::string& dni, char digito) {
    char esperado = digitoDNI(dni);
    std::cout << dni << "-" << digito << "  ->  "
              << (esperado == digito ? "✓ correcto" : "✗ no cuadra") << "\n";
}

int main() {
    std::string dni = "45108273";              // número inventado
    char d = digitoDNI(dni);
    std::cout << "Digito de " << dni << ": " << d << "\n\n";
    revisar(dni, d);                            // bien escrito
    revisar("45108278", d);                     // un número cambiado
    revisar("41508273", d);                     // dos vecinos volteados
}
