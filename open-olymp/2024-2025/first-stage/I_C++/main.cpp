#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
using ll = long long;
using ld = long double;

constexpr int maxn = 2e5;

struct Point {
    int x, y, dx, dy, c;

    friend istream &operator>>(istream &in, Point &p) {
        return in >> p.x >> p.y >> p.dx >> p.dy >> p.c;
    }
};

int n, T;
Point points[maxn];

ll get_val(int t) {
    ll cmax = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (points[i].c == points[j].c) continue;
            const auto &p1 = points[i], &p2 = points[j];
            ll dx = (0ll + p1.x + p1.dx * t - p2.x - p2.dx * t);
            ll dy = (0ll + p1.y + p1.dy * t - p2.y - p2.dy * t);
            cmax = std::max(cmax, dx * dx + dy * dy);
        }
    }
    return cmax;
}

void solve() {
    cin >> n >> T;
    for (int i = 0; i < n; ++i) cin >> points[i];
    ll ans = 4e18;
    int l = 0, r = T;
    while (r - l >= 3) {
        int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (get_val(m1) < get_val(m2)) r = m2;
        else l = m1;
    }
    for (int t = l; t <= r; ++t) ans = std::min(ans, get_val(t));
    cout << std::sqrt(static_cast<ld>(ans)) << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cout << fixed << setprecision(20);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
