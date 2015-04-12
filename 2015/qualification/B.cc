#include <iostream>
#include <algorithm>

using namespace std;

int D;
int P[1024];

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> D;
    for (int i = 0; i < D; ++i) {
      cin >> P[i];
    }
    int ans = 1000;
    for (int s = 1; s <= 1000; ++s) {
      int sp = 0;
      for (int i = 0; i < D; ++i) {
	sp += (P[i]-1) / s;
      }
      ans = min(ans, sp + s);
    }
    cout << "Case #" << iii+1 << ": " << ans << endl;
  }
}
