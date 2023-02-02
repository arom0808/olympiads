#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

inline bool IsContains(const std::set<std::uint32_t> &numbers, const std::uint32_t &num) {
    return numbers.find(num) != numbers.end();
}

std::uint32_t MaxGoals(const std::vector<std::uint32_t> &numbers, const std::set<std::uint32_t> &not_equal_numbers,
                       std::set<std::uint32_t> &deleted_numbers) {
    std::uint32_t result = 0;
    if (deleted_numbers.size() == not_equal_numbers.size()) return 0;
    for (auto it_now_deleting_num = not_equal_numbers.rbegin();
         it_now_deleting_num != not_equal_numbers.rend(); ++it_now_deleting_num) {
        if (IsContains(deleted_numbers, *it_now_deleting_num)) continue;
        auto begin_num_it = std::lower_bound(numbers.begin(), numbers.end(), *it_now_deleting_num);
        auto end_num_it = std::upper_bound(begin_num_it, numbers.end(), *it_now_deleting_num);
        std::uint32_t cur_result = std::distance(begin_num_it, end_num_it) * (*it_now_deleting_num);
        deleted_numbers.insert(*it_now_deleting_num);
        bool is_in_start_minus_deleted = IsContains(deleted_numbers, (*it_now_deleting_num) - 1);
        bool is_in_start_plus_deleted = IsContains(deleted_numbers, (*it_now_deleting_num) + 1);
        if (!is_in_start_minus_deleted) deleted_numbers.insert((*it_now_deleting_num) - 1);
        if (!is_in_start_plus_deleted) deleted_numbers.insert((*it_now_deleting_num) + 1);
        cur_result += MaxGoals(numbers, not_equal_numbers, deleted_numbers);
        deleted_numbers.erase(*it_now_deleting_num);
        if (!is_in_start_minus_deleted) deleted_numbers.erase((*it_now_deleting_num) - 1);
        if (!is_in_start_plus_deleted) deleted_numbers.erase((*it_now_deleting_num) + 1);
        if (cur_result > result) result = cur_result;
    }
    return result;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> numbers(n);
    for (auto &&num: numbers) std::cin >> num;
    std::sort(numbers.begin(), numbers.end());
    std::set<std::uint32_t> not_equal_numbers(numbers.begin(), numbers.end());
    std::set<std::uint32_t> deleted_numbers;
    std::uint32_t result = MaxGoals(numbers, not_equal_numbers, deleted_numbers);
    std::cout << result;
    return 0;
}
