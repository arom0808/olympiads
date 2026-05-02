#pragma GCC optimize("Ofast,O3")
// #pragma GCC target("avx,avx2")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_zip_pos(int val, const vector<int> &fzn) {
    return lower_bound(fzn.begin(), fzn.end(), val) - fzn.begin();
}

class ST {
public:
    struct Node {
        int max_val, change;

        void init(int val) {
            max_val = val, change = 0;
        }
    };

private:
    vector<int> fzn;
    vector<Node> tree;

    void upd_from_children(int v, int l, int r) {
        if (r - l <= 1) return;
        tree[v].max_val = std::max(tree[v * 2].max_val, tree[v * 2 + 1].max_val);
    }

    void push(int v, int l, int r) {
        if (!tree[v].change) return;
        if (r - l > 1) {
            tree[v * 2].max_val += tree[v].change, tree[v * 2].change += tree[v].change;
            tree[v * 2 + 1].max_val += tree[v].change, tree[v * 2 + 1].change += tree[v].change;
        }
        tree[v].change = 0;
    }

    void _build(int v, int l, int r, const vector<int> &all_arr) {
        if (r - l == 1) {
            tree[v].init(all_arr[fzn[l]]);
            return;
        }
        _build(v * 2, l, (l + r) / 2, all_arr);
        _build(v * 2 + 1, (l + r) / 2, r, all_arr);
        upd_from_children(v, l, r);
    }

    void _add(int v, int l, int r, int a, int b, int val) {
        if (l >= b || a >= r) return;
        if (a <= l && r <= b) {
            tree[v].max_val += val, tree[v].change += val;
            return;
        }
        push(v, l, r);
        _add(v * 2, l, (l + r) / 2, a, b, val);
        _add(v * 2 + 1, (l + r) / 2, r, a, b, val);
        upd_from_children(v, l, r);
    }

    int _max_val(int v, int l, int r, int a, int b) {
        if (l >= b || a >= r) return 0;
        if (a <= l && r <= b) return tree[v].max_val;
        push(v, l, r);
        return std::max(_max_val(v * 2, l, (l + r) / 2, a, b), _max_val(v * 2 + 1, (l + r) / 2, r, a, b));
    }

    void zip_coords(int &a, int &b) {
        a = get_zip_pos(a, fzn);
        b = get_zip_pos(b, fzn);
    }

public:
    int size;

    void build(const vector<int> &nvals, const vector<int> &all_arr) {
        fzn = nvals;
        size = nvals.size();
        _build(1, 0, size, all_arr);
    }

    void add(int a, int b, int val) {
        zip_coords(a, b);
        _add(1, 0, size, a, b, val);
    }

    int max_val(int a, int b) {
        zip_coords(a, b);
        return _max_val(1, 0, size, a, b);
    }

    void clear() {
        fzn.clear(), tree.clear();
        size = 0;
    }
};

constexpr int maxn = 2e5, maxa = 1e7;

int divs[maxa + 1];
vector<int> primes;

void resheto_init() {
    for (int k = 2; k <= maxa; ++k) {
        if (divs[k] == 0) {
            divs[k] = k;
            primes.push_back(k);
        }
        for (auto x: primes) {
            if (x > divs[k] || 1ll * x * divs[k] > maxa) break;
            divs[k * x] = x;
        }
    }
}

vector<int> g[maxn];
int n;
int as[maxn];
vector<int> euler;
int tin[maxn], tout[maxn];
int distf0[maxn];
vector<int> all_divs;
vector<vector<int> > poss;
vector<ST> sts;
int ans[maxn];

void dfs1(int v, int dist = 0, int p = -1) {
    distf0[v] = dist;
    tin[v] = euler.size();
    tout[v] = euler.size() - 1;
    euler.push_back(v);
    for (auto u: g[v]) {
        if (u == p) continue;
        dfs1(u, dist + 1, v);
        tout[v] = euler.size();
        euler.push_back(v);
    }
}

void dfs2(int v, int p = -1) {
    int ans = 0;
    for (int val = as[v], cdiv = divs[val], ldiv = -1; val > 1; ldiv = cdiv, val /= cdiv, cdiv = divs[val]) {
        if (cdiv == ldiv) continue;
        auto pid = get_zip_pos(cdiv, all_divs);
        ans = std::max(ans, sts[pid].max_val(0, sts[pid].size));
    }
}

pair<int, int> subtree_tins(int v) {
    return make_pair(tin[v], tout[v] + 1);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> as[i];
    for (int i = 0; i < n; ++i) g[i].clear();
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[v].push_back(u), g[u].push_back(v);
    }
    euler.clear();
    dfs1(0);
    all_divs.clear();
    for (int i = 0; i < n; ++i) {
        for (int val = as[i], cdiv = divs[val]; val > 1; val /= cdiv, cdiv = divs[val]) all_divs.push_back(cdiv);
    }
    sort(all_divs.begin(), all_divs.end());
    all_divs.erase(unique(all_divs.begin(), all_divs.end()), all_divs.end());
    poss.resize(all_divs.size());
    for (int i = 0; i < all_divs.size(); ++i) poss[i].clear();
    for (int i = 0; i < n; ++i) {
        for (int val = as[i], cdiv = divs[val], ldiv = -1; val > 1; ldiv = cdiv, val /= cdiv, cdiv = divs[val]) {
            if (cdiv == ldiv) continue;
            poss[get_zip_pos(cdiv, all_divs)].push_back(tin[i]);
        }
    }
    for (auto &cposs: poss) sort(cposs.begin(), cposs.end());
    vector<int> start_st_vals(euler.size());
    sts.resize(all_divs.size());
    for (int i = 0; i < all_divs.size(); ++i) sts.clear();
    for (int i = 0; i < n; ++i) start_st_vals[tin[i]] = distf0[i];
    for (int i = 0; i < all_divs.size(); ++i) sts[i].build(poss[i], start_st_vals);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    resheto_init();
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
