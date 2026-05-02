#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

template<typename T>
class SegmentTree {
public:
    struct Elem {
        T max_val = 0, change = 0;
    };

    int32_t size;
    vector<Elem> tree;

    void _init(int32_t id, int32_t l, int32_t r, const vector<T> &values) {
        if (l >= r) return;
        if (r - l == 1) tree[id].max_val = values[l];
        else {
            _init(id * 2, l, (l + r) / 2, values);
            _init(id * 2 + 1, (l + r) / 2, r, values);
        }
    }

    inline void transfer_change(int32_t id) {
        if (!tree[id].change) return;
        if (id * 2 + 1 < tree.size()) {
            tree[id * 2].max_val += tree[id].change, tree[id * 2].change += tree[id].change;
            tree[id * 2 + 1].max_val += tree[id].change, tree[id * 2 + 1].change += tree[id].change;
        }
        tree[id].change = 0;
    }

    void _add(int32_t id, int32_t l, int32_t r, int32_t req_l, int32_t req_r, T val) {
        if (l >= r || req_r <= l || r <= req_l) return;
        transfer_change(id);
        if (req_l <= l && r <= req_r) {
            tree[id].max_val += val, tree[id].change += val;
            return;
        } else if (r - l == 1) return;
        _add(id * 2, l, (l + r) / 2, req_l, req_r, val);
        _add(id * 2 + 1, (l + r) / 2, r, req_l, req_r, val);
        tree[id].max_val = max(tree[id * 2].max_val, tree[id * 2 + 1].max_val);
    }

    void _set(int32_t id, int32_t l, int32_t r, int32_t pos, T val) {
        if (l >= r || pos + 1 <= l || r <= pos) return;
        transfer_change(id);
        if (pos <= l && r <= pos + 1) {
            tree[id].max_val = val, tree[id].change = 0;
            return;
        } else if (r - l == 1) return;
        _set(id * 2, l, (l + r) / 2, pos, val);
        _set(id * 2 + 1, (l + r) / 2, r, pos, val);
        tree[id].max_val = max(tree[id * 2].max_val, tree[id * 2 + 1].max_val);
    }

    T _get_max(int32_t id, int32_t l, int32_t r, int32_t req_l, int32_t req_r) {
        if (l >= r || req_r <= l || r <= req_l) return 0;
        transfer_change(id);
        if (req_l <= l && r <= req_r) return tree[id].max_val;
        else if (r - l == 1) return 0;
        return max(_get_max(id * 2, l, (l + r) / 2, req_l, req_r), _get_max(id * 2 + 1, (l + r) / 2, r, req_l, req_r));
    }

    int32_t _get_nearest_to_left(int32_t id, int32_t l, int32_t r, int32_t req_l, int32_t req_r) {
        if (l >= r || req_r <= l || r <= req_l || tree[id].max_val == 0) return -1;
        transfer_change(id);
        if (r - l == 1) return l;
        int32_t res = _get_nearest_to_left(id * 2, l, (l + r) / 2, req_l, req_r);
        if (res == -1) res = _get_nearest_to_left(id * 2 + 1, (l + r) / 2, r, req_l, req_r);
        return res;
    }

    int32_t _get_nearest_to_right(int32_t id, int32_t l, int32_t r, int32_t req_l, int32_t req_r) {
        if (l >= r || req_r <= l || r <= req_l || tree[id].max_val == 0) return -1;
        transfer_change(id);
        if (r - l == 1) return l;
        int32_t res = _get_nearest_to_right(id * 2 + 1, (l + r) / 2, r, req_l, req_r);
        if (res == -1) res = _get_nearest_to_right(id * 2, l, (l + r) / 2, req_l, req_r);
        return res;
    }

    explicit SegmentTree(int32_t n) : size(n), tree(n * 4) {}

    explicit SegmentTree(const vector<T> &values) : size(values.size()), tree(values.size() * 4) {
        _init(1, 0, size, values);
    }

    inline void add(int32_t l, int32_t r, T val) {
        _add(1, 0, size, l, r, val);
    }

    inline void set(int32_t pos, int32_t val) {
        _set(1, 0, size, pos, val);
    }

    inline T get_max(int32_t l, int32_t r) {
        return _get_max(1, 0, size, l, r);
    }

    inline int32_t get_nearest_to_left(int32_t l, int32_t r) {
        return _get_nearest_to_left(1, 0, size, l, r);
    }

    inline int32_t get_nearest_to_right(int32_t l, int32_t r) {
        return _get_nearest_to_right(1, 0, size, l, r);
    }
};

vector<vector<int32_t>> g;
const int32_t maxn = 1000001, logn = 21;
//int32_t up[maxn][logn];
int32_t tin[maxn], tout[maxn];
int32_t levels[maxn];
int32_t parents[maxn];
bool subg[maxn];

int32_t t = 0;

//inline bool anc(int32_t v, int32_t u) {
//    return tin[u] >= tin[v] && tin[u] < tout[v];
//}
//
//int32_t lca(int32_t v, int32_t u) {
//    if (anc(v, u)) return v;
//    if (anc(u, v)) return u;
//    for (int l = logn - 1; l >= 0; --l) if (!anc(up[v][l], u)) v = up[v][l];
//    return up[v][0];
//}

//int32_t dist(int32_t v, int32_t u) {
//    return levels[v] + levels[u] - levels[lca(v, u)] * 2;
//}

void dfs(int32_t v, int32_t level = 0, int32_t p = -1) {
//    for (int32_t l = 1; l < logn; ++l)
//        up[v][l] = up[up[v][l - 1]][l - 1];
    tin[v] = t++;
    levels[v] = level;
    parents[v] = p;
    for (int u: g[v]) {
        if (u == p) continue;
//        up[u][0] = v;
        dfs(u, level + 1, v);
    }
    tout[v] = t;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, k;
    cin >> n >> k;
    g.resize(n);
    int32_t a, b;
    for (int32_t i = 0; i + 1 < n; ++i) {
        cin >> a >> b, --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(n - 1);
    vector<int32_t> start_seg_tree(n);
    for (int32_t i = 0; i < n; ++i) start_seg_tree[tin[i]] = levels[i];
    SegmentTree<int32_t> st(start_seg_tree);
    int32_t subg_size = 1;
    subg[n - 1] = true;
    for (int32_t i = n - 2; i >= 0; --i) {
        auto level = st.get_max(tin[i], tin[i] + 1);
        if (n < level + subg_size + k) continue;
        for (int32_t j = i; !subg[j]; j = parents[j]) {
            subg[j] = true;
            ++subg_size;
            st.add(tin[j], tout[j], -1);
        }
    }
    for (int32_t i = 0; i < n; ++i) {
        if (!subg[i]) cout << i + 1 << "\n";
    }
    return 0;
}
