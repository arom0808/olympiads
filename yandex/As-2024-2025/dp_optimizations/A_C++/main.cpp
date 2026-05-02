#include <iostream>
#include <vector>

using namespace std;
using ll = int64_t;
constexpr ll inf = 1e18;

struct Line {
    ll k, b;

    ll operator()(int x) const {
        return 1ll * k * x + b;
    }

    void init() {
        k = 0, b = inf;
    }
};

namespace LiChao {
    struct Node {
        Line line;
        Node *l = nullptr, *r = nullptr;

        Node &init(Line _line) {
            line = _line;
            return *this;
        }
    };

    constexpr int max_st_size = 5e6;
    constexpr int min_arg = -1e5, max_arg = 1e5;
    Node tree[max_st_size];
    int nodes_used = 0;

    Node *get_new_node(Line line) {
        return &(tree[nodes_used++].init(line));
    }

    Node *init(Line line) {
        return get_new_node(line);
    }

    void init_children(Node *v) {
        if (!v->l) v->l = get_new_node(v->line);
        if (!v->r) v->r = get_new_node(v->line);
    }

    void _insert(Node *v, int l, int r, Line line) {
        int mid = (l + r) / 2;
        if (line(mid) < v->line(mid)) swap(line, v->line);
        if (r - l == 1) return;
        init_children(v);
        if (v->line(l) > line(l)) _insert(v->l, l, mid, line);
        else if (v->line(r - 1) > line(r - 1)) _insert(v->r, mid, r, line);
    }

    void insert(Node *root, Line line) {
        _insert(root, min_arg, max_arg + 1, line);
    }

    ll _min_val(Node *v, int l, int r, int x) {
        int mid = (l + r) / 2;
        ll cv = v->line(x), nv = inf;
        if (x < mid && v->l) nv = std::min(nv, _min_val(v->l, l, mid, x));
        if (x > mid && v->r) nv = std::min(nv, _min_val(v->r, mid, r, x));
        return std::min(cv, nv);
    }

    ll min_val(Node *root, int x) {
        return _min_val(root, min_arg, max_arg, x);
    }
}

constexpr int maxn = 1e5;

vector<int> g[maxn];
ll ans[maxn];
int sz[maxn];
int as[maxn], bs[maxn];
int n;
LiChao::Node *roots[maxn];

void dfs2(LiChao::Node *croot, int v, int p = -1) {
    LiChao::insert(croot, Line(bs[v], ans[v]));
    for (auto u: g[v]) if (u != p) dfs2(croot, u, v);
}

void dfs1(int v, int p = -1) {
    if (g[v].size() == 1 && p != -1) {
        sz[v] = 1;
        ans[v] = 0;
        roots[v] = LiChao::init(Line(bs[v], ans[v]));
        return;
    }
    int mv = -1, msz = 0;
    sz[v] = 1;
    for (auto u: g[v]) {
        if (u == p) continue;
        dfs1(u, v);
        if (sz[u] > msz) msz = sz[u], mv = u;
        sz[v] += sz[u];
    }
    roots[v] = roots[mv];
    for (auto u: g[v]) if (u != p && u != mv) dfs2(roots[v], u, v);
    ans[v] = LiChao::min_val(roots[v], as[v]);
    LiChao::insert(roots[v], Line(bs[v], ans[v]));
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> as[i];
    for (int i = 0; i < n; ++i) cin >> bs[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs1(0);
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
    return 0;
}
