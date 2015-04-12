#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    int n;
    string shy;
    cin >> n >> shy;
    int ans = 0;
    int stand = 0;
    for (int i = 0; i < shy.size(); ++i) {
      int c = shy[i] - '0';
      if (c == 0) continue;
      if (stand < i) {
	int f = i - stand;
	ans += f;
	stand += f;
      }
      stand += c;
    }
    cout << "Case #" << iii+1 << ": " << ans << endl;
  }
}
