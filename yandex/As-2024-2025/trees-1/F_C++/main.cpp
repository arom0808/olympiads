#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 5e4 + 2;
int tin[maxn], tout[maxn], sz[maxn];
vector<int> g[maxn];
int hs[maxn], par[maxn], head[maxn];
int n;
int timer = 0;

namespace ST {
    int tree[maxn * 2];
    // int vals[maxn];

    void init() {
        // for (int i = 0; i < n; ++i) vals[tin[i]] = hs[i];
        for (int i = 0; i < n; ++i) tree[tin[i] + n] = hs[i];
        for (int i = n - 1; i >= 0; --i) tree[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
    }

    int get_max(int l, int r) {
        // int ans = 0;
        // for (int i = l; i < r; ++i) ans = std::max(ans, vals[i]);
        // return ans;
        l += n, r += n;
        int ans = 0;
        while (l != r) {
            if (l & 1) ans = std::max(ans, tree[l++]);
            if (r & 1) ans = std::max(ans, tree[--r]);
            l >>= 1, r >>= 1;
        }
        return ans;
    }

    void set_val(int pos, int val) {
        // vals[pos] = val;
        pos += n;
        tree[pos] = val;
        for (pos >>= 1; pos; pos >>= 1) tree[pos] = std::max(tree[pos << 1], tree[pos << 1 | 1]);
    }
}

void dfs1(int v, int p = -1) {
    par[v] = p;
    if (p != -1) g[v].erase(find(g[v].begin(), g[v].end(), p));
    sz[v] = 1;
    for (auto u: g[v]) {
        dfs1(u, v);
        sz[v] += sz[u];
    }
    for (auto &u: g[v]) if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
}

void dfs2(int v) {
    tin[v] = timer++;
    for (auto u: g[v]) {
        head[u] = (u == g[v][0] ? head[v] : u);
        dfs2(u);
    }
    tout[v] = timer;
}

bool cont(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void up(int &a, int b, int &ans) {
    while (!cont(head[a], b)) {
        ans = std::max(ans, ST::get_max(tin[head[a]], tin[a] + 1));
        a = par[head[a]];
    }
}

int get_ans(int a, int b) {
    int ans = 0;
    up(a, b, ans);
    up(b, a, ans);
    if (tin[a] > tin[b]) swap(a, b);
    ans = std::max(ans, ST::get_max(tin[a], tin[b] + 1));
    return ans;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> hs[i];
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    head[0] = 0;
    dfs1(0);
    dfs2(0);
    ST::init();
    int q;
    cin >> q;
    for (int i = 0, v, j; i < q; ++i) {
        char c;
        cin >> c >> v >> j;
        if (c == '!') ST::set_val(tin[v - 1], j);
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
