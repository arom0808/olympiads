#include <algorithm>
#include <iostream>


using namespace std;
using ll = int64_t;
constexpr int maxn = 2e5, inf = 1e9;

struct Point {
    int x, y;

    friend istream &operator>>(istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
};

int n, m;
Point points[maxn];

int solven4() {
    int fx = inf, sx = 0, fy = inf, sy = 0;
    for (int i = 0; i < n; ++i) {
        fx = std::min(fx, points[i].x);
        sx = std::max(fx, points[i].x);
        fy = std::min(fy, points[i].y);
        sy = std::max(sy, points[i].y);
    }
    if ((fy - sy) % 2) return fx;
    if ((fx - sx) % 2) return fx - 1;
    return fx;
}

int solve_gr_seq() {
    int ans = 0;
    int px = 0;
    for (int i = 0; i < n; ++i) {
        if (points[i].y % 2) return ans;
        if ((points[i].x - px) % 2) return points[i].x - 1;
        ans = points[i].x;
        px = points[i].x;
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> points[i];
    if (n == 4) cout << solven4() << "\n";
    else {
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
