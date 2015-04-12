#include <iostream>
#include <algorithm>

using namespace std;

int X, R, C;
int s, S;

bool CanPlace5() {
  // S >= 5
  if (s < 3) return false;
  if (s == 3) {  // S = 5, 10, 15,...
    return S > 5;
  }
  if (s == 4) {  // S = 5, 10, 15,...
    return true;
  }
  return true;
}

bool CanPlace6() {
  // S >= 6
  if (s < 3) return false;
  if (s == 3) {  // S = 6, 8, 10,...
    return false;  // split odd
  }
  if (s == 4) {  // S = 6, 9, 12,...
    return true;
  }
  return true;
}

bool CanPlace() {
  if (s * S % X != 0) return false;
  if (S < X) return false;
  switch (X) {
  case 1: return true;
  case 2: return true;
  case 3: return s > 1;
  case 4: return s > 2;  // split odd
  case 5: return CanPlace5();
  case 6: return CanPlace6();
  default: return false;
  }
}

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> X >> R >> C;
    s = min(R, C);
    S = max(R, C);
    bool ans = !CanPlace();
    cout << "Case #" << iii+1 << ": " << (ans ? "RICHARD" : "GABRIEL") << endl;
  }
}
