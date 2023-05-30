#include <iostream>
#include <vector>

bool IsNumExists(const std::vector<std::int32_t> &nums, std::int32_t num) {
    std::uint32_t l = 0, r = nums.size() - 1;
    while (l != r) {
        std::uint32_t mid = (l + r) / 2;
        if (nums[mid] < num) l = mid + 1;
        else if (nums[mid] > num) r = mid;
        else {
            l = mid;
            r = mid;
        }
    }
    return nums[l] == num;
}

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;
    std::vector<std::int32_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    std::vector<bool> results(k, false);
    std::int32_t temp_f_num;
    for (std::uint32_t i = 0; i < k; ++i) {
        std::cin >> temp_f_num;
        if (IsNumExists(nums, temp_f_num)) results[i] = true;
    }
    for (const auto &result: results) std::cout << (result ? "YES" : "NO") << std::endl;
    return 0;
}
