#include <iostream>
#include <vector>
#include <algorithm>

bool is_prime_div_of_num(std::uint32_t num, std::uint32_t pr_div, const std::vector<std::uint32_t> &mpd) {
    for (; num != 1; num /= mpd[num]) if (mpd[num] == pr_div) return true;
    return false;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    std::vector<std::uint32_t> mpd(*std::max_element(nums.begin(), nums.end()) + 1, 0), prime;
    for (std::uint32_t i = 2; i < mpd.size(); ++i) {
        if (mpd[i] == 0) {
            mpd[i] = i;
            prime.push_back(i);
        }
        for (const auto &pr_num: prime) {
            if (pr_num > mpd[i] || i * pr_num >= mpd.size()) break;
            mpd[i * pr_num] = pr_num;
        }
    }
    std::uint32_t max_len = 0;
    for (const auto &pr_num: prime) {
        for (std::uint32_t i = 0, cur_len = 0; i < n; ++i) {
            if (is_prime_div_of_num(nums[i], pr_num, mpd)) ++cur_len;
            else cur_len = 0;
            if (cur_len > max_len) max_len = cur_len;
        }
    }
    std::cout << max_len;
    return 0;
}
