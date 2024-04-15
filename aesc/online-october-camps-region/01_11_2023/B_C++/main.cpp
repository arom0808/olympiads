#include <iostream>
#include <map>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::map<std::uint32_t, std::uint32_t> counts;
    for (std::uint32_t i = 0, num; i < n; ++i) {
        std::cin >> num;
        auto it = counts.find(num);
        if (it != counts.end()) ++it->second;
        else counts.emplace(num, 1);
    }
    std::uint32_t pairs_cnt = 0;
    for (auto it1 = counts.begin(), it2 = std::next(it1); it2 != counts.end(); ++it1, ++it2) {
        if (it1->first + 1 == it2->first) {
            pairs_cnt += std::min(it1->second, it2->second);
            it2->second -= std::min(it1->second, it2->second);
        }
    }
    std::cout << n - pairs_cnt;
    return 0;
}