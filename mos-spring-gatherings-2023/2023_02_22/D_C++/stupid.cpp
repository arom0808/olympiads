#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 1e6;
vector<int> low_borders[maxn], high_borders[maxn];
vector<int> g[maxn];
int n, k;
int ans;

void dfs1(int v, int dist, vector<int> low_cur_box, vector<int> high_cur_box, int p = -1) {
    for (int i = 0; i < k; ++i) low_cur_box[i] = std::max(low_cur_box[i], low_borders[v][i]);
    for (int i = 0; i < k; ++i) high_cur_box[i] = std::min(high_cur_box[i], high_borders[v][i]);
    for (int i = 0; i < k; ++i) {
        if (low_cur_box[i] > high_cur_box[i]) {
            ans = std::min(ans, dist);
            return;
        }
    }
    for (auto u: g[v]) if (u != p) dfs1(u, dist + 1, low_cur_box, high_cur_box, v);
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) low_borders[i].resize(k), high_borders[i].resize(k);
    for (int i = 0; i < n; ++i) {
        for (auto &c: low_borders[i]) cin >> c;
        for (auto &c: high_borders[i]) cin >> c;
        for (int j = 0; j < k; ++j)
            if (low_borders[i][j] > high_borders[i][j])
                swap(low_borders[i][j], high_borders[i][j]);
    }
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    vector<int> lcb(k, -1e9 - 1), hcb(k, 1e9 + 1);
    ans = n;
    for (int v = 0; v < n; ++v) dfs1(v, 0, lcb, hcb);
    cout << ((ans == n) ? (-1) : ans) << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
