#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

const int32_t maxn = 2e5;
const int32_t maxlogn = 20;


vector<int32_t> centroids[maxlogn];
vector<int32_t> g[maxn];
int32_t sz[maxn], c_p[maxn];
bool used[maxn];

int32_t dfs_sz(int32_t u, int32_t p = -1) {
    sz[u] = 1;
    for (auto v: g[u]) if (v != p && !used[v]) sz[u] += dfs_sz(v, u);
    return sz[u];
}

int32_t dfs_centroid(int32_t u, int32_t cn, int32_t p = -1) {
    int32_t v = -1;
    for (auto _v: g[u]) if (_v != p && sz[_v] > cn / 2 && !used[_v]) v = _v;
    if (v != -1) return dfs_centroid(v, cn, u);
    return u;
}

void calc_centroid(int32_t v, int32_t c_class, int32_t p_c_id) {
    if (used[v]) return;
    dfs_sz(v);
    int32_t c_id = dfs_centroid(v, sz[v]);
    centroids[c_class].push_back(c_id);
    c_p[c_id] = p_c_id;
    used[c_id] = true;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    for (int32_t i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    calc_centroid(0, 0, -1);
    for (int32_t c_class = 0; c_class < maxlogn && !centroids[c_class].empty(); ++c_class)
        for (auto c_id: centroids[c_class])
            for (auto v: g[c_id])
                calc_centroid(v, c_class + 1, c_id);
    for (int32_t i = 0; i < n; ++i) cout << c_p[i] + 1 << " ";
    return 0;
}
