#include <iostream>
#include <vector>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::int32_t> nums(n);
    bool is_minus_exists = false;
    for (auto &&e: nums) {
        std::cin >> e;
        if (e < 0) is_minus_exists = true;
    }
    std::vector<std::int32_t> sums(n);
    std::uint32_t ibest = 0, jbest = 0, imin = 0;
    sums[0] = nums[0];
    for (std::uint32_t j = 1; j < n; ++j) {
        sums[j] = sums[j - 1] + nums[j];
        if (sums[j] <= sums[imin]) imin = j;
        if (sums[j] - sums[imin] > sums[jbest] - sums[ibest]) {
            ibest = imin;
            jbest = j;
        }
    }
    std::cout << ibest + (is_minus_exists ? 2 : 1) << "\n" << jbest + 1;
    return 0;
}
