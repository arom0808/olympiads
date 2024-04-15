#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t t;
    cin >> t;

    map<uint32_t, set<uint32_t>> id_by_size;
    vector<multiset<uint32_t>> ways;
    set<uint32_t> changes;

    for (uint32_t _ = 0; _ < t; ++_) {
        uint32_t n, m;
        cin >> n >> m;
        ways.resize(n);
        id_by_size.clear();
        for (auto &w: ways) w.clear();
        for (uint32_t i = 0, u, v; i < m; ++i) {
            cin >> v >> u;
            ways[v - 1].insert(u - 1);
            ways[u - 1].insert(v - 1);
        }
        for (uint32_t i = 0; i < n; ++i) {
            auto it = id_by_size.find(ways[i].size());
            if (it != id_by_size.end()) it->second.insert(i);
            else id_by_size.emplace(ways[i].size(), set<uint32_t>{i});
        }
        uint32_t res = 0, destroyed = 0;
        while (true) {
            if (id_by_size.empty() || id_by_size.rbegin()->first == 0) break;
            changes = id_by_size.rbegin()->second;
            for (auto td: changes) {
                if (!ways[td].empty()) {
                    id_by_size[ways[td].size()].erase(td);
                    if (id_by_size[ways[td].size()].empty()) id_by_size.erase(ways[td].size());
                }
                for (auto w: ways[td]) {
                    if (!ways[w].empty()) {
                        id_by_size[ways[w].size()].erase(w);
                        if (id_by_size[ways[w].size()].empty()) id_by_size.erase(ways[w].size());
                        ways[w].erase(td);
                    }
                    if (!ways[w].empty()) {
                        auto it = id_by_size.find(ways[w].size());
                        if (it != id_by_size.end()) it->second.insert(w);
                        else id_by_size.emplace(ways[w].size(), set<uint32_t>{w});
                    }
                }
                ways[td].clear();
                ++destroyed;
            }
            ++res;
        }
        cout << (res + (destroyed < n)) << "\n";
    }
    return 0;
}
