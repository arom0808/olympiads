#include <iostream>
#include <vector>

struct Solution {
    bool is_solved = false;
    std::uint32_t a1 = 0, d1 = 0, a2 = 0, d2 = 0;
};

Solution Solute(const std::vector<std::uint32_t> &nums, std::uint32_t first_seq_d) {
    Solution result;
    std::uint32_t n = nums.size() / 2;
    result.a1 = nums.front();
    result.d1 = first_seq_d;
    std::uint32_t next_first_el = result.a1 + result.d1, first_count = 1;
    std::uint32_t next_second_el = 0, second_count = 0;
    for (std::uint32_t i = 1; i < nums.size(); ++i) {
        if (nums[i] == next_first_el) {
            next_first_el += result.d1;
            ++first_count;
        } else {
            if (next_second_el == 0) {
                if (result.a2 == 0) {
                    result.a2 = nums[i];
                } else {
                    result.d2 = nums[i] - result.a2;
                    next_second_el = nums[i] + result.d2;
                }
            } else {
                if (nums[i] == next_second_el) next_second_el += result.d2;
                else return result;
            }
            ++second_count;
        }
        if (first_count > n || second_count > n) return result;
    }
    result.is_solved = true;
    return result;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> nums(2 * n);
    for (auto &&num: nums) std::cin >> num;
    Solution temp_sol;
    for (std::uint32_t first_seq_d = 1; first_seq_d < nums.back(); ++first_seq_d) {
        temp_sol = Solute(nums, first_seq_d);
        if (temp_sol.is_solved) break;
    }
    if (temp_sol.a1 == nums.front()) {
        for (std::uint32_t i = 0, num = temp_sol.a1; i < n; ++i, num += temp_sol.d1)
            std::cout << num << " ";
    } else {
        for (std::uint32_t i = 0, num = temp_sol.a2; i < n; ++i, num += temp_sol.d2)
            std::cout << num << " ";
    }
    return 0;
}
