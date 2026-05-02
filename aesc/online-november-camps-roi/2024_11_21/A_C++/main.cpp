#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
using ll = int64_t;
constexpr int maxn = 3e5 + 1;
int n;
ll s;
set<int> g[maxn];
int p[maxn];
int vals[maxn];
ll dpv[maxn];

struct DEVal {
    ll max_profit;
    int last_bought_v;
};

map<ll, DEVal> dwv[maxn];

void dfs_fg(int v) {
    ll svals = 0;
    for (auto u: g[v]) dfs_fg(u), svals += dpv[u];
    dpv[v] = std::max<ll>(0, svals + vals[v]);
}

void dwv_dfs(int v) {
    for (auto u: g[v]) dwv_dfs(u);
    if (v == 0) return;
    if (vals[v] >= 0) dwv[v].emplace(0, DEVal{vals[v], v});
    else dwv[v].emplace(-vals[v], DEVal{vals[v], v});
    ll csc = vals[v] < 0 ? -vals[v] : 0;
    ll profit = vals[v];
    for (auto u: g[v]) {
        for (auto [child_start_cap, cdv]: dwv[u]) {
            auto it = dwv[v].find(child_start_cap + csc);
            if (it != dwv[v].end()) {
                if (it->second.max_profit < profit + cdv.max_profit)
                    it->second = DEVal{profit + cdv.max_profit, cdv.last_bought_v};
            } else {
                dwv[v].emplace(child_start_cap + csc, DEVal{profit + cdv.max_profit, cdv.last_bought_v});
            }
        }
    }
}

void solve() {
    cin >> n >> s;
    ++n;
    for (int i = 1, cp; i < n; ++i) {
        cin >> vals[i] >> cp;
        p[i] = cp;
        g[cp].insert(i);
    }
    vals[0] = 0;
    if (s == 1e18) {
        dfs_fg(0);
        cout << dpv[0];
        return;
    }
    dwv_dfs(0);
    while (true) {
        bool ofound = false;
        for (auto u: g[0]) {
            auto it = dwv[u].upper_bound(s);
            if(it==dwv[u].end()) 
        }
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
