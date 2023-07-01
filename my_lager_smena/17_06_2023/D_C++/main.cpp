#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

int main() {
    std::set<std::uint32_t> two_pows;
    two_pows.emplace(1);
    for (std::uint32_t i = 1; i < 25; ++i) two_pows.emplace((*two_pows.rbegin()) * 2);
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> iqs(n);
    for (auto &num: iqs) std::cin >> num;
    std::unordered_map<std::uint32_t, std::uint32_t> counts, counts_with_pluses;
    std::uint64_t res;
    for (std::uint32_t start = 0; start < n; ++start) {
        counts.clear();
        counts_with_pluses.clear();
        std::uint32_t min = iqs[start], max = iqs[start];
        counts.emplace(iqs[start], 1);
        counts_with_pluses.emplace(iqs[start], 1);
        bool is_ok = false;
        for (std::uint32_t end = start; end < n; ++end) {
            if (is_ok && two_pows.find(counts_with_pluses[max]) != two_pows.end()) ++res;

//            bool is_ok = true;
//            for (std::uint32_t i = min; i < max; ++i) {
//                if ((counts[i] + pre_plus) % 2 != 0) {
//                    is_ok = false;
//                    break;
//                }
//                pre_plus = (counts[i] + pre_plus) / 2;
//            }
//            if (is_ok) if (two_pows.find(pre_plus + counts[max]) != two_pows.end()) ++res;
            if (end < n - 1) {
                auto t_it = counts.find(iqs[end + 1]);
                if (t_it == counts.end()) counts.emplace(iqs[end + 1], 1);
                else ++t_it->second;
                if (iqs[end + 1] < min) min = iqs[end + 1];
                if (iqs[end + 1] > max) max = iqs[end + 1];
            }
        }
    }
    std::cout << res;
    return 0;
}
