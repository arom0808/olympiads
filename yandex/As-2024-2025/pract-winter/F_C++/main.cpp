#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e5;

namespace ST {
    constexpr int N = 1 << 17;

    struct Node {
        vector<pair<int, int> > vals;
        vector<int> pf;
    };

    struct STAns {
        int fsum = 0, csum = 0, ccnt = 0;

        STAns &operator+=(const STAns &rhs) {
            fsum += rhs.fsum, csum += rhs.csum, ccnt += rhs.ccnt;
            return *this;
        }

        void add_node(const Node &node, int c) {
            int i1 = lower_bound(node.vals.begin(), node.vals.end(), make_pair(c, 0)) - node.vals.begin();
            int i2 = lower_bound(node.vals.begin(), node.vals.end(), make_pair(c + 1, 0)) -
                     node.vals.begin();
            ccnt += i2 - i1;
            csum += node.pf[i2] - node.pf[i1];
            fsum += node.pf[node.vals.size()];
        }
    };

    Node tree[N * 2];

    void init(const pair<int, int> *arr, const int arr_size) {
        for (int i = 0; i < arr_size; ++i) {
            tree[i + N].vals.push_back(arr[i]);
            tree[i + N].pf.resize(2);
            tree[i + N].pf[0] = 0;
            tree[i + N].pf[1] = arr[i].second;
        }
        for (int i = N - 1; i; --i) {
            auto &cn = tree[i], ln = tree[i << 1], rn = tree[i << 1 | 1];
            cn.vals.resize(ln.vals.size() + rn.vals.size());
            merge(ln.vals.begin(), ln.vals.end(), rn.vals.begin(), rn.vals.end(), cn.vals.begin());
            cn.pf.resize(cn.vals.size() + 1);
            cn.pf[0] = 0;
            for (int j = 0; j < cn.vals.size(); ++j) cn.pf[j + 1] = cn.pf[j] + cn.vals[j].second;
        }
    }

    STAns req(int l, int r, int c) {
        l += N, r += N;
        STAns ans;
        while (l < r) {
            if (l & 1) ans.add_node(tree[l++], c);
            if (r & 1) ans.add_node(tree[--r], c);
            l >>= 1, r >>= 1;
        }
        return ans;
    }
}

struct RawEd {
    int u, c, d;
};

vector<RawEd> raw_g[maxn];
int tin[maxn], tout[maxn], sz[maxn], head[maxn], par[maxn];
vector<int> g[maxn];
pair<int, int> cd_arr[maxn], for_st_arr[maxn];
int timer = 0;

void dfs1(int v, int p = -1) {
    par[v] = p;
    sz[v] = 1;
    for (auto [u,c,d]: raw_g[v]) {
        if (u == p) continue;
        g[v].push_back(u);
        cd_arr[u] = {c, d};
        dfs1(u, v);
        sz[v] += sz[u];
    }
}

void dfs2(int v) {
    tin[v] = timer++;
    for (auto &u: g[v]) if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
    for (auto u: g[v]) {
        head[u] = (u == g[v][0]) ? head[v] : u;
        dfs2(u);
    }
    tout[v] = timer;
}

bool anc(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void up(int &a, int &b, int c, ST::STAns &ans) {
    while (!anc(head[a], b)) {
        ans += ST::req(tin[head[a]], tin[a] + 1, c);
        a = par[head[a]];
    }
}

int get_ans(int a, int b, int c, int nd) {
    ST::STAns ans;
    up(a, b, c, ans);
    up(b, a, c, ans);
    if (!anc(a, b)) swap(a, b);
    ans += ST::req(tin[a] + 1, tin[b] + 1, c);
    return ans.fsum - ans.csum + ans.ccnt * nd;
}

int n, q;

void solve() {
    cin >> n >> q;
    for (int i = 1, a, b, c, d; i < n; ++i) {
        cin >> a >> b >> c >> d, --a, --b, --c;
        raw_g[a].emplace_back(b, c, d), raw_g[b].emplace_back(a, c, d);
    }
    dfs1(0);
    head[0] = 0;
    dfs2(0);
    for (int i = 0; i < n; ++i) for_st_arr[tin[i]] = cd_arr[i];
    ST::init(for_st_arr, n);
    for (int i = 0, x, y, u, v; i < q; ++i) {
        cin >> x >> y >> u >> v, --x, --u, --v;
        cout << get_ans(u, v, x, y) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
