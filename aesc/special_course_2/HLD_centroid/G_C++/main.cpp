#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

const int32_t maxn = 2e5;
const int64_t mod = 1e9 + 7;
using T = uint64_t;

namespace st {
    struct Node {
        T sum = 0, push = 0;
    };

    Node tree[maxn * 4];

    void init(int32_t id, int32_t l, int32_t r, const vector<T> &vals) {
        if (l >= r) return;
        if (r - l == 1) tree[id].sum = l < vals.size() ? vals[l] : 0;
        else {
            init(id * 2, l, (l + r) / 2, vals);
            init(id * 2 + 1, (l + r) / 2, r, vals);
            tree[id].sum = tree[id * 2].sum + tree[id * 2 + 1].sum;
        }
    }

    void assign(const vector<T> &vals) {
        init(1, 0, maxn, vals);
    }

    void push_changes(int32_t id, int32_t l, int32_t r) {
        if (tree[id].push == 0) return;
        if ((l + r) / 2 - l >= 1)
            tree[id * 2].sum += tree[id].push * ((l + r) / 2 - l), tree[id * 2].push += tree[id].push;
        if (r - (l + r) / 2 >= 1)
            tree[id * 2 + 1].sum += tree[id].push * (r - (l + r) / 2), tree[id * 2 + 1].push += tree[id].push;
        tree[id].push = 0;
    }

    void _add(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b, T val) {
        if (l >= r || r <= a || b <= l) return;
        push_changes(id, l, r);
        if (a <= l && r <= b) {
            tree[id].sum += val * (r - l);
            tree[id].push += val;
        } else {
            _add(id * 2, l, (l + r) / 2, a, b, val);
            _add(id * 2 + 1, (l + r) / 2, r, a, b, val);
            tree[id].sum = tree[id * 2].sum + tree[id * 2 + 1].sum;
        }
    }

    void add(int32_t a, int32_t b, T val) {
        _add(1, 0, maxn, a, b, val);
    }

    T _sum(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || r <= a || b <= l) return 0;
        if (a <= l && r <= b) return tree[id].sum;
        push_changes(id, l, r);
        return _sum(id * 2, l, (l + r) / 2, a, b) + _sum(id * 2 + 1, (l + r) / 2, r, a, b);
    }

    T sum(int32_t a, int32_t b) {
        return _sum(1, 0, maxn, a, b);
    }
}

int32_t sz[maxn], tin[maxn], tout[maxn], head[maxn], par[maxn];
vector<int32_t> g[maxn];
int32_t timer = 0;

void dfs_size(int32_t u) {
    sz[u] = 1;
    for (auto &v: g[u]) {
        dfs_size(v);
        sz[u] += sz[v];
        if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}

void dfs_hld(int32_t u) {
    tin[u] = timer++;
    for (auto v: g[u]) {
        head[v] = (v == g[u][0] ? head[u] : v);
        dfs_hld(v);
    }
    tout[u] = timer;
}

bool anc(int32_t a, int32_t b) {
    return tin[a] <= tin[b] && tin[b] < tout[a];
}

void up(int32_t &a, int32_t &b, T &ans) {
    while (!anc(head[a], b)) {
        ans += st::sum(tin[head[a]], tin[a] + 1);
        a = par[head[a]];
    }
}

void up_upd(int32_t &a, int32_t &b, T val) {
    while (!anc(head[a], b)) {
        st::add(tin[head[a]], tin[a] + 1, val);
        a = par[head[a]];
    }
}

T sum_on_path(int32_t a, int32_t b) {
    T ans = 0;
    up(a, b, ans);
    up(b, a, ans);
    if (!anc(a, b)) swap(a, b);
    ans += st::sum(tin[a], tin[b] + 1);
    return ans;
}

T sum_on_subtree(int32_t u) {
    return st::sum(tin[u], tout[u]);
}

T get_val(int32_t u) {
    return st::sum(tin[u], tin[u] + 1);
}

void add_on_path(int32_t a, int32_t b, T val) {
    up_upd(a, b, val);
    up_upd(b, a, val);
    if (!anc(a, b)) swap(a, b);
    st::add(tin[a], tin[b] + 1, val);
}

void add_on_subtree(int32_t u, T val) {
    st::add(tin[u], tout[u], val);
}

void add_val(int32_t u, T val) {
    st::add(tin[u], tin[u] + 1, val);
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m;
    cin >> n >> m;
    for (int32_t i = 1, a; i < n; ++i) cin >> a, par[i] = a, g[a].push_back(i);
    par[0] = -1;
    head[0] = 0;
    dfs_size(0);
    dfs_hld(0);
    vector<T> ocs(n), cs(n);
    for (auto &v: ocs) cin >> v;
    for (int32_t i = 0; i < n; ++i) cs[tin[i]] = ocs[i];
    st::assign(cs);
    cout << get_val(n - 1) << " ";
    for (int32_t i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        uint64_t ns = sum_on_path(0, a) + sum_on_subtree(a) - get_val(a);
        ns %= mod;
        add_on_path(0, b, ns);
        add_on_subtree(b, ns);
        add_val(b, -ns);
        cout << get_val(n - 1) << " ";
    }
    return 0;
}
