#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int maxn = 2e5;

struct Edge {
    int u;
    int color;
};

int n, m;
int used[maxn];
vector<int> g[maxn];
Edge edges[maxn];

int start_e;
vector<int> way;

bool dfs(int pe) {
    used[pe] = 1;
    way.push_back(pe);
    for (auto e: g[edges[pe].u]) {
        if (edges[pe].color == edges[e].color) continue;
        if (!used[e]) {
            if (dfs(e)) return true;
        } else if (used[e] == 1) {
            start_e = e;
            return true;
        }
    }
    used[pe] = 2;
    way.pop_back();
    return false;
}

void solve() {
    way.clear();
    cin >> n >> m;
    for (int i = 0; i < n; ++i) g[i].clear();
    for (int i = 0; i < m; ++i) used[i] = edges[i].u = edges[i].color = 0;
    for (int i = 0, u, v, c; i < m; ++i) {
        cin >> u >> v >> c, --u, --v;
        edges[i].u = v, edges[i].color = c;
        g[u].push_back(i);
    }
    for (int e = 0; e < m; ++e) if (!used[e] && dfs(e)) break;
    int start_pos = find(way.begin(), way.end(), start_e) - way.begin();
    if (way.size() - start_pos == 0) {
        cout << "-1\n";
        return;
    }
    cout << way.size() - start_pos << "\n";
    for (int i = start_pos; i < way.size(); ++i) cout << way[i] + 1 << " ";
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
