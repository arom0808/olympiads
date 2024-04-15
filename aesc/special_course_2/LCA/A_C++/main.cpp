#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<typename T>
class SparseTable {
    vector<vector<pair<T, int64_t>>> st;

    void init_rows() {
        for (int64_t k = 1; k < st.size(); ++k)
            for (int64_t i = 0; i + (1 << (k - 1)) < st[k].size(); ++i)
                st[k][i] = st[k - 1][i].first < st[k - 1][i + (1 << (k - 1))].first
                           ? st[k - 1][i] : st[k - 1][i + (1 << (k - 1))];
    }

public:
    [[nodiscard]] int64_t min_pos(int64_t l, int64_t r) const {
        int64_t k = __lg(r - l);
        return st[k][l].first < st[k][r - (1 << k)].first ? st[k][l].second : st[k][r - (1 << k)].second;
    }

    explicit SparseTable(const list<T> &nums) : st(__lg(nums.size()) + 1,
                                                   vector<pair<T, int64_t>>(nums.size())) {
        auto it = nums.begin();
        for (int64_t i = 0; i < nums.size(); ++i) {
            st[0][i].first = *(it++);
            st[0][i].second = i;
        }
        init_rows();
    }
};

struct Node {
    int64_t p = -1;
    list<int64_t> childs;
};

void dfs(const vector<Node> &nodes, vector<int64_t> &tin, vector<int64_t> &tout, list<int64_t> &ldepths,
         list<int64_t> &lverts, int64_t v, int64_t depth) {

    tin[v] = lverts.size();
    ldepths.push_back(depth);
    lverts.push_back(v);
    for (auto u: nodes[v].childs) {
        dfs(nodes, tin, tout, ldepths, lverts, u, depth + 1);
        tout[v] = lverts.size();
        ldepths.push_back(depth);
        lverts.push_back(v);
    }
    if (nodes[v].childs.empty()) tout[v] = lverts.size() - 1;
}

inline bool is_child(const vector<int64_t> &tin, const vector<int64_t> &tout, int64_t v, int64_t u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int main() {
    int64_t n, m;
    cin >> n >> m;
    vector<Node> nodes(n);
    for (int64_t i = 1; i < n; ++i) {
        cin >> nodes[i].p;
        nodes[nodes[i].p].childs.push_back(i);
    }
    vector<int64_t> tin(n), tout(n);
    list<int64_t> ldepths, lverts;
    dfs(nodes, tin, tout, ldepths, lverts, 0, 0);
    SparseTable<int64_t> depths(ldepths);
    vector<int64_t> verts(lverts.size());
    copy(lverts.begin(), lverts.end(), verts.begin());
    vector<int64_t> ars(m * 2 + 1);
    cin >> ars[1] >> ars[2];
    int64_t x, y, z;
    cin >> x >> y >> z;
    for (int64_t i = 3; i <= m * 2; ++i) ars[i] = (x * ars[i - 2] + y * ars[i - 1] + z) % n;
    int64_t result = 0;
    int64_t v = ars[1], u = ars[2], rv;
    for (int64_t i = 1; i <= m; ++i) {
        if (i > 1) {
            v = (ars[2 * i - 1] + rv) % n;
            u = ars[2 * i];
        }
        if (tin[v] > tin[u]) swap(v, u);
        if (is_child(tin, tout, v, u)) rv = v;
        else rv = verts[depths.min_pos(tout[v], tin[u])];
        result += rv;
    }
    cout << result;
    return 0;
}
