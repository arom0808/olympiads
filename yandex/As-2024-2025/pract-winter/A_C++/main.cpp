#include <iostream>
#include <vector>
#include <map>

using namespace std;

constexpr int maxn = 2e5;

vector<int> g1[maxn], g2[maxn];
int c1[maxn], c2[maxn];
map<int, int> cnt_in_comp[maxn];
int n;

void dfs1(int v, int c) {
    c1[v] = c;
    for (auto u: g1[v]) if (c1[u] == -1) dfs1(u, c);
}

void dfs2(int v, int c) {
    c2[v] = c;
    ++cnt_in_comp[c][c1[v]];
    for (auto u: g2[v]) if (c2[u] == -1) dfs2(u, c);
}

void solve() {
    cin >> n;
    int k, l;
    cin >> k >> l;
    for (int i = 0, u, v; i < k; ++i) {
        cin >> u >> v, --u, --v;
        g1[u].push_back(v), g1[v].push_back(u);
    }
    for (int i = 0, u, v; i < l; ++i) {
        cin >> u >> v, --u, --v;
        g2[u].push_back(v), g2[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) c1[i] = c2[i] = -1;
    int ccolor = 0;
    for (int v = 0; v < n; ++v) if (c1[v] == -1) dfs1(v, ccolor++);
    ccolor = 0;
    for (int v = 0; v < n; ++v) if (c2[v] == -1) dfs2(v, ccolor++);
    for (int v = 0; v < n; ++v) cout << cnt_in_comp[c2[v]][c1[v]] << " ";
    cout << "\n";
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
