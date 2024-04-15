#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<typename T>
class SparseTable {
public:
    vector<vector<pair<T, int32_t>>> st;

    void init_rows() {
        for (int32_t k = 1; k < st.size(); ++k)
            for (int32_t i = 0; i + (1 << (k - 1)) < st[k].size(); ++i)
                st[k][i] = st[k - 1][i].first < st[k - 1][i + (1 << (k - 1))].first
                           ? st[k - 1][i] : st[k - 1][i + (1 << (k - 1))];
    }

    [[nodiscard]] inline int32_t min_pos(int32_t l, int32_t r) const {
        int32_t k = __lg(r - l);
        return st[k][l].first < st[k][r - (1 << k)].first ? st[k][l].second : st[k][r - (1 << k)].second;
    }

    explicit SparseTable(const vector<T> &nums) : st(__lg(nums.size()) + 1,
                                                     vector<pair<T, int32_t>>(nums.size())) {
        auto it = nums.begin();
        for (int32_t i = 0; i < nums.size(); ++i) {
            st[0][i].first = *(it++);
            st[0][i].second = i;
        }
        init_rows();
    }
};

void dfs(const vector<list<int32_t>> &nodes, vector<int32_t> &tin, vector<int32_t> &tout, vector<int32_t> &depths,
         vector<int32_t> &verts, int32_t v, int32_t depth) {
    tin[v] = verts.size();
    depths.push_back(depth);
    verts.push_back(v);
    for (auto u: nodes[v]) {
        dfs(nodes, tin, tout, depths, verts, u, depth + 1);
        tout[v] = verts.size();
        depths.push_back(depth);
        verts.push_back(v);
    }
    if (nodes[v].empty()) tout[v] = verts.size() - 1;
}

inline bool is_child(const vector<int32_t> &tin, const vector<int32_t> &tout, int32_t v, int32_t u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t n, m;
    cin >> n >> m;
    vector<list<int32_t>> nodes(n);
    for (int32_t i = 1, p; i < n; ++i) {
        cin >> p;
        nodes[p].push_back(i);
    }
    vector<int32_t> tin(n), tout(n), vdepths, verts;
    vdepths.reserve(n * 3);
    verts.reserve(n * 3);
    dfs(nodes, tin, tout, vdepths, verts, 0, 0);
    SparseTable<int32_t> depths(vdepths);
    int32_t a1, a2;
    int64_t x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    int64_t result = 0;
    int32_t v = a1, u = a2, rv;
    for (int32_t i = 1; i <= m; ++i) {
        if (i > 1) {
            a1 = static_cast<int32_t>((x * a1 + y * a2 + z) % n);
            a2 = static_cast<int32_t>((x * a2 + y * a1 + z) % n);
            v = (a1 + rv) % n;
            u = a2;
        }
        if (tin[v] > tin[u]) swap(v, u);
        if (is_child(tin, tout, v, u)) rv = v;
        else rv = verts[depths.min_pos(tout[v], tin[u])];
        result += rv;
    }
    cout << result;
    return 0;
}