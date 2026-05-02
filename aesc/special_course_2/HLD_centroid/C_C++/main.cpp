#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

#include <iostream>
#include <cstdint>
#include <vector>
#include <set>

using namespace std;

const int32_t maxn = 2e5, maxlogn = 20;

vector<int32_t> g[maxn], centres[maxlogn];
int32_t cp[maxn], sz[maxn], dist[maxn][maxlogn];
bool used[maxn], color[maxn];
set<pair<int32_t, int32_t>> st[maxn];
int32_t c_class_by_id[maxn];

int32_t dfs_sz(int32_t u, int32_t p = -1) {
    sz[u] = 1;
    for (auto v: g[u]) if (v != p && !used[v]) sz[u] += dfs_sz(v, u);
    return sz[u];
}

int32_t dfs_centroid(int32_t u, int32_t cn, int32_t p = -1) {
    int32_t v = -1;
    for (auto _v: g[u]) {
        if (_v != p && !used[_v] && sz[_v] > cn / 2) {
            v = _v;
            break;
        }
    }
    if (v == -1) return u;
    return dfs_centroid(v, cn, u);
}

void dfs_dist(int32_t u, int32_t c_class, int32_t depth = 0, int32_t p = -1) {
    dist[u][c_class] = depth;
    for (auto v: g[u]) if (!used[v] && v != p) dfs_dist(v, c_class, depth + 1, u);
}

void calc_centroid(int32_t u, int32_t c_class, int32_t p_c_id) {
    if (used[u]) return;
    dfs_sz(u);
    int32_t c_id = dfs_centroid(u, sz[u]);
    dfs_dist(c_id, c_class);
    centres[c_class].push_back(c_id);
    cp[c_id] = p_c_id;
    c_class_by_id[c_id] = c_class;
    used[c_id] = true;
}

void calc_centroid_tree() {
    calc_centroid(0, 0, -1);
    for (int32_t c_class = 0; c_class < maxlogn && !centres[c_class].empty(); ++c_class)
        for (auto c_id: centres[c_class])
            for (auto u: g[c_id])
                calc_centroid(u, c_class + 1, c_id);
}

void upd(int32_t u, bool act) { // true - add, false - erase
    for (int32_t v = u, c_class = c_class_by_id[u]; v != -1; v = cp[v], --c_class) {
        if (act) st[v].emplace(dist[u][c_class], u);
        else st[v].erase({dist[u][c_class], u});
    }
}

int32_t get(int32_t u) {
    int32_t min_dist = -1;
    for (int32_t v = u, c_class = c_class_by_id[u]; v != -1; v = cp[v], --c_class)
        if (!st[v].empty() && (min_dist == -1 || st[v].begin()->first + dist[u][c_class] < min_dist))
            min_dist = st[v].begin()->first + dist[u][c_class];
    return min_dist;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, q;
    cin >> n;
    for (int32_t i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        g[a - 1].push_back(b - 1), g[b - 1].push_back(a - 1);
    }
    calc_centroid_tree();
    cin >> q;
    for (int32_t i = 0, a, b; i < q; ++i) {
        cin >> a >> b, --b;
        if (a == 0) {
            upd(b, !color[b]);
            color[b] = !color[b];
        } else {
            cout << get(b) << "\n";
        }
    }
    return 0;
}
