// Prueba aleatoria: ambas soluciones deben coincidir (con y sin famoso).
#define main main_famoso
#include "famoso.cpp"
#undef main
int main() {
  int ok = 0, total = 0;
  for (int t = 0; t < 5000; t++) {
    srand(t);
    n = 1 + rand() % 12;
    conoce.assign(n, vector<bool>(n, false));
    for (int a = 0; a < n; a++) for (int b = 0; b < n; b++)
      if (a != b) conoce[a][b] = rand() % 2;
    if (rand() % 2) { int f = rand() % n;
      for (int o = 0; o < n; o++) if (o != f) { conoce[o][f] = true; conoce[f][o] = false; } }
    preguntas = 0; int e = eliminacion();
    bool cota = preguntas <= 3LL * (n - 1);
    total++; if (fuerzaBruta() == e && cota) ok++;
  }
  printf("pruebas: %d/%d coinciden (y eliminacion <= 3(n-1) preguntas)\n", ok, total);
}
