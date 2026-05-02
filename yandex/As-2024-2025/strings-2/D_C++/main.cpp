#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

constexpr int maxn = 1e5;

map<vector<int>, int> hashes_cache;
vector<int> g[maxn];
int weights[maxn];
int cnt_by_hash[maxn];
int hash_by_v[maxn];

void dfs(int v, int p) {
    if (p != -1) g[v].erase(find(g[v].begin(), g[v].end(), p));
    for (auto u: g[v]) dfs(u, v);
    for (auto &u: g[v]) u = hash_by_v[u];
    sort(g[v].begin(), g[v].end());
    g[v].push_back(weights[v]);
    auto [it, instd] = hashes_cache.emplace(g[v], hashes_cache.size());
    hash_by_v[v] = it->second;
    ++cnt_by_hash[hash_by_v[v]];
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) cin >> weights[i];
    dfs(0, -1);
    ll ans = 0;
    for (int hv = 0; hv < hashes_cache.size(); ++hv)
        if (cnt_by_hash[hv] >= 2)
            ans += 1ll * cnt_by_hash[hv] * (cnt_by_hash[hv] - 1) / 2;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
