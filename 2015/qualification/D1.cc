#include <iostream>
#include <algorithm>

using namespace std;

int X, R, C;
int m, M;

bool CanPlace() {
  if (X >= 7) return false;
  if (m * M % X != 0) return false;
  if (M < X) return false;
  if (m > X-2) return true;
  if (X == 5 && m == 3 && M > 5) return true;
  if (X == 6 && m > 3) return true;
  return false;
}

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> X >> R >> C;
    m = min(R, C);
    M = max(R, C);
    bool ans = !CanPlace();
    cout << "Case #" << iii+1 << ": " << (ans ? "RICHARD" : "GABRIEL") << endl;
  }
}
