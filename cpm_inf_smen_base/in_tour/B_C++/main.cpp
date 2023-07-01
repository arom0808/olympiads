#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<std::uint16_t> nums(3);
    for (auto &&num: nums) std::cin >> num;
    std::sort(nums.begin(), nums.end());
    std::uint16_t last_digit;
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        if (*it % 2 != 0) continue;
        last_digit = *it;
        nums.erase(it);
        break;
    }
    std::uint16_t res = nums.back() * 100 + nums.front() * 10 + last_digit;
    std::cout << res;
    return 0;
}
