// Código de Hamming (7,4): 4 bits de datos + 3 de paridad.
// Si un bit se voltea, los círculos que fallan señalan cuál fue.
#include <iostream>
#include <string>

// posiciones 1..7: p1 p2 d1 p3 d2 d3 d4
std::string codificar(int d1, int d2, int d3, int d4) {
    int p1 = d1 ^ d2 ^ d4, p2 = d1 ^ d3 ^ d4, p3 = d2 ^ d3 ^ d4;
    int b[7] = {p1, p2, d1, p3, d2, d3, d4};
    std::string s;
    for (int x : b) s += char('0' + x);
    return s;
}

int sindrome(const std::string& s) {
    int b[8];
    for (int i = 1; i <= 7; i++) b[i] = s[i - 1] - '0';
    int c1 = b[1] ^ b[3] ^ b[5] ^ b[7];   // círculo 1
    int c2 = b[2] ^ b[3] ^ b[6] ^ b[7];   // círculo 2
    int c3 = b[4] ^ b[5] ^ b[6] ^ b[7];   // círculo 3
    return c1 + 2 * c2 + 4 * c3;          // 0 = todo bien; si no, la posición dañada
}

int main() {
    std::string enviado = codificar(1, 0, 1, 1);
    std::cout << "enviado:   " << enviado << "\n";

    std::string recibido = enviado;
    recibido[4] = recibido[4] == '0' ? '1' : '0';   // ruido: se voltea el bit 5
    std::cout << "recibido:  " << recibido << "\n";

    int pos = sindrome(recibido);
    std::cout << "error en el bit " << pos << "\n";

    recibido[pos - 1] = recibido[pos - 1] == '0' ? '1' : '0';
    std::cout << "corregido: " << recibido
              << (recibido == enviado ? "  ✓ igual al original" : "  ✗") << "\n";
}
