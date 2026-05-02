#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

const int32_t maxn = 5e4, inf = 1e9;
int32_t sz[maxn], tin[maxn], tout[maxn], head[maxn], par[maxn];
int32_t timer = 0;
vector<int32_t> g[maxn];

namespace st {
    const int32_t size = maxn;
    int32_t tree[size * 4];

    void init(int32_t id, int32_t l, int32_t r, const vector<int32_t> &vals) {
        if (l >= r && id < size * 4) tree[id] = -inf;
        else if (r - l == 1) tree[id] = l < vals.size() ? vals[l] : -inf;
        else {
            init(id * 2, l, (l + r) / 2, vals);
            init(id * 2 + 1, (l + r) / 2, r, vals);
            tree[id] = std::max(tree[id * 2], tree[id * 2 + 1]);
        }
    }

    void assign(const vector<int32_t> &vals) {
        init(1, 0, size, vals);
    }

    void _upd(int32_t id, int32_t l, int32_t r, int32_t pos, int32_t val) {
        if (l >= r || pos < l || r <= pos) return;
        if (l == pos && r == pos + 1) tree[id] = val;
        else {
            _upd(id * 2, l, (l + r) / 2, pos, val);
            _upd(id * 2 + 1, (l + r) / 2, r, pos, val);
            tree[id] = std::max(tree[id * 2], tree[id * 2 + 1]);
        }
    }

    void upd(int32_t pos, int32_t val) {
        _upd(1, 0, size, pos, val);
    }

    int32_t _max_val(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || b <= l || r <= a) return -inf;
        if (a <= l && r <= b) return tree[id];
        return std::max(_max_val(id * 2, l, (l + r) / 2, a, b), _max_val(id * 2 + 1, (l + r) / 2, r, a, b));
    }

    int32_t max_val(int32_t a, int32_t b) {
        return _max_val(1, 0, size, a, b);
    }
}


int32_t dfs_size(int32_t u, int32_t p = -1) {
    sz[u] = 1;
    par[u] = p;
    for (auto &v: g[u]) {
        if (v == p) continue;
        sz[u] += dfs_size(v, u);
        if (sz[v] > sz[g[u][0]] || g[u][0] == p) swap(v, g[u][0]);
    }
    return sz[u];
}

void dfs_hld(int32_t u, int32_t p = -1) {
    tin[u] = timer++;
    for (auto v: g[u]) {
        if (v == p) continue;
        head[v] = (v == g[u][0] ? head[u] : v);
        dfs_hld(v, u);
    }
    tout[u] = timer;
}

void upd(int32_t u, int32_t val) {
    st::upd(tin[u], val);
}

bool anc(int32_t a, int32_t b) {
    return tin[a] <= tin[b] && tin[b] < tout[a];
}

void up(int32_t &a, int32_t &b, int32_t &ans) {
    while (!anc(head[a], b)) {
        ans = std::max(ans, st::max_val(tin[head[a]], tin[a] + 1));
        a = par[head[a]];
    }
}

int32_t get_max(int32_t a, int32_t b) {
    int32_t ans = -inf;
    up(a, b, ans);
    up(b, a, ans);
    if (!anc(a, b)) swap(a, b);
    ans = std::max(ans, st::max_val(tin[a], tin[b] + 1));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    vector<int32_t> rhs(n), hs(n);
    for (auto &v: rhs) cin >> v;
    for (int32_t i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs_size(0);
    dfs_hld(0);
    for (int32_t i = 0; i < n; ++i) hs[tin[i]] = rhs[i];
    st::assign(hs);
    int32_t k;
    cin >> k;
    char c;
    for (int32_t i = 0, a, b; i < k; ++i) {
        cin >> c >> a >> b;
        if (c == '!') {
            upd(a - 1, b);
        } else {
            cout << get_max(a - 1, b - 1) << "\n";
        }
    }
    return 0;
}
