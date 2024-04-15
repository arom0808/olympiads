#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {
    int32_t n, m;
    cin >> n >> m;
    vector<pair<int32_t, int32_t>> gons(m);
    vector<set<int32_t>> mounts(n);
    for (int32_t i = 0; i < m; ++i) {
        auto &[b, p] = gons[i];
        cin >> b >> p;
        mounts[b].insert(i);
    }
    vector<bool> used(n, false);
    vector<int32_t> min_time(n, -1);
    multimap<int32_t, int32_t> que;
    que.emplace(0, gons[0].first);
    while (!que.empty()) {
        auto [t, m_id] = *que.begin();
        que.erase(que.begin());
        if (used[m_id]) continue;
        used[m_id] = true;
        if (m_id == gons[1].first) {
            cout << t;
            break;
        }
        for (auto gon_i: mounts[m_id]) {
            for (int32_t i = 1; m_id >= gons[gon_i].second * i; ++i) {
                auto pos = m_id - gons[gon_i].second * i;
                if (!used[pos] && (min_time[pos] == -1 || min_time[pos] > t + i)) {
                    que.emplace(t + i, pos);
                    min_time[pos] = t + i;
                }
            }
            for (int32_t i = 1; m_id + gons[gon_i].second * i < n; ++i) {
                auto pos = m_id + gons[gon_i].second * i;
                if (!used[pos] && (min_time[pos] == -1 || min_time[pos] > t + i)) {
                    que.emplace(t + i, pos);
                    min_time[pos] = t + i;
                }
            }
        }
        mounts[m_id].clear();
    }
    if (!used[gons[1].first]) cout << -1;
    return 0;
}
