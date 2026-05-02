#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;

constexpr int64_t inf = 1e18;

template<typename T>
class SparseTable {
public:
    vector<vector<pair<T, int32_t> > > st;

    void init_rows() {
        for (int32_t k = 1; k < st.size(); ++k)
            for (int32_t i = 0; i + (1 << (k - 1)) < st[k].size(); ++i)
                st[k][i] = st[k - 1][i].first < st[k - 1][i + (1 << (k - 1))].first
                               ? st[k - 1][i]
                               : st[k - 1][i + (1 << (k - 1))];
    }

    [[nodiscard]] inline int32_t min_pos(int32_t l, int32_t r) const {
        int32_t k = __lg(r - l);
        return st[k][l].first < st[k][r - (1 << k)].first ? st[k][l].second : st[k][r - (1 << k)].second;
    }

    void init(const vector<T> &nums) {
        st.assign(__lg(nums.size()) + 1, vector<pair<T, int32_t> >(nums.size()));
        auto it = nums.begin();
        for (int32_t i = 0; i < nums.size(); ++i) {
            st[0][i].first = *(it++);
            st[0][i].second = i;
        }
        init_rows();
    }
};

constexpr int maxn = 5e5;

struct Edge {
    int v, cost;

    explicit Edge(int v = 0, int cost = 0): v(v), cost(cost) {
    }
};

vector<Edge> raw_g[maxn];
vector<Edge> g[maxn];
int raw_to_main_g[maxn];
int n, levels_cnt;
int tin[maxn], tout[maxn];
int level_on_id[maxn];
vector<int> ids_on_level[maxn];
vector<int> euler_depths;
SparseTable<int> sp;

void dfs(int v, int depth, int p = -1) {
    tin[v] = euler_depths.size();
    euler_depths.push_back(depth);
    for (auto [u,c]: g[v]) {
        if (u == p) continue;
        dfs(u, depth + 1, v);
        tout[v] = euler_depths.size();
        euler_depths.push_back(depth);
    }
    if (g[v].size() == 1) tout[v] = euler_depths.size() - 1;
}

bool is_child(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int dist(int v, int u) {
    if (tin[v] > tin[u]) swap(u, v);
    if (is_child(v, u)) return euler_depths[tin[u]] - euler_depths[tin[v]];
    return euler_depths[tin[v]] + euler_depths[tin[u]] - 2 * euler_depths[sp.min_pos(tout[v], tin[u])];
}

namespace ST {
    void _init(int v, int l, int r) {
        if (l >= r) return;
        if (r - l == 1) {
            g[n + v].emplace_back(l, 0);
            return;
        }
        g[n + v].emplace_back(n + v * 2, 0), g[n + v].emplace_back(n + v * 2 + 1, 0);
        _init(v * 2, l, (l + r) / 2), _init(v * 2 + 1, (l + r) / 2, r);
    }

    void _add_edges(int v, int l, int r, int a, int b, int from, int cost) {
        if (a >= r || l >= b) return;
        if (a <= l && r <= b) {
            g[from].emplace_back(v + n, cost);
            return;
        }
        _add_edges(v * 2, l, (l + r) / 2, a, b, from, cost);
        _add_edges(v * 2 + 1, (l + r) / 2, r, a, b, from, cost);
    }

    void init() {
        _init(1, 0, n);
    }

    void add_edges(int a, int b, int from, int cost) {
        _add_edges(1, 0, n, a, b, from, cost);
    }
}

pair<int, int> get_seg_for_v(const vector<int> &vs, int c_val, int max_dist, int delta) {
    auto cpos = distance(vs.begin(), lower_bound(vs.begin(), vs.end(), c_val));
    int l = -1, r = cpos;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (dist(vs[mid], c_val) <= max_dist) r = mid;
        else l = mid;
    }
    auto ansl = r;
    l = cpos, r = vs.size();
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (dist(vs[mid], c_val) <= max_dist) l = mid;
        else r = mid;
    }
    return {ansl + delta, l + delta};
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int s, f;
    cin >> n >> s >> f;
    for (int i = 1, a, b, c; i < n; ++i) {
        cin >> a >> b >> c, --a, --b;
        raw_g[a].emplace_back(b, c), raw_g[b].emplace_back(a, c);
    }
    vector<pair<int, int> > que1, que2;
    que1.emplace_back(0, -1); // orig v, new v
    raw_to_main_g[0] = 0;
    level_on_id[0] = 0;
    ids_on_level[0].push_back(0);
    levels_cnt = 1;
    for (int level = 0, counter = 1; !que1.empty(); ++level) {
        for (auto [v, p]: que1) {
            for (auto [u,c]: raw_g[v]) {
                if (u == p) continue;
                raw_to_main_g[u] = counter++;
                level_on_id[raw_to_main_g[u]] = level + 1;
                ids_on_level[level + 1].push_back(raw_to_main_g[u]);
                que2.emplace_back(u, v);
                levels_cnt = level + 2;
            }
        }
        swap(que1, que2);
        que2.clear();
    }
    for (int v = 0; v < n; ++v)
        for (auto [u,c]: raw_g[v])
            g[raw_to_main_g[v]].emplace_back(raw_to_main_g[u], c);
    dfs(0, 0, -1);
    sp.init(euler_depths);
    vector<int> pf_levels(levels_cnt + 1, 0);
    for (int i = 0; i < levels_cnt; ++i) pf_levels[i + 1] = pf_levels[i] + ids_on_level[i].size();
    ST::init();
    for (int i = 1, d, m; i < n; ++i) {
        auto ri = raw_to_main_g[i];
        cin >> d >> m;
        auto level_id = level_on_id[ri];
        auto [cl,cr] = get_seg_for_v(ids_on_level[level_id], ri, m, pf_levels[level_id]);
        ST::add_edges(cl, cr + 1, ri, d);
    }
    s = raw_to_main_g[s - 1], f = raw_to_main_g[f - 1];
    vector<int64_t> d(maxn, inf);
    d[s] = 0;
    set<pair<int64_t, int> > qq;
    qq.emplace(0, s);
    while (!qq.empty()) {
        auto v = qq.begin()->second;
        qq.erase(qq.begin());
        for (auto [u,c]: g[v]) {
            if (d[u] > d[v] + c) {
                qq.erase({d[u], u});
                d[u] = d[v] + c;
                qq.insert({d[u], u});
            }
        }
    }
    cout << d[f] << "\n";
    return 0;
}
