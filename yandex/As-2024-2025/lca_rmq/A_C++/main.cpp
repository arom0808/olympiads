#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 2e5, maxlogn = 20;
vector<int> g[maxn];
int up[maxn][maxlogn];
int tin[maxn], tout[maxn];
int t = 0;
int chv[maxn];
int ans = 0, ansval = 0;

// v -> u
bool anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

void dfs_up(int v, int ch = 0, int p = -1) {
    up[v][0] = (p == -1 ? 0 : p);
    for (int l = 1; l < maxlogn; ++l) up[v][l] = up[up[v][l - 1]][l - 1];
    tin[v] = t++;
    for (auto u: g[v]) if (u != p) dfs_up(u, ch + 1, v);
    tout[v] = t;
}

int plca(int v, int u) {
    if (tin[v] < tin[u]) swap(v, u);
    for (int l = maxlogn - 1; l >= 0; --l) if (!anc(up[v][l], u)) v = up[v][l];
    return v;
}

void dfs_ans(int v, int cans = 0, int p = -1) {
    cans += chv[v];
    if (cans > ansval) ansval = cans, ans = v;
    for (auto u: g[v]) if (u != p) dfs_ans(u, cans, v);
}

void solve() {
    int n, m;
    cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y, --x, --y;
        g[x].push_back(y), g[y].push_back(x);
    }
    dfs_up(0);
    cin >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b, --a, --b;
        if (tin[a] > tin[b]) swap(a, b);
        int cl = plca(a, b);
        if (up[cl][0] == a) ++chv[0], --chv[cl], ++chv[b];
        else ++chv[a], ++chv[b];
    }
    dfs_ans(0);
    cout << ansval << "\n";
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
