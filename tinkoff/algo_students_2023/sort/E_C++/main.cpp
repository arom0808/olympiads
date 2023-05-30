#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> results(n - 1);
    std::set<std::uint32_t> ones_positions, zeros_positions;
    for (std::uint32_t i = 0; i < n; ++i) zeros_positions.insert(i);
    std::vector<bool> arr(n, false);
    std::uint32_t last_zero_pos = n - 1;
    for (auto &&res: results) {
        std::uint32_t one_pos;
        std::cin >> one_pos;
        --one_pos;
        zeros_positions.erase(one_pos);
        ones_positions.insert(one_pos);
        arr[one_pos] = true;
        if (one_pos == last_zero_pos) {
            last_zero_pos = *zeros_positions.rbegin();
            ones_positions.erase(ones_positions.lower_bound(last_zero_pos), ones_positions.end());
        } else {
        }
        res = ones_positions.size();
    }
    std::cout << 1 << " ";
    for (const auto &res: results) std::cout << res + 1 << " ";
    std::cout << 1;
    return 0;
}
