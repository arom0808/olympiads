#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    int64_t t;
    while (b) {
        t = a;
        a = b;
        b = t % b;
    }
    return a;
}

class Fract {
public:
    int64_t a, b;

    void simplify() {
        int64_t gg = gcd(a, b);
        a /= gg;
        b /= gg;
    }

    bool operator<(const Fract &other) const { return a * other.b < other.a * b; }

    bool operator>(const Fract &other) const { return a * other.b > other.a * b; }

    bool operator==(const Fract &other) const { return a == other.a && b == other.b; }

    Fract(int64_t a, int64_t b) : a(a), b(b) { simplify(); }

    Fract() : Fract(0, 1) {}

    Fract &operator=(const Fract &other) = default;
};

struct Obj {
    int64_t x = 0, y = 0, v = 0;
};

struct Target {
    int64_t a = 0, b = 0;
};

struct Way {
    Fract time;
    int64_t l = 0, r = 0;
};

inline int64_t sq(int64_t v) { return v * v; }

bool dfs(const vector<vector<pair<Fract, int64_t>>> &g, vector<int64_t> &rm, vector<int64_t> &used, int64_t timer,
         int64_t v, Fract max_time) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto [t, u]: g[v]) {
        if (t > max_time) continue;
        if (rm[u] == -1) {
            rm[u] = v;
            return true;
        }
    }
    for (auto [t, u]: g[v]) {
        if (t > max_time) continue;
        if (dfs(g, rm, used, timer, rm[u], max_time)) {
            rm[u] = v;
            return true;
        }
    }
    return false;
}

bool is_ok(const vector<vector<pair<Fract, int64_t>>> &g, vector<int64_t> &rm, vector<int64_t> &used, int64_t &timer,
           Fract max_time) {
    fill(rm.begin(), rm.end(), -1);
    ++timer;
    for (int64_t v = 0; v < g.size(); ++v) {
        if (dfs(g, rm, used, timer, v, max_time)) ++timer;
        else return false;
    }
    return true;
}

int main() {
    int64_t n;
    cin >> n;
    vector<Obj> objs(n);
    for (auto &[x, y, v]: objs) cin >> x >> y >> v;
    vector<Target> targets(n);
    for (auto &[a, b]: targets) cin >> a >> b;
    vector<vector<pair<Fract, int64_t>>> g(n, vector<pair<Fract, int64_t>>(n));
    vector<Fract> times(n * n);
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < n; ++j) {
            g[i][j] = {Fract(sq(objs[i].x - targets[j].a) + sq(objs[i].y - targets[j].b), sq(objs[i].v)), j};
            times[i * n + j] = g[i][j].first;
        }
    }
    sort(times.begin(), times.end());
    times.erase(unique(times.begin(), times.end()), times.end());
    vector<int64_t> rm(n, -1), used(n, -1);
    int64_t l = 0, r = times.size() - 1, timer = 0;
    while (l != r) {
        Fract m = times[(l + r) / 2];
        if (is_ok(g, rm, used, timer, m)) r = (l + r) / 2;
        else l = (l + r) / 2 + 1;
    }
    cout << fixed << setprecision(8)
            << sqrt(static_cast<long double>(times[l].a) / static_cast<long double>(times[l].b));
    return 0;
}
