#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 1e5 + 2, maxlogn = 17;

struct CentrInfo {
    int centroid, dist, color;
};

struct MV {
    int dist, color;

    bool operator<(const MV &rhs) const {
        return dist > rhs.dist;
    }
};

int vals[maxn];
vector<int> g[maxn];
CentrInfo cbv[maxn][maxlogn];
int n;
bool used[maxn];
int sz[maxn];
int p_level[maxn];
array<MV, 3> maxs[maxn];

int dfs_sz(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (auto u: g[v]) if (u != p) sz[v] += dfs_sz(u, v);
    return sz[v];
}

void dfs_process_centroid(int v, int p, int dist, int centr_id, int color, int level) {
    if (used[v]) return;
    p_level[v] = level;
    cbv[v][level] = {centr_id, dist, color};
    for (auto u: g[v]) if (u != p) dfs_process_centroid(u, v, dist + 1, centr_id, color, level);
}

void find_process_centroid(int v) {
    dfs_sz(v);
    int csz = sz[v] / 2;
    for (int found = 1, cp = -1; found;) {
        found = false;
        for (auto u: g[v]) {
            if (u == cp || used[u] || sz[u] <= csz) continue;
            cp = v, v = u, found = true;
            break;
        }
    }
    ++p_level[v];
    cbv[v][p_level[v]] = {v, 0, v};
    for (auto u: g[v]) dfs_process_centroid(u, v, 1, v, u, p_level[v]);
    used[v] = true;
}

void add_v_to_centroid(int v, int dist, int color) {
    maxs[v][2] = {dist, color};
    sort(maxs[v].begin(), maxs[v].end());
    if (maxs[v][0].color == maxs[v][1].color) swap(maxs[v][1], maxs[v][2]);
}

void enable_v(int v) {
    for (int i = 0; i < maxlogn; ++i) {
        if (cbv[v][i].centroid == -1) break;
        add_v_to_centroid(cbv[v][i].centroid, cbv[v][i].dist, cbv[v][i].color);
    }
}

int get_centr_max_dist_by_color(int v, int color) {
    if (maxs[v][0].color == color) return maxs[v][1].dist;
    return maxs[v][0].dist;
}

int find_longest_way(int v) {
    int ans = 0;
    for (int i = 0; i < maxlogn; ++i) {
        if (cbv[v][i].centroid == -1) break;
        int cans = get_centr_max_dist_by_color(cbv[v][i].centroid, cbv[v][i].color);
        if (cans != -1) ans = std::max(ans, cans + cbv[v][i].dist);
    }
    return ans;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> vals[i];
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int v = 0; v < n; ++v) for (int i = 0; i < maxlogn; ++i) cbv[v][i].centroid = -1;
    for (int v = 0; v < n; ++v) for (auto &[d,c]: maxs[v]) d = c = -1;
    for (int i = 0; i < n; ++i) p_level[i] = -1;
    for (int v = 0; v < n; ++v) while (!used[v]) find_process_centroid(v);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [](int a, int b) {
        return vals[a] > vals[b];
    });
    ll ans = 0;
    for (auto v: order) {
        ans = std::max(ans, 1ll * find_longest_way(v) * vals[v]);
        enable_v(v);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
