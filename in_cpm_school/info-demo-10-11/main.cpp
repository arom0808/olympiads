#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<std::uint32_t> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::uint32_t min_sum = 123123;
    do {
        auto sum = nums[0] + nums[1] + nums[3] + nums[4] + nums[1] + nums[2] + nums[4] + nums[5] + nums[3] + nums[4] +
                   nums[6] + nums[7] + nums[4] + nums[5] + nums[7] + nums[8];
        if (sum < min_sum) min_sum = sum;
    } while (std::next_permutation(nums.begin(), nums.end()));
    std::cout << min_sum;
    return 0;
}
