#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 1e5, maxm = 1e5, mod = 1e9 + 7;
int n;
vector<int> g[maxn];
int par[maxn];
int start_vals[maxn], st_start_vals[maxn];
int sz[maxn], tin[maxn], tout[maxn], head[maxn];
int timer = 0;

void dfs1(int v) {
    sz[v] = 1;
    for (auto u: g[v]) {
        dfs1(u);
        sz[v] += sz[u];
    }
    for (auto &u: g[v]) if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
}

void dfs2(int v) {
    tin[v] = timer++;
    for (auto u: g[v]) {
        head[u] = (u == g[v][0]) ? head[v] : u;
        dfs2(u);
    }
    tout[v] = timer;
}

namespace ST {
    struct Node {
        ll sum = 0, push = 0;
    };

    Node tree[maxn * 4];

    void push(int v, int l, int r) {
        if (!tree[v].push) return;
        int m = (l + r) >> 1;
        if (r - l > 1) {
            tree[v << 1].sum += tree[v].push * (m - l), tree[v << 1].push += tree[v].push;
            tree[v << 1 | 1].sum += tree[v].push * (r - m), tree[v << 1 | 1].push += tree[v].push;
        }
        tree[v].push = 0;
    }

    void upd_from_children(int v, int l, int r) {
        if (r - l <= 1) return;
        tree[v].sum = tree[v << 1].sum + tree[v << 1 | 1].sum;
    }

    void _init(int v, int l, int r) {
        if (r - l == 1) {
            tree[v].sum = st_start_vals[l];
            return;
        }
        int m = (l + r) / 2;
        _init(v << 1, l, m);
        _init(v << 1 | 1, m, r);
        upd_from_children(v, l, r);
    }

    void init() {
        _init(1, 0, n);
    }

    void _add(int v, int l, int r, int a, int b, ll val) {
        if (a >= r || l >= b) return;
        if (a <= l && r <= b) {
            tree[v].sum += val * (r - l), tree[v].push += val;
            return;
        }
        push(v, l, r);
        int m = (l + r) >> 1;
        _add(v << 1, l, m, a, b, val);
        _add(v << 1 | 1, m, r, a, b, val);
        upd_from_children(v, l, r);
    }

    void add(int a, int b, ll val) {
        _add(1, 0, n, a, b, val);
    }

    ll _sum(int v, int l, int r, int a, int b) {
        if (a >= r || l >= b) return 0;
        if (a <= l && r <= b) return tree[v].sum;
        push(v, l, r);
        int m = (l + r) >> 1;
        return _sum(v << 1, l, m, a, b) + _sum(v << 1 | 1, m, r, a, b);
    }

    ll sum(int a, int b) {
        return _sum(1, 0, n, a, b);
    }

    // ll vals[maxn];
    //
    // ll sum(int l, int r) {
    //     ll ans = 0;
    //     for (int i = l; i < r; ++i) ans += vals[i];
    //     return ans;
    // }
    //
    // void add(int l, int r, ll val) {
    //     for (int i = l; i < r; ++i) vals[i] += val;
    // }
    //
    // void init() {
    //     for (int i = 0; i < n; ++i) vals[i] = st_start_vals[i];
    // }
}

bool anc(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void up_get(int &a, int b, ll &ans) {
    while (!anc(head[a], b)) {
        ans += ST::sum(tin[head[a]], tin[a] + 1);
        a = par[head[a]];
    }
}

ll get_sum_on_path(int a, int b) {
    ll ans = 0;
    up_get(a, b, ans);
    up_get(b, a, ans);
    if (!anc(a, b)) swap(a, b);
    ans += ST::sum(tin[a], tin[b] + 1);
    return ans;
}

void up_add(int &a, int b, ll val) {
    while (!anc(head[a], b)) {
        ST::add(tin[head[a]], tin[a] + 1, val);
        a = par[head[a]];
    }
}

void add_on_path(int a, int b, ll val) {
    up_add(a, b, val);
    up_add(b, a, val);
    if (!anc(a, b)) swap(a, b);
    ST::add(tin[a], tin[b] + 1, val);
}

void solve() {
    int m;
    cin >> n >> m;
    for (int i = 1, p; i < n; ++i) {
        cin >> p;
        par[i] = p, g[p].push_back(i);
    }
    for (int i = 0; i < n; ++i) cin >> start_vals[i];
    dfs1(0);
    dfs2(0);
    for (int i = 0; i < n; ++i) st_start_vals[tin[i]] = start_vals[i];
    ST::init();
    cout << ST::sum(tin[n - 1], tin[n - 1] + 1) << " ";
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        ll s = get_sum_on_path(0, a) + ST::sum(tin[a], tout[a]) - ST::sum(tin[a], tin[a] + 1);
        s %= mod;
        add_on_path(0, b, s);
        ST::add(tin[b], tout[b], s);
        ST::add(tin[b], tin[b] + 1, -s);
        cout << ST::sum(tin[n - 1], tin[n - 1] + 1) << " ";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
