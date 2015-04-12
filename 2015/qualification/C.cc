#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum {
  I = 2,
  J = 3,
  K = 4,
};

int MAT[5][5] = {
  {},
  { 0, 1, I, J, K },
  { 0, I, -1, K, -J },
  { 0, J, -K, -1, I },
  { 0, K, J, -I, -1},
};

int Find(const string& pat, int pos, int target) {
  int cur = 1;
  for (int i = pos; i < pat.size(); ++i) {
    int sign = 1;
    if (cur < 0) { sign *= -1; cur *= -1; }
    cur = MAT[cur][pat[i]] * sign;
    if (cur == target) return i + 1;
  }
  return -1;
}

int Multiply(const string& pat, int pos) {
  int cur = 1;
  for (int i = pos; i < pat.size(); ++i) {
    int sign = 1;
    if (cur < 0) { sign *= -1; cur *= -1; }
    cur = MAT[cur][pat[i]] * sign;
  }
  return cur;
}

int L;
long long int X;
string pat;

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> L >> X >> pat;
    for (int i = 0; i < pat.size(); ++i) {
      pat[i] = pat[i] - 'i' + I;
    }
    int x = X < 16 ? X : 12 + X % 4;
    string full;
    for (int i = 0; i < x; ++i) full += pat;
    bool ans = false;
    int p = Find(full, 0, I);
    if (p > 0) {
      int q = Find(full, p, J);
      // cerr << p << ", " << q << endl;
      if (q > 0 && Multiply(full, q) == K) {
	ans = true;
      }
    }
    cout << "Case #" << iii+1 << ": " << (ans ? "YES" : "NO") << endl;
  }
}
