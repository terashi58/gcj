#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int N;
int m[20000];

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> N;
    for (int i = 0; i < N; ++i)
      cin >> m[i];
    int ans1 = 0, max_d = 0, ans2 = 0;
    for (int i = 1; i < N; ++i) {
      int prev = m[i-1];
      int cur = m[i];
      if (cur < prev) {
	ans1 += prev - cur;
	max_d = max(max_d, prev-cur);
      }
    }
    for (int i = 1; i < N; ++i) {
      int prev = m[i-1];
      int cur = m[i];
      if (prev - max_d > 0) {
	ans2 += max_d;
      } else {
	ans2 += prev;
      }
    }
    cout << "Case #" << iii+1 << ": " << ans1 << " " << ans2 << endl;
  }
}
