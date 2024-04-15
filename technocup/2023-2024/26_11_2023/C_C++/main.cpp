#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

int main() {
    uint32_t n, m;
    cin >> n >> m;
    vector<list<uint32_t>> rg(n);
    for (uint32_t i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        rg[a - 1].push_back(b - 1);
        rg[b - 1].push_back(a - 1);
    }
    uint32_t s;
    cin >> s;
    vector<bool> used(n, false);
    deque<pair<uint32_t, bool>> que;
    que.emplace_back(s - 1, false);
    uint32_t res = 0;
    while (!que.empty()) {
        auto [v, switched] = que.front();
        que.pop_front();
        if (used[v]) continue;
        used[v] = true;
        if (!switched) ++res;
        for (auto to: rg[v]) if (!used[to]) que.emplace_back(to, !switched);
    }
    cout << res;
    return 0;
}
