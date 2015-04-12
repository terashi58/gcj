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

int Char2Code(char c) {
  switch (c) {
  case 'i': return I;
  case 'j': return J;
  case 'k': return K;
  default: return -10000;
  }
}

void Str2Code(string& str) {
  for (int i = 0; i < str.size(); ++i) {
    str[i] = Char2Code(str[i]);
  }
}

int FindFromHead(const string& pat, int target) {
  int cur = 1;
  for (int i = 0; i < pat.size(); ++i) {
    int sign = 1;
    if (cur < 0) { sign *= -1; cur *= -1; }
    cur = MAT[cur][pat[i]] * sign;
    if (cur == target) return i + 1;
  }
  return -1;
}

int FindFromTail(const string& pat, int target) {
  int cur = 1;
  for (int i = 0; i < pat.size(); ++i) {
    int sign = 1;
    if (cur < 0) { sign *= -1; cur *= -1; }
    cur = MAT[pat[pat.size()-i-1]][cur] * sign;
    if (cur == target) return i+1;
  }
  return -1;
}

int Multiply(const string& pat) {
  int cur = 1;
  for (int i = 0; i < pat.size(); ++i) {
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
  string ijk = "ijk";
  Str2Code(ijk);
  int expected = Multiply(ijk);
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> L >> X >> pat;
    Str2Code(pat);
    int x = X < 16 ? X : 12 + X % 4;
    string full;
    for (int i = 0; i < x; ++i) full += pat;
    bool ans = false;
    // cerr << Multiply(full) << endl;
    if (Multiply(full) == expected) {
      int p = FindFromHead(full, I);
      int q = FindFromTail(full, K);
      // cerr << p << ", " << q << endl;
      if (p > 0 && q > 0 && p + q < full.size()) {
	ans = true;
      }
    }
    cout << "Case #" << iii+1 << ": " << (ans ? "YES" : "NO") << endl;
  }
}
