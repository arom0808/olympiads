#include <iostream>
#include <vector>

using namespace std;
using ll = int64_t;
using ull = uint64_t;
using ld = long double;

const int maxn = 100;
vector<int> g[maxn];
bool used[maxn];

int dfs(int v) {
    if (used[v]) return 0;
    used[v] = true;
    int res = 1;
    for (auto u: g[v]) res += dfs(u);
    return res;
}

void solve() {
    for (int i = 0; i < maxn; ++i) used[i] = false, g[i].clear();
    int n, m;
    cin >> n >> m;
    for (int i = 0, v, u; i < m; ++i) {
        cin >> v >> u, --v, --u;
        g[v].push_back(u), g[u].push_back(v);
    }
    vector<int> cnts;
    for (int v = 0; v < n; ++v) if (!used[v]) cnts.push_back(dfs(v));
    int a1 = 0, a2 = 0, a3 = 0;
    for (auto c: cnts) {
        int n1 = 0, n2 = 0, n3 = 0;
        n3 = c / 3;
        c %= 3;
        if (c == 2) ++n2;
        else if (c == 1) ++n1;
        if (n1 && n3) --n1, --n3, n2 += 2;
        a1 += n1, a2 += n2, a3 += n3;
    }
    cout << a1 << "\n" << a2 << "\n" << a3 << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
