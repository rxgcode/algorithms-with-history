// Reed-Solomon sobre GF(256), el mismo cuerpo que usan los códigos QR (polinomio 0x11D).
// Codifica un mensaje añadiendo P bytes de paridad y lo repara:
//   · borrados (sabemos qué posiciones se perdieron): hasta P bytes
//   · errores (no sabemos dónde están): hasta P/2 bytes
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// ---- aritmética en GF(256): los bytes se suman con XOR y se multiplican con tablas de logaritmos
unsigned char EXP[512], LOG[256];
void tablas() {
    int x = 1;
    for (int i = 0; i < 255; i++) {
        EXP[i] = x; LOG[x] = i;
        x <<= 1; if (x & 0x100) x ^= 0x11D;        // módulo el polinomio primitivo del estándar QR
    }
    for (int i = 255; i < 512; i++) EXP[i] = EXP[i - 255];
}
unsigned char mul(unsigned char a, unsigned char b) { return (a && b) ? EXP[LOG[a] + LOG[b]] : 0; }
unsigned char inv(unsigned char a) { return EXP[255 - LOG[a]]; }
unsigned char div_(unsigned char a, unsigned char b) { return a ? EXP[(LOG[a] + 255 - LOG[b]) % 255] : 0; }

typedef vector<unsigned char> Poly;               // coeficientes de mayor a menor grado
Poly pmul(const Poly& a, const Poly& b) {
    Poly r(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); i++) for (size_t j = 0; j < b.size(); j++) r[i + j] ^= mul(a[i], b[j]);
    return r;
}
unsigned char peval(const Poly& p, unsigned char x) {   // Horner
    unsigned char y = 0;
    for (unsigned char c : p) y = mul(y, x) ^ c;
    return y;
}

// ---- codificar: generador g(x) = (x-α^0)(x-α^1)…(x-α^(P-1)); paridad = resto de m(x)·x^P entre g(x)
Poly generador(int P) {
    Poly g = {1};
    for (int i = 0; i < P; i++) g = pmul(g, Poly{1, EXP[i]});
    return g;
}
vector<unsigned char> codificar(const vector<unsigned char>& msg, int P) {
    Poly g = generador(P);
    vector<unsigned char> out(msg.begin(), msg.end()); out.resize(msg.size() + P, 0);
    for (size_t i = 0; i < msg.size(); i++) {
        unsigned char c = out[i];
        if (c) for (size_t j = 1; j < g.size(); j++) out[i + j] ^= mul(g[j], c);
    }
    for (size_t i = 0; i < msg.size(); i++) out[i] = msg[i];   // sistemático: mensaje + paridad
    return out;
}

// ---- decodificar (Berlekamp–Massey + Chien + Forney), con soporte de borrados conocidos
vector<unsigned char> sindromes(const vector<unsigned char>& r, int P) {
    vector<unsigned char> s(P);
    for (int i = 0; i < P; i++) s[i] = peval(Poly(r.begin(), r.end()), EXP[i]);
    return s;
}
// posiciones medidas desde el final (x = α^pos): pos = n-1-índice
bool corregir(vector<unsigned char>& r, int P, const vector<int>& borrados, int& nerr) {
    int n = r.size();
    vector<unsigned char> S = sindromes(r, P);
    bool limpio = true; for (auto s : S) if (s) limpio = false;
    nerr = 0; if (limpio) return true;
    // localizador de borrados Γ(x) = ∏(1 - α^pos x)
    Poly G = {1};                                   // menor a mayor grado aquí
    for (int idx : borrados) { unsigned char xj = EXP[(n - 1 - idx) % 255]; Poly t(G.size() + 1, 0);
        for (size_t i = 0; i < G.size(); i++) { t[i] ^= G[i]; t[i + 1] ^= mul(G[i], xj); } G = t; }
    int e = borrados.size();
    // síndromes modificados (Forney): T = S·Γ
    vector<unsigned char> T(P, 0);
    for (int i = 0; i < P; i++) for (size_t j = 0; j < G.size() && (int)(i - j) >= 0; j++) T[i] ^= mul(S[i - j], G[j]);
    // Berlekamp–Massey sobre T[e..] para el localizador de errores Λ
    Poly L = {1}, B = {1}; int Ld = 0, m = 1; unsigned char b = 1;
    for (int k = e; k < P; k++) {
        unsigned char d = T[k];
        for (int i = 1; i <= Ld; i++) if (i < (int)L.size() && k - i >= 0) d ^= mul(L[i], T[k - i]);
        if (d == 0) { m++; continue; }
        Poly Tn = L; unsigned char coef = div_(d, b);
        if ((int)L.size() < (int)B.size() + m) L.resize(B.size() + m, 0);
        for (size_t i = 0; i < B.size(); i++) L[i + m] ^= mul(coef, B[i]);
        if (2 * Ld <= k - e) { Ld = k - e + 1 - Ld; B = Tn; b = d; m = 1; } else m++;
    }
    L.resize(Ld + 1);
    // localizador total Ψ = Λ·Γ ; raíces por búsqueda de Chien
    Poly Psi(L.size() + G.size() - 1, 0);
    for (size_t i = 0; i < L.size(); i++) for (size_t j = 0; j < G.size(); j++) Psi[i + j] ^= mul(L[i], G[j]);
    vector<int> pos;
    for (int i = 0; i < n; i++) { unsigned char xinv = EXP[(255 - (n - 1 - i) % 255) % 255], y = 0;
        for (int k = Psi.size() - 1; k >= 0; k--) y = mul(y, xinv) ^ Psi[k];
        if (y == 0) pos.push_back(i); }
    if ((int)pos.size() != (int)Psi.size() - 1) return false;   // más errores de los que se pueden corregir
    // magnitudes (Forney): Ω = S·Ψ mod x^P ; e_j = x_j·Ω(x_j^-1) / Ψ'(x_j^-1)   (fcr = 0)
    Poly Om(P, 0);
    for (int i = 0; i < P; i++) for (size_t j = 0; j < Psi.size() && (int)(i - j) >= 0; j++) Om[i] ^= mul(S[i - j], Psi[j]);
    for (int idx : pos) {
        unsigned char xj = EXP[(n - 1 - idx) % 255], xinv = inv(xj), num = 0, den = 0;
        for (int k = P - 1; k >= 0; k--) num = mul(num, xinv) ^ Om[k];
        for (size_t k = 1; k < Psi.size(); k += 2) { unsigned char t = Psi[k]; for (size_t q = 1; q < k; q++) t = mul(t, xinv); den ^= t; }  // Ψ'(x) (derivada formal)
        if (!den) return false;
        r[idx] ^= div_(mul(xj, num), den);
    }
    nerr = pos.size();
    return true;
}

