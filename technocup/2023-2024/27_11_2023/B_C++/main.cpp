#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <list>

using namespace std;

struct QueAct {
    uint32_t par, v;
    bool inv;
    list<uint32_t>::iterator par_it;
};

int main() {
    uint32_t n, m;
    cin >> n >> m;
    vector<list<pair<uint32_t, bool>>> g(n);
    list<pair<uint32_t, uint32_t>> edges;
    for (uint32_t i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        edges.emplace_back(a - 1, b - 1);
        g[a - 1].emplace_back(b - 1, false);
        g[b - 1].emplace_back(a - 1, true);
    }
    vector<bool> used(n, false);
    deque<QueAct> que;
    list<uint32_t> students, hist;
    students.emplace_back(0);
    for (auto [to, inv]: g[0]) que.emplace_back(0, to, inv, students.begin());
    used[0] = true;
    while (!que.empty()) {
        auto [par, v, inv, par_it] = que.front();
        que.pop_front();
        if (used[v]) continue;
        used[v] = true;
        hist.push_back(v);
        auto t_it = students.insert(inv ? par_it : next(par_it), v);
        for (auto [to, to_inv]: g[v]) if (!used[to]) que.emplace_back(v, to, to_inv, t_it);
    }
    if (find(used.begin(), used.end(), false) != used.end()) {
        cout << 0;
        return 0;
    }
    for (auto s: students) cout << s + 1 << " ";
    cout << "\n";
    for (auto it = hist.rbegin(); it != hist.rend(); ++it) cout << ((*it) + 1) << " ";
    return 0;
}
