// La persona famosa: todos la conocen y ella no conoce a nadie.
// Solo se puede preguntar: "¿A conoce a B?"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

int n;
vector<vector<bool>> conoce;
long long preguntas = 0;

bool pregunta(int a, int b) { preguntas++; return conoce[a][b]; }

// Fuerza bruta: preguntarle a cada uno por cada uno.
int fuerzaBruta() {
  vector<vector<bool>> r(n, vector<bool>(n, false));
  for (int a = 0; a < n; a++)
    for (int b = 0; b < n; b++)
      if (a != b) r[a][b] = pregunta(a, b);
  for (int c = 0; c < n; c++) {
    bool famoso = true;
    for (int o = 0; o < n; o++)
      if (o != c && (r[c][o] || !r[o][c])) famoso = false;
    if (famoso) return c;
  }
  return -1;
}

// Eliminación: cada pregunta descarta a una persona.
int eliminacion() {
  int candidato = 0;
  for (int i = 1; i < n; i++)
    if (pregunta(candidato, i)) candidato = i;   // si conoce a i, no es famoso
  for (int o = 0; o < n; o++) {                  // comprobar al que quedó
    if (o == candidato) continue;
    if (pregunta(candidato, o) || !pregunta(o, candidato)) return -1;
  }
  return candidato;
}

// 999000 -> "999 000"
string miles(long long x) {
  string s = to_string(x);
  for (int i = (int)s.size() - 3; i > 0; i -= 3) s.insert(i, " ");
  return s;
}

int main(int argc, char** argv) {
  n = argc > 1 ? atoi(argv[1]) : 1000;
  int famoso = argc > 2 ? atoi(argv[2]) : n * 7 / 10;
  srand(42);
  conoce.assign(n, vector<bool>(n, false));
  for (int a = 0; a < n; a++)
    for (int b = 0; b < n; b++)
      if (a != b) conoce[a][b] = rand() % 2;
  for (int o = 0; o < n; o++) {
    if (o == famoso) continue;
    conoce[o][famoso] = true;
    conoce[famoso][o] = false;
  }
  preguntas = 0; int r1 = fuerzaBruta(); long long p1 = preguntas;
  preguntas = 0; int r2 = eliminacion(); long long p2 = preguntas;
  printf("%d invitados (famoso: #%d)\n", n, famoso);
  printf("\033[31mfuerza bruta:\033[0m #%d en \033[31m%s\033[0m preguntas\n", r1, miles(p1).c_str());
  printf("\033[32mpor descarte:\033[0m #%d en \033[32m%s\033[0m preguntas\n", r2, miles(p2).c_str());
  return 0;
}
