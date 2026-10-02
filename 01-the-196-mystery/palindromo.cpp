// Invertir y sumar con long long: funciona... hasta que el número ya no cabe.
#include <iostream>
using namespace std;

long long invertir(long long n) {
    long long r = 0;
    while (n > 0) { r = r * 10 + n % 10; n /= 10; }
    return r;
}

bool esPalindromo(long long n) { return n == invertir(n); }

int main(int argc, char* argv[]) {
    long long n = atoll(argv[1]);
    for (int paso = 1; paso <= 44; paso++) {
        n = n + invertir(n);
        cout << "paso " << paso << ": " << (n < 0 ? "\033[31m" : "") << n << "\033[0m\n";
        if (esPalindromo(n)) { cout << "\033[32m¡palíndromo en " << paso << " pasos!\033[0m\n"; return 0; }
    }
}
