// Intercalado (interleaving): por qué un rayón largo no destruye ningún bloque entero.
// Simula 28 bloques de 28 bytes. Sin intercalar, un rayón de 56 bytes seguidos borra 2 bloques completos.
// Intercalando (el byte i del bloque j se graba en la posición i·28 + j), el mismo rayón toca solo 2 bytes de cada bloque.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char** argv) {
    const int B = 28, L = 28;                      // B bloques de L bytes (como las palabras C2 del CD)
    int rayon = argc > 1 ? atoi(argv[1]) : 56;     // bytes seguidos que borra el rayón
    int ini = 300;
    auto cuenta = [&](bool inter) {
        vector<int> perdidos(B, 0);
        for (int p = ini; p < ini + rayon; p++) {
            int bloque = inter ? p % B : p / L;    // ¿a qué bloque pertenece el byte grabado en la posición p?
            if (bloque < B) perdidos[bloque]++;
        }
        return perdidos;
    };
    for (bool inter : {false, true}) {
        vector<int> v = cuenta(inter);
        int peor = *max_element(v.begin(), v.end()), tocados = count_if(v.begin(), v.end(), [](int x) { return x > 0; });
        cout << (inter ? "\033[1mCON intercalado:\033[0m " : "\033[1mSIN intercalar:\033[0m  ") << "rayón de " << rayon << " bytes → toca " << tocados << " bloques\n"
             << "    el peor pierde " << peor << " de " << L << " bytes"
             << (peor <= 4 ? "  \033[32m✓ reparable · límite 4\033[0m" : "  \033[31m✗ irreparable\033[0m") << "\n";
    }
}
