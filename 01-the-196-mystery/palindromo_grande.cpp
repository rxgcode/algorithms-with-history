// Invertir y sumar dígito a dígito: el número vive en un string, sin límite de tamaño.
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string sumarConReverso(const string& n) {
    string r(n.rbegin(), n.rend()), s;
    int acarreo = 0;
    for (int i = n.size() - 1; i >= 0; i--) {
        int d = (n[i] - '0') + (r[i] - '0') + acarreo;
        s += char('0' + d % 10);
        acarreo = d / 10;
    }
    if (acarreo) s += '1';
    reverse(s.begin(), s.end());
    return s;
}

bool esPalindromo(const string& n) { return equal(n.begin(), n.begin() + n.size() / 2, n.rbegin()); }

int main(int argc, char* argv[]) {
    string n = argv[1];
    long pasos = atol(argv[2]);
    for (long paso = 1; paso <= pasos; paso++) {
        n = sumarConReverso(n);
        if (esPalindromo(n)) { cout << "\033[32m¡palíndromo en " << paso << " pasos! (" << n.size() << " dígitos)\033[0m\n"; return 0; }
        if (paso % 10000 == 0) cout << "paso " << paso << ": " << n.size() << " dígitos\033[90m… nada\033[0m\n";
    }
    cout << "después de " << pasos << " pasos: " << n.size() << " dígitos\n\033[31mningún palíndromo\033[0m\n";
}
