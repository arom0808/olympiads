#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e5, maxlogn = 17;
vector<pair<int, int> > g[maxn];
int centroid_by_level[maxn][maxlogn], dist_centroid_by_level[maxn][maxlogn];
int centroid_h[maxn];
int cur_par[maxn], par[maxn], sz[maxn];
bool used[maxn];
int n;

struct DT {
    int dist, color, time;
};

vector<DT> col_sts[maxn];
int timer = 0;

int dfs_sz(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (auto [u,w]: g[v]) if (u != p) sz[v] += dfs_sz(u, v);
    return sz[v];
}

void dfs_centroid_process(int v, int clevel, int cid, int cdist, int p = -1) {
    if (used[v]) return;
    centroid_by_level[v][clevel] = cid;
    dist_centroid_by_level[v][clevel] = cdist;
    cur_par[v] = cid;
    for (auto [u,w]: g[v]) if (u != p) dfs_centroid_process(u, clevel, cid, cdist + w, v);
}

void find_add_centroid(int v) {
    dfs_sz(v);
    int csz = sz[v];
    for (int found = 1, cp = -1; found;) {
        found = 0;
        for (auto [u,w]: g[v]) {
            if (used[u] || u == cp || sz[u] <= csz / 2) continue;
            cp = v, v = u, found = 1;
            break;
        }
    }
    par[v] = cur_par[v];
    int cur_level = (par[v] == -1) ? 0 : centroid_h[par[v]] + 1;
    centroid_h[v] = cur_level;
    dfs_centroid_process(v, cur_level, v, 0);
    used[v] = true;
}

void add_dt_to_centroid(int v, int c, int d) {
    if (d < 0) return;
    while (!col_sts[v].empty() && col_sts[v].back().dist <= d) col_sts[v].pop_back();
    col_sts[v].emplace_back(d, c, timer);
}

void process_req1(int v, int d, int c) {
    ++timer;
    for (int level = 0; level < maxlogn; ++level) {
        if (centroid_by_level[v][level] == -1) break;
        add_dt_to_centroid(centroid_by_level[v][level], c, d - dist_centroid_by_level[v][level]);
    }
}

pair<int, int> get_ans_in_centroid(int v, int d) {
    if (col_sts[v].empty()) return {-1, 0};
    int l = 0, r = col_sts[v].size();
    while (r - l != 1) {
        int m = (l + r) / 2;
        if (col_sts[v][m].dist >= d) l = m;
        else r = m;
    }
    if (col_sts[v][l].dist < d) return {-1, 0};
    return {col_sts[v][l].time, col_sts[v][l].color};
}

int process_req2(int v) {
    pair<int, int> ans{-1, 0};
    for (int level = 0; level < maxlogn; ++level) {
        if (centroid_by_level[v][level] == -1) break;
        ans = std::max(ans, get_ans_in_centroid(centroid_by_level[v][level], dist_centroid_by_level[v][level]));
    }
    return ans.second;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) for (int j = 0; j < maxlogn; ++j) centroid_by_level[i][j] = -1;
    for (int i = 0, u, v, w; i + 1 < n; ++i) {
        cin >> u >> v >> w, --u, --v;
        g[v].emplace_back(u, w), g[u].emplace_back(v, w);
    }
    for (int v = 0; v < n; ++v) cur_par[v] = -1;
    for (int v = 0; v < n; ++v) while (!used[v]) find_add_centroid(v);
    int q;
    cin >> q;
    for (int _ = 0, t, v, d, c; _ < q; ++_) {
        cin >> t >> v, --v;
        if (t == 1) {
            cin >> d >> c;
            process_req1(v, d, c);
        } else {
            cout << process_req2(v) << "\n";
        }
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
