#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

const int32_t maxn = 2e5;

int32_t n;

vector<int32_t> g[maxn];
int32_t sz[maxn];

int32_t dfs_sz(int32_t u, int32_t p = -1) {
    sz[u] = 1;
    for (auto v: g[u]) if (v != p) sz[u] += dfs_sz(v, u);
    return sz[u];
}

int32_t dfs_centroid(int32_t u, int32_t p = -1) {
    int32_t v = -1;
    for (auto _v: g[u]) if (_v != p && sz[_v] > n / 2) v = _v;
    if (v != -1) return dfs_centroid(v, u);
    return u;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int32_t i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs_sz(0);
    cout << dfs_centroid(0) + 1 << "\n";
    return 0;
}
