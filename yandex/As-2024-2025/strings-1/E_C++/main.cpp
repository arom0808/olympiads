#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 3e5, asz = 26;

char chs[maxn];
int nums[maxn];
vector<int> raw_g[maxn];
int g[maxn][asz];
int sz[maxn];
int n;
int max_ans_val = 0, max_ans_cnt = 0;

vector<int> chbc[asz];

void merge(int v, int u) {
    for (int c = 0; c < asz; ++c) {
        if (g[u][c] == -1) continue;
        if (g[v][c] == -1) {
            g[v][c] = g[u][c];
            sz[v] += sz[g[u][c]];
        } else {
            int psz = sz[g[v][c]];
            merge(g[v][c], g[u][c]);
            sz[v] += sz[g[v][c]] - psz;
        }
    }
}

void dfs(int v, int p = -1) {
    for (auto u: raw_g[v]) if (u != p) dfs(u, v);
    for (int i = 0; i < asz; ++i) chbc[i].clear();
    for (auto u: raw_g[v]) if (u != p) chbc[chs[u]].push_back(u);
    sz[v] = 1;
    for (int c = 0; c < asz; ++c) {
        if (chbc[c].empty()) continue;
        if (chbc[c].size() > 1) {
            for (auto &u: chbc[c]) if (sz[u] > sz[chbc[c][0]]) swap(u, chbc[c][0]);
            for (int i = 1; i < chbc[c].size(); ++i) merge(chbc[c][0], chbc[c][i]);
        }
        g[v][c] = chbc[c][0];
        sz[v] += sz[g[v][c]];
    }
    int cv = sz[v] + nums[v];
    if (cv > max_ans_val) max_ans_val = cv, max_ans_cnt = 1;
    else if (cv == max_ans_val) ++max_ans_cnt;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    for (int i = 0; i < n; ++i) cin >> chs[i], chs[i] -= 'a';
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        raw_g[u].push_back(v), raw_g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < asz; ++j) g[i][j] = -1;
    dfs(0);
    cout << max_ans_val << "\n" << max_ans_cnt << "\n";
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
