#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 2e5;

int n;
vector<int> g[maxn];
bool used[maxn];
int timer = 1;
int sz[maxn], cur_par[maxn], par[maxn];


int dfs_sz(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (auto u: g[v]) if (u != p) sz[v] += dfs_sz(u, v);
    return sz[v];
}

void p_dfs(int v, int set_p, int p = -1) {
    if (used[v]) return;
    cur_par[v] = set_p;
    for (auto u: g[v]) if (u != p) p_dfs(u, set_p, v);
}

void find_add_centroid(int root) {
    dfs_sz(root);
    int v = root;
    for (int found = 1, cp = -1; found;) {
        found = 0;
        for (auto u: g[v]) {
            if (u == cp || used[u] || sz[u] <= sz[root] / 2) continue;
            cp = v, v = u, found = 1;
            break;
        }
    }
    par[v] = cur_par[v];
    p_dfs(v, v);
    used[v] = true;
}

void solve() {
    cin >> n;
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) cur_par[i] = -1;
    for (int v = 0; v < n; ++v) while (!used[v]) find_add_centroid(v);
    for (int i = 0; i < n; ++i) cout << par[i] + 1 << " ";
    cout << "\n";
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
