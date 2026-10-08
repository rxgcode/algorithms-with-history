// Algoritmo de Luhn (H. P. Luhn, IBM, patente de 1954).
#include <iostream>
#include <string>

bool luhn(const std::string& n) {
    int suma = 0;
    bool doblar = false;
    for (int i = (int)n.size() - 1; i >= 0; i--) {
        int d = n[i] - '0';
        if (doblar) { d *= 2; if (d > 9) d -= 9; }
        suma += d;
        doblar = !doblar;
    }
    return suma % 10 == 0;
}

int main() {
    // números de prueba públicos, no son tarjetas reales
    std::string casos[] = {
        "4111111111111111",   // válido
        "4111111111111121",   // un número cambiado
        "4111111111111911",   // dos vecinos volteados
        "4111111111091115",   // otro válido, con un "09"
        "4111111111901115",   // "09" volteado a "90": ¡se le escapa!
    };
    for (auto& c : casos)
        std::cout << c << "  ->  " << (luhn(c) ? "✓ pasa" : "✗ error") << "\n";
}
