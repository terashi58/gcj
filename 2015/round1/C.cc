#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct Pos {
  long long x, y;
  int operator <(const Pos& b) const {
    return make_pair(x,y) < make_pair(b.x,b.y);
  }
  int operator ==(const Pos& b) const {
    return make_pair(x,y) == make_pair(b.x,b.y);
  }
};

long long cross(const Pos& o, const Pos& a, const Pos& b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int N;
Pos pos[4048];

vector<int> convex_hull(const vector<bool>& use) {
  int n = 0;
  vector<Pos> P;
  for (int i = 0; i < N; ++i) {
    if (use[i]) {
      P.push_back(pos[i]);
      ++n;
    }
  }
  sort(P.begin(), P.end());

  int k = 0;
  vector<Pos> H(2*n);
 
  // Build lower hull
  for (int i = 0; i < n; i++) {
    while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--;
    H[k++] = P[i];
  }
 
  // Build upper hull
  for (int i = n-2, t = k+1; i >= 0; i--) {
    while (k >= 2 && k >= t && cross(H[k-2], H[k-1], P[i]) < 0) k--;
    H[k++] = P[i];
  }

  H.resize(k);
 
  vector<int> R;
  for (const Pos& p : H) {
    R.push_back(find(pos, pos+N, p) - pos);
  }
  return R;
}

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> N;
    for (int i = 0; i < N; ++i) {
      cin >> pos[i].x >> pos[i].y;
    }
    vector<int> ans(N, N);
    for (int t = (1<<N)-1; t >= 0; --t) {
      vector<bool> use(N, false);
      int cut = 0;
      for (int i = 0; i < N; ++i)
	if (t & (1<<i)) {
	  use[i] = true;
	} else {
	  ++cut;
	}
      vector<int> hull = convex_hull(use);
      // cerr << t << ": ";
      // for (int i : hull) cerr << i << ", ";
      // cerr << endl;
      for (int i : hull) {
	if (ans[i] > cut) {
	  ans[i] = min(ans[i], cut);
	}
      }
    }

    cout << "Case #" << iii+1 << ":" << endl;
    for (int a : ans) {
      cout << a << endl;
    }
  }
}
