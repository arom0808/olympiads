#include <iostream>
#include<map>
#include <vector>

using Ways = std::multimap<std::uint32_t, std::uint32_t>;
using Towns = std::vector<bool>;

long double getMid(const Ways &ways, Towns &towns, std::uint32_t fromTownId) {
    std::uint32_t cnt = 0;
    long double mid = 0;
    for (const auto &way: ways) {
        if (way.first == fromTownId && !towns[way.second]) {
            towns[way.second] = true;
            ++cnt;
            mid += 1 + getMid(ways, towns, way.second);
            towns[way.second] = false;
        }
    }
    if (cnt == 0) return 0;
    return mid / static_cast<long double>(cnt);
}


int main() {
    std::uint32_t n;
    std::cin >> n;
    Ways ways;
    Towns towns(n, false);
    towns[0] = true;
    std::pair<std::uint32_t, std::uint32_t> temp_pair;
    for (std::uint32_t i = 1; i < n; ++i) {
        std::cin >> temp_pair.first >> temp_pair.second;
        ways.emplace(temp_pair.first - 1, temp_pair.second - 1);
        ways.emplace(temp_pair.second - 1, temp_pair.first - 1);
    }
    std::cout.precision(15);
    std::cout << getMid(ways, towns, 0);
    return 0;
}
