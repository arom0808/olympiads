#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int maxn = 2e5, maxlogn = 20;
int n, q;
int xs[maxn];
int panss[maxn * 3];
vector<int> wr_pos[maxn];
vector<pair<int, int> > g[maxn];
int up[maxn][maxlogn];
int tin[maxn], tout[maxn];
int t = 0;

bool anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

void up_dfs(int v, int p = -1) {
    up[v][0] = (p == -1 ? 0 : p);
    for (int l = 1; l < maxlogn; ++l) up[v][l] = up[up[v][l - 1]][l - 1];
    tin[v] = t++;
    for (auto [u,c]: g[v]) if (u != p) up_dfs(u, v);
    tout[v] = t;
}

int lca(int v, int u) {
    if (anc(v, u)) return v;
    if (anc(u, v)) return u;
    for (int l = maxlogn - 1; l >= 0; --l) if (!anc(up[v][l], u)) v = up[v][l];
    return up[v][0];
}

ordered_multiset<int> cvals;

void ans_dfs(int v, int p = -1) {
    for (auto cp: wr_pos[v]) panss[cp] = cvals.order_of_key(xs[cp / 3] + 1);
    for (auto [u,c]: g[v]) {
        if (u == p) continue;
        cvals.insert(c);
        ans_dfs(u, v);
        cvals.erase(cvals.find_by_order(cvals.order_of_key(c)));
    }
}

void solve() {
    cin >> n >> q;
    for (int i = 1, a, b, l; i < n; ++i) {
        cin >> a >> b >> l, --a, --b;
        g[a].emplace_back(b, l), g[b].emplace_back(a, l);
    }
    up_dfs(0);
    for (int i = 0, a, b, x; i < q; ++i) {
        cin >> a >> b >> x, --a, --b;
        xs[i] = x;
        wr_pos[a].push_back(i * 3);
        wr_pos[b].push_back(i * 3 + 1);
        wr_pos[lca(a, b)].push_back(i * 3 + 2);
    }
    ans_dfs(0);
    for (int i = 0; i < q; ++i) cout << panss[i * 3] + panss[i * 3 + 1] - 2 * panss[i * 3 + 2] << "\n";
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
