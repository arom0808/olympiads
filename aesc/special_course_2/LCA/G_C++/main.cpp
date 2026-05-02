#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;


template<typename T>
class SparseTable {
public:
    int32_t log_size = 0, size = 0;
    vector<vector<pair<T, int32_t>>> table;

    SparseTable() = default;

    explicit SparseTable(const vector<T> &vals) {
        assign(vals);
    }

    void assign(const vector<T> &vals) {
        log_size = __lg(vals.size()) + 1, size = vals.size();
        table.clear();
        table.resize(log_size, vector<pair<T, int32_t>>(size, pair<T, int32_t>{0, 0}));
        for (int32_t i = 0; i < size; ++i) table[0][i] = {vals[i], i};
        for (int32_t i = 0; i + 1 < log_size; ++i)
            for (int32_t j = 0; j + (1 << i) < size; ++j)
                table[i + 1][j] = min(table[i][j], table[i][j + (1 << i)]);
    }

    int32_t min_pos(int32_t l, int32_t r) {
        int32_t t = __lg(r - l);
        return min(table[t][l], table[t][r - (1 << t)]).second;
    }
};

int32_t n, k;
vector<vector<pair<int32_t, int32_t>>> g;
vector<int32_t> euler, euler_depths, tin, tout, ans, weights;
SparseTable<int32_t> st;
int32_t t = 0;

bool anc(int32_t u, int32_t v) { // u -> v TODO: check with tin[v] < tout[u]
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int32_t lca(int32_t u, int32_t v) {
    if (tin[u] > tin[v]) swap(u, v);
    if (anc(u, v)) return u;
    return euler[st.min_pos(tout[u], tin[v])];
}

void dfs1(int32_t u, int32_t depth = 0, int32_t p = -1) {
    tin[u] = euler.size();
    euler.push_back(u), euler_depths.push_back(depth);
    for (auto [v, edge_id]: g[u]) {
        if (v == p) continue;
        dfs1(v, depth + 1, u);
        tout[u] = euler.size();
        euler.push_back(u), euler_depths.push_back(depth);
    }
    if (g[u].size() <= 1) tout[u] = euler.size() - 1;
}

int32_t dfs2(int32_t u, int32_t p = -1) {
    int32_t gw = 0;
    for (auto [v, e_id]: g[u]) {
        if (v == p) continue;
        int32_t cw = dfs2(v, u);
        ans[e_id] = cw;
        gw += cw;
    }
    return gw + weights[u];
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    g.resize(n);
    for (int32_t i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].emplace_back(v, i), g[v].emplace_back(u, i);
    }
    tin.resize(n), tout.resize(n), weights.resize(n);
    dfs1(0);
    st.assign(euler_depths);
    ans.resize(n - 1);
    cin >> k;
    for (int32_t i = 0, a, b; i < k; ++i) {
        cin >> a >> b, --a, --b;
        ++weights[a], ++weights[b], weights[lca(a, b)] -= 2;
    }
    dfs2(0);
    for (auto a: ans) cout << a << " ";
//    cin >> k;
//    for (int32_t i = 0; i <= 16; ++i) {
//        cout << i << ": " << __lg(i) << "\n";
//    }
    return 0;
}