string texto(const vector<unsigned char>& v, size_t n) { string s; for (size_t i = 0; i < n; i++) s += (v[i] >= 32 && v[i] < 127) ? char(v[i]) : '?'; return s; }
void hexdump(const vector<unsigned char>& v, size_t k) { for (size_t i = 0; i < v.size(); i++) { if (i == k) cout << "| "; printf("%02X ", v[i]); } cout << "\n"; }

int main(int argc, char** argv) {
    tablas();
    if (argc > 1 && string(argv[1]) == "--prueba") {        // 2000 mensajes al azar con P/2+1 errores: ¿lo detecta o entrega basura sin avisar?
        int P = 10, det = 0, mal = 0, T = 2000; srand(1);
        for (int t = 0; t < T; t++) {
            vector<unsigned char> msg(22); for (auto& c : msg) c = rand() % 256;
            vector<unsigned char> cw = codificar(msg, P), r = cw; vector<int> toc;
            for (int i = 0; i < P / 2 + 1; i++) { int q; do q = rand() % cw.size(); while (count(toc.begin(), toc.end(), q)); toc.push_back(q); r[q] ^= 1 + rand() % 255; }
            int ne; bool ok = corregir(r, P, {}, ne);
            if (!ok) det++; else if (r != cw) mal++; else det++;
        }
        cout << "con " << P / 2 + 1 << " errores (uno más del límite), " << T << " mensajes:\n  detectado " << det << "/" << T << " · corregido mal sin avisar " << mal << "/" << T << "\n";
        return 0;
    }
    string m = argc > 1 ? argv[1] : "Este mensaje sobrevive";
    int P = argc > 2 ? atoi(argv[2]) : 10;
    vector<unsigned char> msg(m.begin(), m.end()), cw = codificar(msg, P);
    size_t k = msg.size();
    cout << "\033[1mmensaje\033[0m  (" << k << " bytes): " << m << "\n";
    cout << "\033[1mparidad\033[0m  (" << P << " bytes): \033[35m"; for (size_t i = k; i < cw.size(); i++) printf("%02X ", cw[i]); cout << "\033[0m\n\n";

    // 1) un rayón: P bytes seguidos BORRADOS (sabemos dónde)
    vector<unsigned char> r = cw; vector<int> borr; int ini = 3;
    for (int i = 0; i < P; i++) { r[ini + i] = 0; borr.push_back(ini + i); }
    cout << "\033[1mrayón:\033[0m se pierden " << P << " bytes seguidos (posiciones conocidas)\n   leído:    " << texto(r, k) << "\n";
    int ne; bool ok = corregir(r, P, borr, ne);
    cout << "   \033[2mreparado:\033[0m " << texto(r, k) << (ok && r == cw ? "  \033[32m✓ igual al original\033[0m" : "  \033[31m✗\033[0m") << "\n\n";

    // 2) errores en posiciones DESCONOCIDAS: hasta P/2
    r = cw; srand(7); vector<int> tocados;
    for (int i = 0; i < P / 2; i++) { int p; do p = rand() % cw.size(); while (count(tocados.begin(), tocados.end(), p)); tocados.push_back(p); r[p] ^= 0x5A; }
    cout << "\033[1mruido:\033[0m " << P / 2 << " bytes cambiados sin saber cuáles\n   leído:    " << texto(r, k) << "\n";
    ok = corregir(r, P, {}, ne);
    cout << "   \033[2mreparado:\033[0m " << texto(r, k) << (ok && r == cw ? "  \033[32m✓ " + to_string(ne) + " errores corregidos\033[0m" : "  \033[31m✗\033[0m") << "\n\n";

    // 3) uno más de la cuenta: P/2 + 1 errores → ya no alcanza
    r = cw; tocados.clear();
    for (int i = 0; i < P / 2 + 1; i++) { int p; do p = rand() % cw.size(); while (count(tocados.begin(), tocados.end(), p)); tocados.push_back(p); r[p] ^= 0x5A; }
    cout << "\033[1mruido:\033[0m " << P / 2 + 1 << " bytes cambiados\n   leído:    " << texto(r, k) << "\n";
    ok = corregir(r, P, {}, ne);
    cout << "   \033[2mreparado:\033[0m " << (ok && r == cw ? texto(r, k) + "  \033[32m✓\033[0m" : "\033[31m✗ no se puede: demasiados errores\033[0m") << "\n";
}
