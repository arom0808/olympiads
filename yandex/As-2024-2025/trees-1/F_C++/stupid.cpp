#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 5e4 + 2;
int tin[maxn], tout[maxn], sz[maxn];
vector<int> g[maxn];
int hs[maxn], par[maxn];
int n;
int timer = 0;

void dfs1(int v, int p = -1) {
    tin[v] = timer++;
    par[v] = p;
    if (p != -1) g[v].erase(find(g[v].begin(), g[v].end(), p));
    sz[v] = 1;
    for (auto u: g[v]) {
        dfs1(u, v);
        sz[v] += sz[u];
    }
    for (auto &u: g[v]) if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
    tout[v] = timer;
}

bool cont(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int get_ans(int a, int b) {
    int ans = 0;
    while (!cont(a, b)) {
        ans = std::max(ans, hs[a]);
        a = par[a];
    }
    ans = std::max(ans, hs[a]);
    while (!cont(b, a)) {
        ans = std::max(ans, hs[b]);
        b = par[b];
    }
    return ans;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> hs[i];
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs1(0);
    int q;
    cin >> q;
    for (int i = 0, v, j; i < q; ++i) {
        char c;
        cin >> c >> v >> j;
        if (c == '!') hs[v - 1] = j;
        else cout << get_ans(v - 1, j - 1) << "\n";
    }
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
