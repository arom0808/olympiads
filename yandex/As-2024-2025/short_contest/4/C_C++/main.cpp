#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e5;
int size[maxn];
vector<pair<int, int> > g[maxn];

void solve() {
    int n;
    cin >> n;
    for (int i = 0, u, v, w; i < n; ++i) {
        cin >> u >> v >> w, --u, --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
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
