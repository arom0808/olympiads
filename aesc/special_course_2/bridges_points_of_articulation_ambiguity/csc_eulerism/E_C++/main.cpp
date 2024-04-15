#include <iostream>
#include <vector>
#include <map>
#include <set>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::pair<std::string, std::uint32_t>> points;
    std::vector<std::set<std::uint32_t>> g, rg;
    points.reserve(n);
    g.reserve(n);
    rg.reserve(n);
    std::map<std::string, std::uint32_t> point_ids;
    std::map<std::string, std::set<std::uint32_t>> start_on_ids, ends_on_ids;
    std::string tmp;
    for (std::uint32_t i = 0; i < n; ++i) {
        std::cin >> tmp;
        auto it1 = point_ids.find(tmp);
        if (it1 != point_ids.end()) ++points[it1->second].second;
        else {
            points.emplace_back(tmp, 1);
            g.emplace_back();
            rg.emplace_back();
            std::uint32_t v = points.size() - 1;
            point_ids.emplace(tmp, v);
            auto ns = tmp.substr(0, 2), ne = tmp.substr(1, 2);
            auto it2 = start_on_ids.find(ns);
            if (it2 != start_on_ids.end()) it2->second.emplace(v);
            else start_on_ids.emplace(ns, std::set<std::uint32_t>{v});
            auto it3 = ends_on_ids.find(ne);
            if (it3 != ends_on_ids.end()) it3->second.emplace(v);
            else ends_on_ids.emplace(ne, std::set<std::uint32_t>{v});
            auto addit1 = start_on_ids.find(ne);
            if (addit1 != start_on_ids.end()) {
                for (auto u: addit1->second) {
                    g[v].emplace(u);
                    rg[u].emplace(v);
                }
            }
            auto addit2 = ends_on_ids.find(ns);
            if (addit2 != ends_on_ids.end()) {
                for (auto p: addit2->second) {
                    g[p].emplace(v);
                    rg[v].emplace(p);
                }
            }
        }
    }
    return 0;
}
