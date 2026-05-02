#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 60, maxm = 15, mod = 1e9 + 7;

int n, m, k;
vector<int> g[maxn];
int hs[maxn];
int par[maxn];
pair<int, int> paths[maxm];
int color[maxn];

void dfs1(int v, int h, int p = -1) {
    hs[v] = h;
    par[v] = p;
    if (p != -1) g[v].erase(find(g[v].begin(), g[v].end(), p));
    for (auto u: g[v]) dfs1(u, h + 1, v);
}

bool is_ok() {
    for (int i = 0; i < m; ++i) {
        auto [u,v] = paths[i];
        int col;
        if (hs[u] < hs[v]) swap(u, v);
        col = color[u];
        bool found = false;
        while (u != v && !found) {
            if (hs[u] < hs[v]) swap(u, v);
            if (color[u] != col) found = true;
            u = par[u];
        }
        if (!found) return false;
    }
    return true;
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b, --a, --b;
        paths[i] = {a, b};
    }
    dfs1(0, 0);
    int ans = 0;
    for (int i = 0; i < (1 << (n - 1)); ++i) {
        for (int j = 0; j + 1 < n; ++j) color[j + 1] = (i >> j) & 1;
        ans = (ans + is_ok()) % mod;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}