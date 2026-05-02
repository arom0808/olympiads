#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 155;

int n, m;
int timer = 0;
int used[maxn], mt[maxn], lmt[maxn], rused[maxn];
vector<int> g[maxn], ig[maxn], rg[maxn];

bool dfs(int v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto u: g[v]) {
        if (mt[u] == -1) {
            mt[u] = v;
            return true;
        }
    }
    for (auto u: g[v]) {
        if (dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

void ldfs(int v);

void rdfs(int v) {
    if (rused[v] == timer) return;
    rused[v] = timer;
    if (mt[v] != -1) ldfs(mt[v]);
}

void ldfs(int v) {
    if (used[v] == timer) return;
    used[v] = timer;
    for (auto u: g[v]) if (u != lmt[v]) rdfs(u);
}

void solve_test() {
    cin >> n >> m;
    for (int i = 0, j; i < n; ++i) {
        g[i].clear();
        while (true) {
            cin >> j;
            if (!j) break;
            g[i].push_back(j - 1);
        }
        sort(g[i].begin(), g[i].end());
    }
    for (int i = 0; i < n; ++i) {
        ig[i].clear();
        for (int j = 0; j < m; ++j)
            if (!binary_search(g[i].begin(), g[i].end(), j))
                ig[i].push_back(j);
    }
    swap(g, ig);
    for (int i = 0; i < m; ++i) rg[i].clear();
    for (int i = 0; i < n; ++i) for (auto j: g[i]) rg[j].push_back(i);
    for (int i = 0; i < m; ++i) mt[i] = -1;
    for (int i = 0; i < n; ++i) lmt[i] = -1;
    ++timer;
    for (int i = 0; i < n; ++i) if (dfs(i)) ++timer;
    for (int i = 0; i < m; ++i) if (mt[i] != -1) lmt[mt[i]] = i;
    ++timer;
    for (int i = 0; i < n; ++i) if (lmt[i] == -1) ldfs(i);
    int lcnt = 0, rcnt = 0;
    for (int i = 0; i < n; ++i) if (used[i] == timer) ++lcnt;
    for (int i = 0; i < m; ++i) if (rused[i] != timer) ++rcnt;
    cout << lcnt + rcnt << "\n";
    cout << lcnt << " " << rcnt << "\n";
    for (int i = 0; i < n; ++i) if (used[i] == timer) cout << i + 1 << " ";
    cout << "\n";
    for (int i = 0; i < m; ++i) if (rused[i] != timer) cout << i + 1 << " ";
    cout << "\n";
}

void solve() {
    int k;
    cin >> k;
    while (k--) solve_test();
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
