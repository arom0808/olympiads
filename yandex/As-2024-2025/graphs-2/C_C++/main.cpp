#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 100;

struct Point {
    ll t, x, y;

    friend istream &operator>>(istream &is, Point &p) {
        is >> p.t;
        p.t *= 60;
        is.ignore();
        is >> p.x;
        p.t += p.x;
        is >> p.x >> p.y;
        return is;
    }

    bool operator<(const Point &rhs) const {
        if (t != rhs.t) return t < rhs.t;
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

ll dist(const Point &a, const Point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ll speed;

ll max_dist_can(const Point &a, const Point &b) {
    ll v1 = speed * std::abs(a.t - b.t);
    return v1 * v1 / (60 * 60);
}

ll n;
Point points[maxn];
vector<ll> g[maxn];
int timer = 0;
int used[maxn], mt[maxn];

bool dfs(int v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto u: g[v]) {
        if (mt[u] == -1) {
            mt[u] = v;
            return true;
        }
    }
    for (auto u: g[v]) {
        if (dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> speed;
    for (ll i = 0; i < n; ++i) cin >> points[i];
    sort(points, points + n);
    for (ll i = 0; i < n; ++i)
        for (ll j = i + 1; j < n; ++j)
            if (dist(points[i], points[j]) <= max_dist_can(points[i], points[j]))
                g[i].push_back(j);
    int ans = 0;
    ++timer;
    for (int i = 0; i < n; ++i) mt[i] = -1;
    for (int i = 0; i < n; ++i) if (dfs(i)) ++ans, ++timer;
    cout << n - ans;
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
