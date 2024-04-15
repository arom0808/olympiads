#include <iostream>
#include <vector>
#include <set>
#include <map>

int main() {
    std::uint64_t n, m;
    std::cin >> n >> m;
    std::vector<std::uint64_t> a(n), b(n);
    for (auto &c: a) std::cin >> c;
    for (auto &c: b) std::cin >> c;
    std::map<std::uint64_t, std::set<std::uint64_t>> ibyc;
    ibyc.emplace(0, std::set<std::uint64_t>{});
    for (std::uint64_t i = 0; i < n; ++i) ibyc.begin()->second.insert(i);
    std::vector<bool> lec_used(n, false);
    for (std::uint64_t w = 0; w < m; ++w) {
        std::fill(lec_used.begin(), lec_used.end(), false);
        for (std::uint64_t li = 0; li < n; ++li) {
            auto nv = ibyc.begin()->first;
            auto ni = *ibyc.begin()->second.begin();
            ibyc.begin()->second.erase(ni);
            if (ibyc.begin()->second.empty()) ibyc.erase(ibyc.begin());
            if (a[ni] > b[ni] && !lec_used[ni]) {
                lec_used[ni] = true;
                nv += a[ni];
            } else nv += b[ni];
            auto it = ibyc.find(nv);
            if (it != ibyc.end()) it->second.insert(ni);
            else ibyc.emplace(nv, std::set<std::uint64_t>{ni});
        }
    }
    std::cout << ibyc.begin()->first;
    return 0;
}
