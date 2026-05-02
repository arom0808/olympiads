#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

constexpr int maxn = 3e5;

int par[maxn], vbr[maxn];
vector<int> g[maxn];
vector<pair<int, int> > raw_g[maxn];
bool banned[maxn];
int group, n;
int dp[maxn][2];

void g_p_vbr_dfs(int v, int p = -1) {
    par[v] = p;
    for (auto [u, rid]: raw_g[v]) {
        if (u == p) continue;
        vbr[rid] = u;
        g[v].push_back(u);
        g_p_vbr_dfs(u, v);
    }
}

void calc_dp(int v) {
    dp[v][0] = 0;
    for (int u: g[v]) if (!banned[u]) dp[v][0] += dp[u][1];
    dp[v][1] = 0;
    for (int u: g[v]) {
        if (banned[u]) continue;
        dp[v][1] = std::max(dp[v][1], dp[v][0] - dp[u][1] + dp[u][0] + 1);
    }
}

void start_dp_dfs(int v) {
    for (auto u: g[v]) start_dp_dfs(u);
    calc_dp(v);
}

void solve_2group() {
    int q;
    cin >> q;
    set<int> cbnd;
    for (int _ = 0, t, x; _ < q; ++_) {
        cin >> t >> x, --x;
        if (t == 1) {
            if (cbnd.contains(x)) cbnd.erase(x);
            else cbnd.insert(x);
        } else {
            int lb, rb;
            if (cbnd.lower_bound(x) == cbnd.end()) rb = n - 1;
            else rb = *cbnd.lower_bound(x);
            if (cbnd.lower_bound(x) == cbnd.begin()) lb = -1;
            else lb = *prev(cbnd.lower_bound(x));
            cout << (rb - lb) / 2 << "\n";
        }
    }
}

void solve() {
    cin >> group >> n;
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        raw_g[u].emplace_back(v, i), raw_g[v].emplace_back(u, i);
    }
    if (group == 2) {
        solve_2group();
        return;
    }
    g_p_vbr_dfs(0);
    for (int i = 0; i < n; ++i) sort(g[i].begin(), g[i].end());
    start_dp_dfs(0);
    int q;
    cin >> q;
    for (int _ = 0, t, x; _ < q; ++_) {
        cin >> t >> x, --x;
        if (t == 1) {
            x = vbr[x];
            banned[x] = !banned[x];
            for (int u = par[x]; u != -1; u = par[u]) calc_dp(u);
        } else {
            while (par[x] != -1 && !banned[x]) x = par[x];
            cout << std::max(dp[x][0], dp[x][1]) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
    return 0;
}
