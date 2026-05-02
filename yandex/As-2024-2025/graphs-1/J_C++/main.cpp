#include <iostream>
#include <deque>

using namespace std;

constexpr int maxn = 1e5, inf = 1e9;

int dist[maxn];

void solve() {
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) dist[i] = inf;
    dist[1] = 1;
    deque<int> d;
    d.push_back(1);
    while (!d.empty()) {
        int v = d.front();
        d.pop_front();
        for (int i = 0, u = (v + 1) % k, w = 1; i < 2; ++i, u = (v * 10) % k, w = 0) {
            if (dist[u] <= dist[v] + w) continue;
            dist[u] = dist[v] + w;
            if (!w) d.push_front(u);
            else d.push_back(u);
        }
    }
    cout << dist[0] << "\n";
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
