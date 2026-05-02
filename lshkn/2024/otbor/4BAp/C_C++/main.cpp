#include <iostream>
#include <vector>
#include <cstdint>
#include <deque>

using namespace std;

const int32_t maxn = 100001;
vector<vector<int32_t>> g;
int32_t colors[maxn], values[maxn];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m, k;
    cin >> n >> m >> k;
    g.resize(n);
    for (int32_t i = 0, u, v; i < m; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int32_t i = 0; i < maxn; ++i) values[i] = -1;
    for (int32_t i = 0; i < n; ++i) cin >> colors[i];
    vector<int32_t> b(k);
    for (auto &val: b) cin >> val;
    vector<bool> visited(n);
    deque<int32_t> deq;
    deq.push_back(0);
    values[0] = b[0] == colors[0] ? 1 : 0;
    while (!deq.empty()) {
        auto v = deq.front();
        deq.pop_front();
        if (visited[v]) continue;
        visited[v] = true;
        if (values[v] >= k) continue;
        for (auto u: g[v]) {
            auto new_val = values[v] + (colors[u] == b[values[v]] ? 1 : 0);
            if (!visited[u] && (values[u] == -1 || new_val < values[u])) {
                values[u] = new_val;
                deq.push_back(u);
            }
        }
    }
//    multimap<int32_t, int32_t> queue;
//    queue.emplace(b[0] == colors[0] ? 1 : 0, 0);
//    while (!queue.empty()) {
//        auto [val, v] = *queue.begin();
//        queue.erase(queue.begin());
//        if (values[v] != val || val >= k) continue;
//        for (auto u: g[v]) {
//            auto new_val = val + (colors[u] == b[val] ? 1 : 0);
//            if (values[u] == -1 || new_val < values[u]) {
//                values[u] = new_val;
//                queue.emplace(values[u], u);
//            }
//        }
//    }
    if (values[n - 1] == -1 || values[n - 1] == k) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}
