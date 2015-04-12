#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <bitset>
#include <set>
#include <cstring>

using namespace std;

const int DX[] = {1, 0, -1, 0};
const int DY[] = {0, 1, 0, -1};

struct Omino {
  static const int LEN = 8;

  Omino() : w(0), h(0) {}
  Omino(int ww, int hh) : w(ww), h(hh) {}

  bool get(int x, int y) const {
    return (0 <= x && x < w && 0 <= y && y < h) ? cell[x+y*LEN] : false;
  }
  void set(int x, int y) { cell[x+y*LEN] = true; }
  bool settable(int x, int y) const {
    if (!get(x, y)) {
      for (int i = 0; i < 4; ++i) {
	if (get(x + DX[i], y + DY[i])) return true;
      }
    }
    return false;
  }

  Omino expanded(int x, int y) const {
    Omino cp(w + x, h + y);
    cp.cell = cell;
    return cp;
  }

  Omino shifted(int x, int y) const {
    Omino cp(w + x, h + y);
    for (int i = 0; i < w; ++i)
      for (int j = 0; j < h; ++j)
	if (get(i, j))
	  cp.set(i + x, j + y);
    return cp;
  }

  Omino rotated() const {
    Omino cp(h, w);
    for (int i = 0; i < w; ++i)
      for (int j = 0; j < h; ++j)
	if (get(i, j))
	  cp.set(j, w-i-1);
    return cp;
  }

  Omino reflected() const {
    Omino cp(w, h);
    for (int i = 0; i < w; ++i)
      for (int j = 0; j < h; ++j)
	if (get(i, j))
	  cp.set(w-i-1, j);
    return cp;
  }

  Omino normalized() const {
    vector<Omino> cps = listup();
    return *min_element(cps.begin(), cps.end());
  }

  vector<Omino> listup() const {
    vector<Omino> cps(8);
    cps[0] = *this;
    for (int i = 1; i < 4; ++i) cps[i] = cps[i-1].rotated();
    cps[4] = reflected();
    for (int i = 5; i < 8; ++i) cps[i] = cps[i-1].rotated();
    sort(cps.begin(), cps.end());
    cps.erase(unique(cps.begin(), cps.end()), cps.end());
    return cps;
  }

  bool operator ==(const Omino& b) const { return cell == b.cell; }
  bool operator <(const Omino& b) const {
    return cell.to_ullong() < b.cell.to_ullong();
  }
  friend ostream& operator <<(ostream& s, const Omino& o) {
    for (int y = 0; y < o.h; ++y) {
      for (int x = 0; x < o.w; ++x) {
	s << (o.get(x, y) ? '*' : '.');
      }
      s << endl;
    }
    return s;
  }

  static Omino Single() {
    Omino single(1, 1);
    single.set(0, 0);
    return single;
  }

  int w, h;
  bitset<LEN*LEN> cell;
};

const int MAX_SIZE = 6;
set<Omino> piece[MAX_SIZE + 1];

void Extend(int size) {
  for (const Omino& base : piece[size]) {
    for (int x = -1; x <= base.w; ++x)
      for (int y = -1; y <= base.h; ++y)
	if (base.settable(x, y)) {
	  Omino ex = base;
	  int dx = 0, dy = 0;
	  if (x == ex.w) {
	    ex = ex.expanded(1, 0);
	  } else if (x == -1) {
	    ex = ex.shifted(1, 0);
	    dx = 1;
	  }
	  if (y == ex.h) {
	    ex = ex.expanded(0, 1);
	  } else if (y == -1) {
	    ex = ex.shifted(0, 1);
	    dy = 1;
	  }
	  ex.set(x + dx, y + dy);
	  piece[size+1].insert(ex.normalized());
	}
  }
}

void Init() {
  piece[1].insert(Omino::Single());
  for (int i = 1; i < MAX_SIZE; ++i) {
    Extend(i);
  }
  // for (int i = 1; i <= MAX_SIZE; ++i) {
  //   cerr << "SIZE: " << i << ", num: " << piece[i].size() << endl;
  //   for (const Omino& p : piece[i]) {
  //     cerr << p << endl;
  //   }
  // }
}

int X, R, C;
bool field[32][32];

void FillPieace(const Omino& p, int dx, int dy) {
  memset(field, 0, sizeof(field));
  for (int x = 0; x < p.w; ++x)
    for (int y = 0; y < p.h; ++y)
      if (p.get(x, y))
	field[x + dx][y + dy] = -1;
}

int Count(int px, int py, int color) {
  list<pair<int, int>> up;
  up.emplace_back(px, py);
  int cnt = 0;
  while (!up.empty()) {
    int x = up.back().first;
    int y = up.back().second;
    up.pop_back();
    if (!(0 <= x && x < R && 0 <= y && y < C && field[x][y] == 0)) continue;
    field[x][y] = color;
    ++cnt;
    for (int i = 0; i < 4; ++i)
      up.emplace_back(x+DX[i], y+DY[i]);
  }
  return cnt;
}

bool Check() {
  int color = 1;
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j)
      if (field[i][j] == 0) {
	if (Count(i, j, color++) % X != 0) return false;
      }
  return true;
}

bool CanPlaceAPieace(const Omino& p) {
  int dw = R - p.w + 1;
  int dh = C - p.h + 1;
  for (int dx = 0; dx < dw; ++dx) {
    for (int dy = 0; dy < dh; ++dy) {
      FillPieace(p, dx, dy);
      if (Check()) return true;
    }
  }
  return false;
}

bool CanPlace() {
  if (X > MAX_SIZE) return false;
  for (const Omino& base : piece[X]) {
    vector<Omino> cps = base.listup();
    bool placed = false;
    for (const Omino& p : cps) {
      if (CanPlaceAPieace(p)) {
	placed = true;
	break;
      }
    }
    if (!placed) {
      // cerr << base;
      return false;
    }
  }
  return true;
}

int main() {
  Init();
  int nnn;
  cin >> nnn;
  for (int iii = 0; iii < nnn; ++iii) {
    cin >> X >> R >> C;
    bool ans = !CanPlace();
    cout << "Case #" << iii+1 << ": " << (ans ? "RICHARD" : "GABRIEL") << endl;
  }
}
