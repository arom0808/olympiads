#include <iostream>
#include <vector>
#include <deque>

using namespace std;

constexpr int maxn = 1e6, inf = 1e9;

vector<pair<int, int> > g[maxn];
int dist[maxn];
int n, m;

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        g[l - 1].emplace_back(r - 1, 0);
        g[r - 1].emplace_back(l - 1, 0);
    }
    for (int i = 0; i + 1 < n; ++i) g[i].emplace_back(i + 1, 1), g[i + 1].emplace_back(i, 1);
    for (int i = 0; i < n; ++i) dist[i] = inf;
    dist[0] = 0;
    deque<int> d;
    while (!d.empty()) {
        auto v = d.front();
        d.pop_front();
        for (auto [u,w]: g[v]) {
            if (dist[u] <= dist[v] + w) continue;
            if (!w) d.push_front(u);
            else d.push_back(u);
        }
    }
    for (int i = 0; i < n; ++i) {
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
