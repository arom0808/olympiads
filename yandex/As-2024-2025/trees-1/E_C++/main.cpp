#include <iostream>
#include <vector>
#include <map>

using namespace std;

constexpr int maxn = 1e5 + 2, maxlogn = 17, inf = 1e9;
pair<int, int> cbvl[maxn][maxlogn];
int sz[maxn], p_lev[maxn], colors[maxn];
bool used[maxn];
int n;
vector<int> g[maxn];
map<int, int> centroid_near_color[maxn];

int dfs_sz(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (auto u: g[v]) if (u != p) sz[v] += dfs_sz(u, v);
    return sz[v];
}

void dfs_proc_centroid(int v, int centroid, int level, int dist, int p = -1) {
    if (used[v]) return;
    p_lev[v] = level;
    cbvl[v][level] = {centroid, dist};
    auto it = centroid_near_color[centroid].emplace(colors[v], dist).first;
    if (it->second > dist) it->second = dist;
    for (auto u: g[v]) if (u != p) dfs_proc_centroid(u, centroid, level, dist + 1, v);
}

void find_proc_centroid(int v) {
    dfs_sz(v);
    int csz = sz[v] / 2;
    for (int found = 1, p = -1; found;) {
        found = 0;
        for (auto u: g[v]) {
            if (u == p || used[u] || sz[u] <= csz) continue;
            p = v, v = u, found = 1;
            break;
        }
    }
    dfs_proc_centroid(v, v, ++p_lev[v], 0);
    used[v] = true;
}

void solve() {
    cin >> n;
    for (int i = 1, p; i < n; ++i) {
        cin >> p;
        g[p].push_back(i), g[i].push_back(p);
    }
    for (int i = 0; i < n; ++i) cin >> colors[i];
    for (int i = 0; i < n; ++i) p_lev[i] = -1;
    for (int i = 0; i < n; ++i) for (int j = 0; j < maxlogn; ++j) cbvl[i][j].first = -1;
    for (int i = 0; i < n; ++i) while (!used[i]) find_proc_centroid(i);
    int q;
    cin >> q;
    for (int _ = 0; _ < q; ++_) {
        int v, c;
        cin >> v >> c;
        int ans = inf;
        for (int i = 0; i < maxlogn; ++i) {
            int cid = cbvl[v][i].first;
            if (cbvl[v][i].first == -1) break;
            auto it = centroid_near_color[cid].find(c);
            if (it != centroid_near_color[cid].end()) ans = std::min(ans, cbvl[v][i].second + it->second);
        }
        if (ans == inf) cout << "-1 ";
        else cout << ans << " ";
    }
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
