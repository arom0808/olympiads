#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <algorithm>
#include <functional>

std::random_device dev;
std::uint32_t seed = dev();
std::mt19937 rng(seed);

void Test(const std::function<std::uint64_t(const std::vector<std::uint32_t> &)> &test_func) {
    std::uniform_int_distribution dist_n(2, 10000), dist_num(1, 100000);
    while (true) {
        std::vector<std::uint32_t> nums(dist_n(rng));
        for (auto &&num: nums) num = dist_num(rng);
        std::uint64_t max_result = 0;
        for (auto it_i = nums.begin(); it_i != std::prev(nums.end()); ++it_i) {
            for (auto it_j = std::next(it_i); it_j != nums.end(); ++it_j) {
                std::uint64_t min = *std::min_element(it_i, it_j);
                auto sum = static_cast<std::uint64_t>(std::accumulate(it_i, it_j, 0));
                if (max_result < min * sum) max_result = sum * min;
            }
        }
        auto my_res = test_func(nums);
        if (my_res != max_result) {
            std::cout << "Error!\n\n";
            std::cout << "Inputs:\n";
            std::cout << nums.size() << "\n";
            for (const auto &num: nums) std::cout << num << " ";
            std::cout << "\n\nRight out: " << max_result << "\nMy out: " << my_res;
            break;
        }
    }
}

std::uint64_t Solute(const std::vector<std::uint32_t> &nums) {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> lower_indexes(nums.size(), {nums.size(), nums.size()});
    std::deque<std::pair<std::uint32_t, std::uint32_t>> ids_and_nums_stack;
    for (std::uint32_t i = 0; i < nums.size(); ++i) {
        if (i > 0 && !ids_and_nums_stack.empty() && ids_and_nums_stack.front().second < nums[i]) {
            for (auto it = ids_and_nums_stack.rbegin(); it != ids_and_nums_stack.rend(); ++it) {
                if (it->second < nums[i]) {
                    lower_indexes[i].first = it->first;
                    break;
                }
            }
        }
        while (!ids_and_nums_stack.empty() && ids_and_nums_stack.back().second >= nums[i])
            ids_and_nums_stack.pop_back();
        ids_and_nums_stack.emplace_back(i, nums[i]);
    }
    ids_and_nums_stack.clear();
    for (std::int32_t i = nums.size() - 1; i >= 0; --i) {
        if (i < nums.size() - 1 && !ids_and_nums_stack.empty() && ids_and_nums_stack.front().second < nums[i]) {
            for (auto it = ids_and_nums_stack.rbegin(); it != ids_and_nums_stack.rend(); ++it) {
                if (it->second < nums[i]) {
                    lower_indexes[i].second = it->first;
                    break;
                }
            }
        }
        while (!ids_and_nums_stack.empty() && ids_and_nums_stack.back().second >= nums[i])
            ids_and_nums_stack.pop_back();
        ids_and_nums_stack.emplace_back(i, nums[i]);
    }
    std::vector<std::uint64_t> sums_prefixes(nums.size() + 1);
    sums_prefixes[0] = 0;
    for (std::uint32_t i = 0; i < nums.size(); ++i) sums_prefixes[i + 1] = sums_prefixes[i] + nums[i];
    std::uint64_t max_result = 0;
    for (std::uint32_t i = 0; i < nums.size(); ++i) {
        std::uint64_t sum_pre_arr = lower_indexes[i].first == nums.size() ? 0 : sums_prefixes[lower_indexes[i].first + 1];
        std::uint64_t sum_with_arr = sums_prefixes[lower_indexes[i].second];
        std::uint64_t new_result = sum_with_arr - sum_pre_arr;
        new_result *= nums[i];
        if (new_result > max_result) max_result = new_result;
    }
    return max_result;
}

int main() {
//    std::uint32_t n;
//    std::cin >> n;
//    std::vector<std::uint32_t> nums(n);
//    for (auto &&num: nums) std::cin >> num;
//    std::cout << Solute(nums);
    Test()
    return 0;
}
