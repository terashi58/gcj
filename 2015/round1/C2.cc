#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>

using namespace std;

const double PI = acos(-1);
const double EPS = 1e-8;

struct Real {
  long long x, y;
  double theta;

  Real(int xx, int yy) : x(xx), y(yy), theta(atan2(y, x)) {}
  bool operator <(const Real& b) const {
    if (abs(b.theta - theta) < EPS) return false;
    return theta < b.theta;
  }
};

struct Pos {
  Pos() {}
  Pos(int xx, int yy) : x(xx), y(yy) {}

  long long x, y;

  bool operator <(const Pos& b) const {
    return make_pair(x,y) < make_pair(b.x,b.y);
  }
  bool operator ==(const Pos& b) const {
    return make_pair(x,y) == make_pair(b.x,b.y);
  }
};

int N;
Pos pos[4048];
int ans[4048];

void Solve() {
  if (N <= 3) {
    fill_n(ans, N, 0);
    return;
  }
  for (int i = 0; i < N; ++i) {
    Pos p0 = pos[i];
    map<Real, vector<int>> upper, lower;
    int u = 0, l = 0;
    set<Real> args;
    for (int j = 0; j < N; ++j) {
      if (i == j) continue;
      Pos d(pos[j].x - p0.x, pos[j].y - p0.y);
      if (d.y > 0 || (d.y == 0 && d.x > 0)) {
	upper[Real(d.x, d.y)].push_back(j);
	args.insert(Real(d.x, d.y));
	++u;
      } else {
	lower[Real(-d.x, -d.y)].push_back(j);
	args.insert(Real(-d.x, -d.y));
	++l;
      }
    }

    for (const auto& r : args) {
      const vector<int>& up = upper[r];
      const vector<int>& low = lower[r];
      u -= up.size();
      l -= low.size();
      for (int j : up) {
	ans[j] = min(ans[j], min(u, l));
      }
      for (int j : low) {
	ans[j] = min(ans[j], min(u, l));
      }
      u += low.size();
      l += up.size();
    }
  }
}

int main() {
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> N;
    for (int i = 0; i < N; ++i) {
      cin >> pos[i].x >> pos[i].y;
      ans[i] = N;
    }
    Solve();

    cout << "Case #" << iii+1 << ":" << endl;
    for (int i = 0; i < N; ++i) {
      cout << ans[i] << endl;
    }
  }
}
