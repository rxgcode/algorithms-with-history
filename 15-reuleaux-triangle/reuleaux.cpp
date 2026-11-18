// El triángulo de Reuleaux: construcción y ancho constante (Algoritmos con historia, regCode).
// Compilar: g++ -std=c++17 -O2 -o reuleaux reuleaux.cpp
// Uso:  ./reuleaux            -> mide el ancho en 1000 direcciones y la altura al rodar
//       ./reuleaux --rueda N  -> tabla de N poses de un rodillo que rueda sobre el suelo (para dibujarlo)
//       ./reuleaux --cuadrado N -> tabla de N poses del triángulo girando dentro de un cuadrado (broca de Watts)
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>

struct P { double x, y; };
const double PI = std::acos(-1.0);
const double L = 1.0;                 // lado del triángulo = ancho de la figura
const double R = L / std::sqrt(3.0);  // distancia del centro a cada vértice

// Vértices del triángulo equilátero, con el centro en el origen: A arriba (90°), B (210°), C (330°).
std::vector<P> vertices() {
    std::vector<P> v;
    for (int k = 0; k < 3; k++) {
        double a = PI / 2 + k * 2 * PI / 3;
        v.push_back({R * std::cos(a), R * std::sin(a)});
    }
    return v;
}

// Ángulo normalizado a [0, 2π).
double norm(double a) { a = std::fmod(a, 2 * PI); return a < 0 ? a + 2 * PI : a; }

// Construcción: tres arcos de radio L, cada uno con centro en un vértice y que une los otros dos.
// El arco con centro en V cubre las direcciones (vistas desde V) entre V→W1 y V→W2, que abarcan 60°.
// Punto de contacto con una recta de dirección normal u (la recta toca la figura "por el lado u").
P contacto(double ang, bool reuleaux) {
    auto V = vertices();
    P u{std::cos(ang), std::sin(ang)};
    P best = V[0];
    double hb = -1e300;
    for (int i = 0; i < 3; i++) {                       // los vértices siempre son candidatos
        double h = V[i].x * u.x + V[i].y * u.y;
        if (h > hb) { hb = h; best = V[i]; }
    }
    if (!reuleaux) return best;
    for (int i = 0; i < 3; i++) {                       // el arco con centro en V[i]
        const P& W1 = V[(i + 1) % 3]; const P& W2 = V[(i + 2) % 3];
        double a1 = std::atan2(W1.y - V[i].y, W1.x - V[i].x), a2 = std::atan2(W2.y - V[i].y, W2.x - V[i].x);
        double lo = std::fmin(norm(a1), norm(a2)), hi = std::fmax(norm(a1), norm(a2));
        if (hi - lo > PI) std::swap(lo, hi);            // el arco de 60° que cruza el 0°
        double a = norm(ang);
        bool dentro = lo < hi ? (a >= lo && a <= hi) : (a >= lo || a <= hi);
        if (!dentro) continue;
        P p{V[i].x + L * u.x, V[i].y + L * u.y};      // el punto del arco cuya normal es u
        double h = p.x * u.x + p.y * u.y;
        if (h > hb) { hb = h; best = p; }
    }
    return best;
}

// Ancho en la dirección ang: distancia entre las dos rectas paralelas (normales ±u) que tocan la figura.
double ancho(double ang, bool reuleaux) {
    P u{std::cos(ang), std::sin(ang)};
    P a = contacto(ang, reuleaux), b = contacto(ang + PI, reuleaux);
    return (a.x - b.x) * u.x + (a.y - b.y) * u.y;
}

