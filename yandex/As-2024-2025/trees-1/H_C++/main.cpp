#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr int maxn = 1e5, maxd = 20000;

int vals[maxn], sz[maxn], tin[maxn], tout[maxn], head[maxn], par[maxn], ids_sort_by_vals[maxn], sorted_vals[maxn],
        sorted_div_vals[maxn];
vector<pair<int, int> > g[maxn];
int n, timer = 0;

namespace ST {
    int tree[maxn * 2];

    void set_val(int pos, int val) {
        pos += n;
        tree[pos] = val;
        for (pos >>= 1; pos; pos >>= 1) tree[pos] = tree[pos << 1] + tree[pos << 1 | 1];
    }

    int sum(int l, int r) {
        l += n, r += n;
        int ans = 0;
        while (l != r) {
            if (l & 1) ans += tree[l++];
            if (r & 1) ans += tree[--r];
            l >>= 1, r >>= 1;
        }
        return ans;
    }
}

void dfs1(int v, int val = 0, int p = -1) {
    par[v] = p;
    vals[v] = val;
    sz[v] = 1;
    if (p != -1) g[v].erase(find_if(g[v].begin(), g[v].end(), [p](const pair<int, int> &u) { return u.first == p; }));
    for (auto [u,d]: g[v]) {
        dfs1(u, d, v);
        sz[v] += sz[u];
    }
    for (auto &u: g[v]) if (sz[u.first] > sz[g[v][0].first]) swap(u, g[v][0]);
}

void dfs2(int v) {
    tin[v] = timer++;
    for (auto [u,d]: g[v]) {
        head[u] = (u == g[v][0].first) ? head[v] : u;
        dfs2(u);
    }
    tout[v] = timer;
}

void upd_t(int t) {
    for (int k = 0, a = k * t + 1, b = (k + 1) * t; a <= maxd; a += t, b += t, ++k) {
        int l = lower_bound(sorted_vals, sorted_vals + n, a) - sorted_vals;
        int r = upper_bound(sorted_vals, sorted_vals + n, b) - sorted_vals;
        int c = lower_bound(sorted_div_vals + l, sorted_div_vals + r, k) - sorted_div_vals;
        int d = upper_bound(sorted_div_vals + l, sorted_div_vals + r, k) - sorted_div_vals;
        for (int i = l; i < c; ++i) {
            sorted_div_vals[i] = k;
            ST::set_val(tin[ids_sort_by_vals[i]], k);
        }
        for (int i = d; i < r; ++i) {
            sorted_div_vals[i] = k;
            ST::set_val(tin[ids_sort_by_vals[i]], k);
        }
    }
}

bool anc(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void up(int &a, int b, int &ans) {
    while (!anc(head[a], b)) {
        ans += ST::sum(tin[head[a]], tin[a] + 1);
        ans += tin[a] - tin[head[a]] + 1;
        a = par[head[a]];
    }
}

int get_sum_in_path(int a, int b) {
    int ans = 0;
    up(a, b, ans);
    up(b, a, ans);
    if (!anc(a, b)) swap(a, b);
    ans += ST::sum(tin[a], tin[b] + 1);
    ans -= ST::sum(tin[a], tin[a] + 1);
    ans += tin[b] - tin[a] + 1;
    return ans;
}

struct Req {
    int s, f, t, id;

    bool operator<(const Req &rhs) const {
        return t < rhs.t;
    }

    friend istream &operator>>(istream &is, Req &rhs) {
        is >> rhs.s >> rhs.f >> rhs.t;
        --rhs.s, --rhs.f;
        return is;
    }
};

Req reqs[maxn];
int ans[maxn];

void solve() {
    int q;
    cin >> n >> q;
    for (int i = 1, u, v, d; i < n; ++i) {
        cin >> u >> v >> d, --u, --v;
        g[u].emplace_back(v, d), g[v].emplace_back(u, d);
    }
    head[0] = 0;
    dfs1(0);
    dfs2(0);
    iota(ids_sort_by_vals, ids_sort_by_vals + n, 0);
    sort(ids_sort_by_vals, ids_sort_by_vals + n, [](int a, int b) { return vals[a] < vals[b]; });
    for (int i = 0; i < n; ++i) sorted_vals[i] = vals[ids_sort_by_vals[i]];
    for (int i = 0; i < q; ++i) cin >> reqs[i], reqs[i].id = i;
    sort(reqs, reqs + q);
    int pre_t = 0;
    for (int i = 0; i < q; ++i) {
        if (pre_t != reqs[i].t) upd_t(reqs[i].t), pre_t = reqs[i].t;
        ans[reqs[i].id] = get_sum_in_path(reqs[i].f, reqs[i].s);
    }
    for (int i = 0; i < q; ++i) cout << ans[i] << "\n";
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
