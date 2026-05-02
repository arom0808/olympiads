#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int32_t maxn = 1e5;

//int32_t parents[maxn];
//vector<pair<int32_t, int32_t>> childs[maxn];
vector<int32_t> firsts[maxn], seconds[maxn];
vector<pair<int32_t, int32_t>> g[maxn];
map<int32_t, int64_t> dist_firsts[maxn], dist_seconds[maxn];
int64_t result[maxn];
int64_t dists[maxn];
int32_t tin[maxn], tout[maxn];
vector<int32_t> euler_arr, euler_depth;
vector<int32_t> plan_firsts[maxn], plan_seconds[maxn];
int32_t n, q;
//int32_t timer = 0;

//void dfs1(int32_t v, int32_t p = -1) {
//    parents[v] = p;
//    for (auto u: g[v]) {
//        if (u.first == p) continue;
//        childs[v].push_back(u);
//        dfs1(u.first, v);
//    }
//}

void dfs2(int32_t v, int32_t p = -1) {
    for (auto [u, c]: g[v]) {
        if (u == p) continue;
        dfs2(u, v);
        if (dist_firsts[v].empty()) {
            dist_firsts[u].swap(dist_firsts[v]);
            for (auto &[plan, dist]: dist_firsts[v]) dist += c;
        } else {
            for (auto [plan, dist]: dist_firsts[u]) {
                auto it = dist_firsts[v].find(plan);
                if (it == dist_firsts[v].end()) dist_firsts[v].emplace(plan, dist + c);
                else if (it->second > dist + c) it->second = dist + c;
            }
        }
        if (dist_seconds[v].empty()) {
            dist_seconds[u].swap(dist_seconds[v]);
            for (auto &[plan, dist]: dist_seconds[v]) dist += c;
        } else {
            for (auto [plan, dist]: dist_seconds[u]) {
                auto it = dist_seconds[v].find(plan);
                if (it == dist_seconds[v].end()) dist_seconds[v].emplace(plan, dist + c);
                else if (it->second > dist + c) it->second = dist + c;
            }
        }
    }
    for (auto plan: firsts[v]) {
        auto it = dist_firsts[v].find(plan);
        if (it == dist_firsts[v].end()) dist_firsts[v].emplace(plan, 0);
        else it->second = 0;
    }
    for (auto plan: seconds[v]) {
        auto it = dist_seconds[v].find(plan);
        if (it == dist_seconds[v].end()) dist_seconds[v].emplace(plan, 0);
        else it->second = 0;
    }
    auto it1 = dist_firsts[v].begin(), it2 = dist_seconds[v].begin();
    while (it1 != dist_firsts[v].end() && it2 != dist_seconds[v].end()) {
        while (it1 != dist_firsts[v].end() && it2 != dist_seconds[v].end() && it1->first != it2->first) {
            while (it1 != dist_firsts[v].end() && it1->first < it2->first) ++it1;
            if (it1 != dist_firsts[v].end())
                while (it2 != dist_seconds[v].end() && it2->first < it1->first)
                    ++it2;
        }
        if (it1 != dist_firsts[v].end() && it2 != dist_seconds[v].end()) {
            if (result[it1->first] == -1 || result[it1->first] > it1->second + it2->second)
                result[it1->first] = it1->second + it2->second;
            ++it1, ++it2;
        }
    }
}

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

void dfs3(int32_t v, int64_t nd = 0, int32_t depth = 0, int32_t p = -1) {
    dists[v] = nd;
    tin[v] = euler_arr.size();
    euler_arr.push_back(v), euler_depth.push_back(depth);
    for (auto [u, c]: g[v]) {
        if (u == p) continue;
        dfs3(u, nd + c, depth + 1, v);
        tout[v] = euler_arr.size();
        euler_arr.push_back(v), euler_depth.push_back(depth);
    }
    if (g[v].size() <= 1) tout[v] = euler_arr.size() - 1;
}

inline bool is_child(int32_t v, int32_t u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

void third_group() {
    dfs3(0);
    SparseTable<int32_t> depths(euler_depth);
    for (int32_t plan = 0; plan < q; ++plan) {
        for (auto _v: plan_firsts[plan]) {
            for (auto _u: plan_seconds[plan]) {
                int32_t v = _v, u = _u, r;
                if (tin[v] > tin[u]) swap(v, u);
                if (is_child(v, u)) r = v;
                else r = euler_arr[depths.min_pos(tout[v], tin[u])];
                int64_t r_s = dists[u] + dists[v] - dists[r] * 2;
                if (result[plan] == -1 || result[plan] > r_s) result[plan] = r_s;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (auto &val: result) val = -1;
    cin >> n >> q;
    for (int32_t i = 0, u, v, c; i + 1 < n; ++i) {
        cin >> u >> v >> c, --u, --v;
        g[u].emplace_back(v, c), g[v].emplace_back(u, c);
    }
    for (int64_t i = 0, s, t; i < q; ++i) {
        cin >> s >> t;
        if (q * s * t < 100000000) {
            for (int32_t j = 0, r = 0; j < s; ++j)
                cin >> r, plan_firsts[i].push_back(r - 1);
            for (int32_t j = 0, r = 0; j < t; ++j)
                cin >> r, plan_seconds[i].push_back(r - 1);
        } else {
            for (int32_t j = 0, r = 0; j < s; ++j)
                cin >> r, firsts[r - 1].push_back(i);
            for (int32_t j = 0, r = 0; j < t; ++j)
                cin >> r, seconds[r - 1].push_back(i);
        }
    }
//    dfs1(0);
    dfs2(0);
    third_group();
//    if (q == 1) dfs2(0);
//    else third_group();
    for (int32_t i = 0; i < q; ++i) cout << result[i] << "\n";
//    for (auto val: result) cout << val << "\n";
    return 0;
}
