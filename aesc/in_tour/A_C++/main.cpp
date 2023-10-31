#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

int main() {
    std::int64_t n;
    std::cin >> n;
    std::map<std::int64_t, std::int64_t> raw_nums;
    std::int64_t sum = 0;
    for (std::int64_t i, num; i < n; ++i) {
        std::cin >> num;
        auto it = raw_nums.find(num);
        if (it != raw_nums.end()) ++it->second;
        else raw_nums.emplace(num, 1);
    }
    std::vector<std::int64_t> counts;
    for (const auto &[num, cnt]: raw_nums) counts.push_back(cnt);
    std::sort(counts.rbegin(), counts.rend());
    std::int64_t mcnt = counts.front();
    if (counts.size() == 1) {
        std::cout << 1;
        return 0;
    }
    for (const auto &cnt: counts) sum += cnt;
    if (mcnt > sum - mcnt + 1) {
        std::cout << ((sum - mcnt) * 2 + 1);
    } else {
        std::cout << n;
    }
    return 0;
}