#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

constexpr int maxn = 5e5;
int n, m;
vector<int> raw_g[maxn], rev_raw_g[maxn], comp_g[maxn];
int comp_by_id[maxn];
vector<int> raw_topsort;
bool used[maxn], achieve_finish[maxn];
int comp_tin[maxn], comp_fup[maxn], comp_size[maxn];
int comp_timer = 0;
int comps_cnt = 0;
vector<int> ids_in_comp[maxn];
vector<int> comp_sochl_points;

void dfs1(int v) {
    used[v] = true;
    for (auto u: raw_g[v]) if (!used[u]) dfs1(u);
    raw_topsort.push_back(v);
}

void dfs2(int v, int c) {
    used[v] = true;
    comp_by_id[v] = c;
    ++comp_size[c];
    ids_in_comp[c].push_back(v);
    for (auto u: rev_raw_g[v]) if (!used[u]) dfs2(u, c);
}

void dfs3(int v, int p = -1) {
    used[v] = true;
    comp_fup[v] = comp_tin[v] = comp_timer++;
    for (auto u: comp_g[v]) {
        if (u == p) continue;
        if (used[u]) comp_fup[v] = std::min(comp_fup[v], comp_tin[u]);
        else {
            dfs3(u, v);
            comp_fup[v] = std::min(comp_fup[v], comp_fup[u]);
        }
    }
    if (achieve_finish[v] && comp_fup[v] >= comp_tin[v]) comp_sochl_points.push_back(v);
}

bool dfs4(int v) {
    if (used[v]) return achieve_finish[v];
    used[v] = true;
    if (v == comp_by_id[n - 1]) achieve_finish[v] = true;
    for (auto u: comp_g[v]) achieve_finish[v] |= dfs4(u);
    return achieve_finish[v];
}

void solve() {
    cin >> n >> m;
    comp_sochl_points.clear();
    for (int i = 0; i < n; ++i)
        raw_g[i].clear(), rev_raw_g[i].clear(), comp_g[i].clear(), comp_size[i] = 0,
                ids_in_comp[i].clear(), achieve_finish[i] = false;
    raw_topsort.clear();
    comp_timer = 0;
    comps_cnt = 0;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b, --a, --b;
        raw_g[a].push_back(b), rev_raw_g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) used[i] = false;
    dfs1(0);
    if (!used[n - 1]) {
        cout << "0\n\n";
        return;
    }
    for (int i = 0; i < n; ++i) used[i] = false;
    for (int i = 0; i < n; ++i) comp_by_id[i] = -1;
    reverse(raw_topsort.begin(), raw_topsort.end());
    for (auto v: raw_topsort) if (!used[v]) dfs2(v, comps_cnt++);
    for (int v = 0; v < n; ++v) {
        if (comp_by_id[v] == -1) continue;
        for (auto u: raw_g[v]) {
            if (comp_by_id[u] == -1 || comp_by_id[v] == comp_by_id[u]) continue;
            comp_g[comp_by_id[v]].push_back(comp_by_id[u]);
            // comp_g[comp_by_id[u]].push_back(comp_by_id[v]);
        }
    }
    for (int i = 0; i < n; ++i) used[i] = false;
    dfs4(0);
    for (int v = 0; v < comps_cnt; ++v) for (auto u: comp_g[v]) comp_g[u].push_back(v);
    for (int i = 0; i < n; ++i) used[i] = false;
    dfs3(0);
    comp_sochl_points.push_back(comp_by_id[0]);
    reverse(comp_sochl_points.begin(), comp_sochl_points.end());
    comp_sochl_points.push_back(comp_by_id[n - 1]);
    comp_sochl_points.erase(unique(comp_sochl_points.begin(), comp_sochl_points.end()), comp_sochl_points.end());
    erase_if(comp_sochl_points, [](int cv) {
        return comp_size[cv] != 1 ||
               find(raw_g[ids_in_comp[cv][0]].begin(), raw_g[ids_in_comp[cv][0]].end(),
                    ids_in_comp[cv][0]) != raw_g[ids_in_comp[cv][0]].end();
    });
    cout << comp_sochl_points.size() << "\n";
    for (auto cv: comp_sochl_points) cout << ids_in_comp[cv][0] + 1 << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
