#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e6 + 10, inf = 1e9;

int n;
vector<int> g[maxn];
pair<int, int> tmxs[maxn];
int va[maxn];

void dfs1(int v, int p = -1) {
    tmxs[v].first = 0;
    va[v] = 1;
    for (auto u: g[v]) {
        if (u == p) continue;
        dfs1(u, v);
        if (va[u] >= tmxs[v].first) tmxs[v].second = tmxs[v].first, tmxs[v].first = va[u];
        else if (va[u] >= tmxs[v].second) tmxs[v].second = va[u];
        va[v] = std::max(va[v], tmxs[v].first + 1);
    }
}

void dfs2(int v, int p = -1) {
    for (auto u: g[v]) {
        if (u == p) continue;
        int cv = ((va[u] == tmxs[v].first) ? tmxs[v].second : tmxs[v].first) + 1;
        va[u] = std::max(va[u], cv + 1);
        if (cv >= tmxs[u].first) tmxs[u].second = tmxs[u].first, tmxs[u].first = cv;
        else if (cv >= tmxs[u].second) tmxs[u].second = cv;
        dfs2(u, v);
    }
}


void solve() {
    int v1 = 0, v2 = 0;
    for (int _ = 0; _ < 2; ++_) {
        cin >> n;
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n; ++i) va[i] = 0;
        for (int i = 1, u, v; i < n; ++i) {
            cin >> u >> v, --u, --v;
            g[u].push_back(v), g[v].push_back(u);
        }
        for (int i = 0; i < n; ++i) tmxs[i] = {-inf, -inf};
        dfs1(0);
        dfs2(0);
        if (_ == 0) v1 = *min_element(va, va + n);
        else v2 = *max_element(va, va + n);
    }
    if (v1 > v2) cout << "GGEZ\n";
    else cout << "FF\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    cin >> t;
#endif
    while (t--) solve();
    return 0;
}