// Rodar sin resbalar hacia la derecha: tras girar phi (horario), la dirección "abajo" del suelo vista desde la figura
// es 270° + phi. El suelo avanza L·dphi mientras el contacto está en un arco y 0 mientras pivota sobre un vértice.
struct Pose { double phi, s, cx, cy; };
std::vector<Pose> rodar(int n) {
    std::vector<Pose> out;
    double s = 0, prev = 0;
    for (int k = 0; k <= n; k++) {
        double phi = 2 * PI * k / n;
        if (k > 0) {                                     // longitud de arco recorrida entre prev y phi (exacta por tramos)
            int m = 64;
            for (int j = 0; j < m; j++) {
                double a = 1.5 * PI + prev + (phi - prev) * (j + 0.5) / m;
                P c = contacto(a, true); auto V = vertices();
                bool vert = false;
                for (auto& v : V) if (std::hypot(c.x - v.x, c.y - v.y) < 1e-12) vert = true;
                if (!vert) s += L * (phi - prev) / m;
            }
        }
        P c = contacto(1.5 * PI + phi, true);            // punto de la figura que toca el suelo
        double cs = std::cos(-phi), sn = std::sin(-phi);  // giro horario de la figura
        P w{c.x * cs - c.y * sn, c.x * sn + c.y * cs};
        out.push_back({phi, s, s - w.x, -w.y});         // el centro, con el contacto en (s, 0)
        prev = phi;
    }
    return out;
}

int main(int argc, char** argv) {
    if (argc == 3 && !std::strcmp(argv[1], "--rueda")) {
        for (auto& p : rodar(std::atoi(argv[2]))) std::printf("%.9f %.9f %.9f %.9f\n", p.phi, p.s, p.cx, p.cy);
        return 0;
    }
    if (argc == 3 && !std::strcmp(argv[1], "--cuadrado")) {     // dentro del cuadrado [0,L]×[0,L], tocando los 4 lados
        int n = std::atoi(argv[2]);
        for (int k = 0; k <= n; k++) {
            double th = 2 * PI * k / n, cs = std::cos(th), sn = std::sin(th);
            // tras girar th (antihorario), la recta "por la izquierda" tiene normal 180° - th vista desde la figura
            P l = contacto(PI - th, true), d = contacto(1.5 * PI - th, true);
            double cx = -(l.x * cs - l.y * sn), cy = -(d.x * sn + d.y * cs);
            std::printf("%.9f %.9f %.9f\n", th, cx, cy);
        }
        return 0;
    }
    const int N = 1000;
    double tmin = 1e9, tmax = -1e9, rmin = 1e9, rmax = -1e9, peor = 0;
    int ok = 0;
    for (int k = 0; k < N; k++) {
        double a = PI * k / N;                           // 1000 direcciones entre 0° y 180°
        double t = ancho(a, false), r = ancho(a, true);
        tmin = std::fmin(tmin, t); tmax = std::fmax(tmax, t);
        rmin = std::fmin(rmin, r); rmax = std::fmax(rmax, r);
        peor = std::fmax(peor, std::fabs(r - L));
        if (std::fabs(r - L) < 1e-12) ok++;
    }
    double cmin = 1e9, cmax = -1e9, top = 0;
    for (auto& p : rodar(3600)) {
        cmin = std::fmin(cmin, p.cy); cmax = std::fmax(cmax, p.cy);
        top = std::fmax(top, std::fabs(ancho(PI / 2 + p.phi, true) - L));   // tabla apoyada arriba
    }
    std::printf("lado del triángulo = %.0f\n", L);
    std::printf("ancho entre 2 rectas paralelas, %d direcciones:\n", N);
    std::printf("  triángulo normal: de %.6f a %.6f\n", tmin, tmax);
    std::printf("  Reuleaux:         de %.12f a %.12f\n", rmin, rmax);
    std::printf("  |ancho - lado| < 1e-12 en %d de %d %s\n", ok, N, ok == N ? "✓" : "✗");
    std::printf("al rodar por el suelo:\n");
    std::printf("  altura del centro: de %.4f a %.4f\n", cmin, cmax);
    std::printf("  altura de la tabla: %.12f siempre\n", L + top);
    return 0;
}
