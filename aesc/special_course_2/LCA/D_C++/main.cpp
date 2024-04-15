#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int32_t inf = 1e9;

void dfs(const vector<list<pair<int32_t, int32_t>>> &g, vector<vector<int32_t>> &up, vector<vector<int32_t>> &min_up,
         vector<int32_t> &tin, vector<int32_t> &tout, int32_t v, int32_t p, int32_t pc, int32_t logn, int32_t &t) {
    up[0][v] = p;
    min_up[0][v] = pc;
    for (int32_t i = 1; i <= logn; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
        min_up[i][v] = min(min_up[i - 1][up[i - 1][v]], min_up[i-1][v]);
    }
    tin[v] = t++;
    for (auto [u, c]: g[v]) if (u != p) dfs(g, up, min_up, tin, tout, u, v, c, logn, t);
    tout[v] = t++;
}

inline bool is_parent(const vector<int32_t> &tin, const vector<int32_t> &tout, int32_t x, int32_t y) {
    return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int32_t min_for_x(const vector<vector<int32_t>> &up, const vector<vector<int32_t>> &min_up, const vector<int32_t> &tin,
                  const vector<int32_t> &tout, int32_t logn, int32_t x, int32_t y) {
    if (is_parent(tin, tout, x, y)) return inf;
    int32_t res = inf;
    for (int32_t i = logn; i >= 0; --i) {
        if (!is_parent(tin, tout, up[i][x], y)) {
            if (min_up[i][x] < res) res = min_up[i][x];
            x = up[i][x];
        }
    }
    return min(min_up[0][x], res);
}

int main() {
    int32_t n;
    cin >> n;
    vector<list<pair<int32_t, int32_t>>> g(n);
    for (int32_t i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        g[x - 1].emplace_back(i, y);
    }
    int32_t logn = __lg(n);
    vector<vector<int32_t>> up(logn + 1, vector<int32_t>(n, 0)), min_up(logn + 1, vector<int32_t>(n, inf));
    vector<int32_t> tin(n), tout(n);
    int32_t t = 0;
    dfs(g, up, min_up, tin, tout, 0, 0, inf, logn, t);
    int32_t m;
    cin >> m;
    for (int32_t i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        --x;
        --y;
        cout << min(min_for_x(up, min_up, tin, tout, logn, x, y), min_for_x(up, min_up, tin, tout, logn, y, x)) << "\n";
    }
    return 0;
}
