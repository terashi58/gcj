#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <set>

using namespace std;

int B;
long long N;
int M[1000000];

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> B >> N;
    for (int i = 0; i < B; ++i) {
      cin >> M[i];
    }
    int min_b = min_element(M, M+B) - M;
    long long max_t = M[min_b] * N;
    // cerr << min_b << ", " << max_t << endl;
    long long a = 0, b = max_t;
    int ans = -1000;
    while (a <= b) {
      long long t = (a + b) / 2;
      // cerr << a << ", " << b << ", " << t << endl;
      long long n = 0;
      int eq = 0;
      for (int i = 0; i < B; ++i) {
	n += (t-1) / M[i] + 1;
	if (t % M[i] == 0) ++eq;
      }
      // cerr << t << ", " << n << ", " << eq << endl;
      if (n < N && N <= n+eq) {
	// cerr << t << ", " << n << ", " << eq << endl;
	for (int i = 0; i < B; ++i)
	  if (t % M[i] == 0) {
	    ++n;
	    if (n == N) {
	      ans = i;
	      break;
	    }
	  }
	break;
      }
      if (n < N) {
	a = t+1;
      }	else {
	b = t;
      }
    }
    cout << "Case #" << iii+1 << ": " << ans+1 << endl;
  }
}
