#include <iostream>
#include <vector>
#include <functional>

using namespace std;

constexpr int maxn = 1e6 + 10, inf = 2e9;

namespace DD {
    struct Node {
        int min_x, x, h, prior;
        Node *left = nullptr, *right = nullptr;
    };

    constexpr int max_nodes_cnt = 1e7;
    Node tree[max_nodes_cnt];
    // Node* zero_node =
};

struct ST_high {
    ordered_map<int, int> vals;
    int shift;

    void init() {
        vals.clear();
        shift = maxn;
    }

    void swap(ST_high &rhs) {
        vals.swap(rhs.vals);
        std::swap(shift, rhs.shift);
    }

    int get_leftest_less(int x) {
        if (vals.empty()) return inf;
        int l = -1, r = vals.size() - 1;
        while (r - l != 1) {
            int m = (l + r) >> 1;
            int cv = vals.find_by_order(m)->second;
            if (cv >= x) l = m;
            else r = m;
        }
        auto it = vals.find_by_order(r);
        if (it->second < x) return it->first - shift;
        return inf;
    }

    void set_min_eq(int a, int b, int val) {
        a += shift, b += shift;
        if (b - a == 1) {
            auto it = vals.insert(make_pair(a, val)).first;
            if (it->second > val) it->second = val;
            if (it != vals.begin() && prev(it)->second <= it->second) vals.erase(it);
            else
                while (next(it) != vals.end() && it->second <= next(it)->second)
                    vals.erase(next(it));
        } else {
            vals.insert(make_pair(a, val));
            if (vals.begin()->second > val) vals.begin()->second = val;
            auto it = vals.begin();
            it->second = std::min(it->second, val);
            while (next(it) != vals.end() && it->second <= next(it)->second)
                vals.erase(next(it));
        }
    }

    void increase_h() {
        --shift;
    }

    void list_vals(const function<void(int, int)> &f) {
        for (auto [h, v]: vals) f(h - shift, v);
    }

    void del() {
        vals.clear();
    }
};

struct ST_low {
    ordered_map<int, int> vals;
    int shift;

    void swap(ST_low &rhs) {
        vals.swap(rhs.vals);
        std::swap(shift, rhs.shift);
    }

    void init() {
        vals.clear();
        shift = maxn;
    }

    int get_leftest_greater(int x) {
        if (vals.empty()) return inf;
        x = -x;
        int l = -1, r = vals.size() - 1;
        while (r - l != 1) {
            int m = (l + r) >> 1;
            int cv = vals.find_by_order(m)->second;
            if (cv >= x) l = m;
            else r = m;
        }
        auto it = vals.find_by_order(r);
        if (it->second < x) return it->first - shift;
        return inf;
        // int ans = ST::_get_leftest_less(root, 0, maxn << 1, -x);
        // if (ans == inf) return ans;
        // return ST::_get_leftest_less(root, 0, maxn << 1, -x) - shift;
    }

    void set_max_eq(int a, int b, int val) {
        val = -val;
        a += shift, b += shift;
        if (b - a == 1) {
            auto it = vals.insert(make_pair(a, val)).first;
            if (it->second > val) it->second = val;
            if (it != vals.begin() && prev(it)->second <= it->second) vals.erase(it);
            else
                while (next(it) != vals.end() && it->second <= next(it)->second)
                    vals.erase(next(it));
        } else {
            vals.insert(make_pair(a, val));
            if (vals.begin()->second > val) vals.begin()->second = val;
            // if (vals.empty()) return;
            auto it = vals.begin();
            it->second = std::min(it->second, val);
            while (next(it) != vals.end() && it->second <= next(it)->second)
                vals.erase(next(it));
        }
        // ST::_set_min_eq(root, 0, maxn << 1, a + shift, b + shift, -val);
    }

    void increase_h() {
        --shift;
    }

    void list_vals(const function<void(int, int)> &f) {
        for (auto [h, v]: vals) f(h - shift, -v);
        // ST::_list_vals(root, 0, maxn << 1, [&f,this](int h, int v) { f(h - shift, -v); });
    }

    void del() {
        vals.clear();
    }
};


vector<int> low_borders[maxn], high_borders[maxn];
int n;
vector<int> g[maxn];
int hs[maxn];
ST_high high_sts[maxn];
ST_low low_sts[maxn];

void dfs1(int v, int h, int p = -1) {
    hs[v] = h;
    if (p != -1) g[v].erase(find(g[v].begin(), g[v].end(), p));
    for (auto u: g[v]) dfs1(u, h + 1, v);
    for (auto u: g[v]) hs[v] = std::max(hs[v], hs[u]);
    for (auto &u: g[v]) if (hs[u] > hs[g[v][0]]) swap(u, g[v][0]);
}

int dfs2(int v, int ki) {
    int ans = inf;
    for (auto u: g[v]) ans = std::min(ans, dfs2(u, ki));
    if (!g[v].empty()) {
        swap(high_sts[v], high_sts[g[v][0]]);
        swap(low_sts[v], low_sts[g[v][0]]);
    } else {
        low_sts[v].init();
        high_sts[v].init();
    }
    high_sts[v].increase_h();
    low_sts[v].increase_h();
    ans = std::min(ans, low_sts[v].get_leftest_greater(high_borders[ki][v]));
    ans = std::min(ans, high_sts[v].get_leftest_less(low_borders[ki][v]));
    low_sts[v].set_max_eq(0, n, low_borders[ki][v]);
    high_sts[v].set_min_eq(0, n, high_borders[ki][v]);
    for (int _ = 1; _ < g[v].size(); ++_) {
        int u = g[v][_];
        low_sts[u].list_vals([&ans,v](int h1, int val) {
            int h2 = high_sts[v].get_leftest_less(val);
            if (h1 != inf && h2 != inf) ans = std::min(ans, h1 + h2 + 1);
        });
        high_sts[u].list_vals([&ans, v](int h1, int val) {
            int h2 = low_sts[v].get_leftest_greater(val);
            if (h1 != inf && h2 != inf) ans = std::min(ans, h1 + h2 + 1);
        });
        low_sts[u].list_vals([v](int h, int val) {
            low_sts[v].set_max_eq(h + 1, h + 2, val);
        });
        high_sts[u].list_vals([v](int h, int val) {
            high_sts[v].set_min_eq(h + 1, h + 2, val);
        });
        low_sts[u].del();
        high_sts[u].del();
    }
    return ans;
}

int get_ans_ks(int ki) {
    for (int i = 0; i < n; ++i) low_sts[i].del();
    for (int i = 0; i < n; ++i) high_sts[i].del();
    return dfs2(0, ki);
}

void solve() {
    int k;
    cin >> n >> k;
    for (int i = 0; i < k; ++i) low_borders[i].resize(n);
    for (int i = 0; i < k; ++i) high_borders[i].resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) cin >> low_borders[j][i];
        for (int j = 0; j < k; ++j) cin >> high_borders[j][i];
        for (int j = 0; j < k; ++j)
            if (low_borders[j][i] > high_borders[j][i])
                swap(low_borders[j][i], high_borders[j][i]);
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs1(0, 0);
    int ans = inf;
    for (int i = 0; i < k; ++i) ans = std::min(ans, get_ans_ks(i));
    cout << ((ans == inf) ? (-1) : ans) << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
