#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::int32_t n, m;
    std::cin >> n >> m;
    std::vector<std::set<std::int32_t>> oh(n);
    std::int32_t min_from_maxes = 2e9;
    std::set<std::int32_t> all;
    for (std::int32_t i = 0; i < n; ++i) {
        for (std::int32_t j = 0, c; j < m; ++j) {
            std::cin >> c;
            oh[i].insert(c);
            all.insert(c);
        }
        if (*oh[i].rbegin() < min_from_maxes) min_from_maxes = *oh[i].rbegin();
    }
    std::vector<std::list<std::int32_t>> h(n);
    for (std::int32_t i = 0; i < n; ++i) {
        h[i].resize(oh[i].size());
        std::copy(oh[i].begin(), oh[i].end(), h[i].begin());
    }
    std::int32_t best_res = 2e9, best_start_val = *all.begin();
    for (auto c: all) {
        if (c > min_from_maxes) break;
        std::int32_t max_of_min = 0;
        for (auto &s: h) {
            while (s.front() < c) s.erase(s.begin());
            if (s.front() > max_of_min) max_of_min = s.front();
        }
        if (max_of_min - c < best_res) {
            best_res = max_of_min - c;
            best_start_val = c;
        }
    }
    std::vector<std::int32_t> seq;
    seq.reserve(n);
    for (const auto &s: oh) seq.push_back(*s.lower_bound(best_start_val));
    std::sort(seq.begin(), seq.end());
    for (auto &c: seq) std::cout << c << " ";
    return 0;
}
