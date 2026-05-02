#ifdef LOCAL
#include <iostream>
#else
#pragma GCC optimize("Ofast")
#endif

#include <vector>
using namespace std;

constexpr int maxn = 1e6;

vector<int> g[maxn];
int par[maxn], sz[maxn];
int tin[maxn], tout[maxn], head[maxn], depth[maxn];
int root = 0;
int n, q, timer = 0;
int mst_nums[maxn];

namespace MST {
    constexpr int max_nodes_cnt = 5e7;

    struct Node {
        int sum = 0;
        Node *l = nullptr, *r = nullptr;

        void init() {
            sum = 0;
            l = r = nullptr;
        }
    };

    Node tree[max_nodes_cnt];
    Node *roots[maxn * 3];
    int nodes_used = 0;

    Node *get_new_node() {
        Node *res = &tree[nodes_used++];
        res->init();
        return res;
    }

    void _add(Node *v, int l, int r, int pos, int val) {
        if (l > pos || pos >= r) return;
        if (l == pos && r == pos + 1) {
            v->sum += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos < mid) {
            if (!v->l) v->l = get_new_node();
            _add(v->l, l, mid, pos, val);
        } else {
            if (!v->r) v->r = get_new_node();
            _add(v->r, mid, r, pos, val);
        }
        v->sum = 0;
        if (v->l) v->sum += v->l->sum;
        if (v->r) v->sum += v->r->sum;
    }

    void init() {
        nodes_used = 0;
        for (int i = 0; i < n * 3; ++i) roots[i] = get_new_node();
        for (int i = 0; i < n; ++i)
            if (mst_nums[i] + 2 * n >= 0 && mst_nums[i] + 2 * n < n * 3)
                _add(roots[mst_nums[i] + 2 * n], 0, n, i, 1);
    }

    void change(int pos, int new_val) {
        if (mst_nums[pos] + 2 * n >= 0 && mst_nums[pos] + 2 * n < n * 3)
            _add(roots[mst_nums[pos] + 2 * n], 0, n, pos, -1);
        mst_nums[pos] = new_val;
        if (mst_nums[pos] + 2 * n >= 0 && mst_nums[pos] + 2 * n < n * 3)
            _add(roots[mst_nums[pos] + 2 * n], 0, n, pos, 1);
    }

    int _sum(Node *v, int l, int r, int a, int b) {
        if (l >= b || a >= r || !v->sum) return 0;
        if (a <= l && r <= b) return v->sum;
        int res = 0;
        if (v->l) res += _sum(v->l, l, (l + r) / 2, a, b);
        if (v->r) res += _sum(v->r, (l + r) / 2, r, a, b);
        return res;
    }

    int cnt(int a, int b, int val) {
        if (val + 2 * n >= 0 && val + 2 * n < n * 3) return _sum(roots[val + 2 * n], 0, n, a, b);
        return 0;
    }
}

// a -> b
inline bool anc(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void size_reorder_dfs(int v, int d = 0) {
    depth[v] = d;
    sz[v] = 1;
    for (auto &u: g[v]) {
        size_reorder_dfs(u, d + 1);
        sz[v] += sz[u];
        if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
    }
}

void up(int &a, int &b, int &ans, int val) {
    while (!anc(head[a], b)) {
        ans += MST::cnt(tin[head[a]], tin[a] + 1, val);
        a = par[head[a]];
    }
}

void nothing_up(int &a, int &b) {
    while (!anc(head[a], b)) a = par[head[a]];
}

int lca(int a, int b) {
    nothing_up(a, b);
    nothing_up(b, a);
    if (anc(a, b)) return a;
    return b;
}

int get_cnt(int a, int b, int val) {
    int ans = 0;
    up(a, b, ans, val);
    nothing_up(b, a);
    if (!anc(b, a)) return ans;
    ans += MST::cnt(tin[b] + 1, tin[a] + 1, val);
    return ans;
}

void hld(int v) {
    tin[v] = timer++;
    for (auto u: g[v]) {
        head[u] = (u == g[v][0] ? head[v] : u);
        hld(u);
    }
    tout[v] = timer;
}

vector<int> solve(int _n, int _q, vector<int> nums, vector<int> _p, vector<int> qt, vector<int> qx, vector<int> qy) {
    n = _n, q = _q;
    copy(_p.begin(), _p.end(), par);
    for (int v = 0; v < n; ++v) {
        if (par[v] != -1) g[par[v]].push_back(v);
        else root = v;
    }
    size_reorder_dfs(root);
    head[root] = root;
    hld(root);
    vector<int> ans;
    ans.reserve(q);
    for (int v = 0; v < n; ++v) mst_nums[tin[v]] = nums[v] + depth[v];
    MST::init();
    for (int i = 0; i < q; ++i) {
        if (qt[i] == 1) MST::change(tin[qx[i]], qy[i] + depth[qx[i]]);
        else ans.push_back(get_cnt(qx[i], qy[i], depth[qx[i]]));
    }
    for (int v = 0; v < n; ++v) mst_nums[tin[v]] = nums[v] - depth[v];
    MST::init();
    for (int i = 0, j = 0; i < q; ++i) {
        if (qt[i] == 1) MST::change(tin[qx[i]], qy[i] - depth[qx[i]]);
        else {
            int lv = lca(qx[i], qy[i]);
            ans[j] += get_cnt(qy[i], qx[i], depth[qx[i]] - 2 * depth[lv]);
            if (mst_nums[tin[lv]] == depth[qx[i]] - 2 * depth[lv]) ++ans[j];
            ++j;
        }
    }
    return ans;
}

#ifdef LOCAL
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];
    vector<int> qt(q), qx(q), qy(q);
    for (int i = 0; i < q; ++i) cin >> qt[i] >> qx[i] >> qy[i];
    auto result = solve(n, q, a, p, qt, qx, qy);
    for (int x: result) cout << x << "\n";
    return 0;
}
#endif
