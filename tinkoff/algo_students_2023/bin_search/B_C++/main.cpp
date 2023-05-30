#include <iostream>
#include <vector>

std::int32_t NearestNum(const std::vector<std::int32_t> &nums, std::int32_t num) {
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
    if (l == 0) return nums[l];
    else if (num - nums[l - 1] > nums[l] - num) return nums[l];
    else return nums[l - 1];
}

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;
    std::vector<std::int32_t> nums(n), results(k);
    for (auto &&num: nums) std::cin >> num;
    std::int32_t temp_f_num;
    for (auto &&result: results) {
        std::cin >> temp_f_num;
        result = NearestNum(nums, temp_f_num);
    }
    for (const auto &result: results) std::cout << result << std::endl;
    return 0;
}
