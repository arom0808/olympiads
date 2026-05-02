#include <iostream>

using namespace std;

constexpr int maxn = 205;

int n, m;
int compatibility[maxn][maxn];
int min_comp = 0;
int timer = 0;
int used[maxn];
int mt[maxn];

bool dfs(int v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (int u = 0; u < m; ++u) {
        if (compatibility[v][u] >= min_comp && mt[u] == -1) {
            mt[u] = v;
            return true;
        }
    }
    for (int u = 0; u < m; ++u) {
        if (compatibility[v][u] >= min_comp && dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> compatibility[i][j];
    int max_cnt = 0;
    for (int i = 0; i < m; ++i) mt[i] = -1;
    ++timer;
    for (int i = 0; i < n; ++i) if (dfs(i)) ++max_cnt, ++timer;
    int l = 0, r = 1e9 + 1;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        min_comp = mid;
        int cur_cnt = 0;
        for (int i = 0; i < m; ++i) mt[i] = -1;
        ++timer;
        for (int i = 0; i < n; ++i) if (dfs(i)) ++cur_cnt, ++timer;
        if (cur_cnt == max_cnt) l = mid;
        else r = mid;
    }
    cout << l;
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
