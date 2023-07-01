#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include <vector>

std::set<std::uint32_t> two_pows{2, 4, 8, 16, 32, 64, 128, 256};
std::vector<std::uint32_t> two_pows_vec{1, 2, 4, 8, 16, 32, 64, 128, 256};

bool is_sorted(std::list<std::uint32_t>::iterator first, std::list<std::uint32_t>::iterator last) {
    std::uint32_t pre_num = 0;
    for (; first != last; ++first) {
        if (*first < pre_num) return false;
        pre_num = *first;
    }
    return true;
}

std::uint32_t pow2of(std::uint32_t num) {
    for (std::uint32_t i = 0; i < two_pows_vec.size(); ++i) if (num == two_pows_vec[i]) return i;
}

bool is_first_n_equals(const std::vector<std::uint32_t> &sorted_nums,
                       const std::list<std::uint32_t> &nums, std::uint32_t n, std::uint32_t sort_vec_start) {
    auto it = nums.begin();
    for (std::uint32_t i = sort_vec_start; i < sort_vec_start + n; ++i, ++it)
        if (*it != sorted_nums[i])
            return false;
    return true;
}

void SortFirst2PowN(std::vector<std::uint16_t> &moves, const std::vector<std::uint32_t> &sorted_nums,
                    std::list<std::uint32_t> &nums, std::uint32_t n, std::uint32_t sort_vec_start) {
    if (n == 0) return;
    if (n == 1) {
        if (*nums.begin() > *std::next(nums.begin())) {
            nums.splice(nums.begin(), nums, std::next(nums.begin()));
            moves.emplace_back(2);
        }
//        for (auto num: nums) std::cout << num << " ";
//        std::cout << "\n";
        return;
    }
    std::uint32_t start_i = 0;
    auto last_el = std::next(nums.begin(), two_pows_vec[n] - 1);
    while (!is_first_n_equals(sorted_nums, nums, two_pows_vec[n - 1], sort_vec_start)) {
        if (*nums.begin() > *std::next(nums.begin()) && start_i != 1) {
            nums.splice(nums.begin(), nums, std::next(nums.begin()));
            moves.emplace_back(2);
        }
        if (is_first_n_equals(sorted_nums, nums, two_pows_vec[n - 1], sort_vec_start)) break;
        last_el = std::prev(last_el);
        nums.splice(nums.begin(), nums, std::next(last_el));
        ++start_i;
        if (start_i == two_pows_vec[n]) start_i = 0;
        moves.emplace_back(two_pows_vec[n]);
//        for (auto num: nums) std::cout << num << " ";
//        std::cout << "\n";
    }
    for (std::uint32_t i = 0; i < two_pows_vec[n - 1]; ++i) {
        last_el = std::prev(last_el);
        nums.splice(nums.begin(), nums, std::next(last_el));
        moves.emplace_back(two_pows_vec[n]);
    }
    SortFirst2PowN(moves, sorted_nums, nums, n - 1, sort_vec_start + two_pows_vec[n - 1]);
    for (std::uint32_t i = 0; i < two_pows_vec[n - 1]; ++i) {
        last_el = std::prev(last_el);
        nums.splice(nums.begin(), nums, std::next(last_el));
        moves.emplace_back(two_pows_vec[n]);
    }
}

int main() {
    std::list<std::uint32_t> nums;
    std::uint32_t n, g;
    std::cin >> n >> g;
    for (std::uint32_t i = 0, temp; i < n; ++i) {
        std::cin >> temp;
        nums.push_back(temp);
    }
    std::vector<std::uint32_t> sorted_nums(nums.begin(), nums.end());
    std::sort(sorted_nums.begin(), sorted_nums.end());
//    std::uint32_t t_n_pow = std::distance(two_pows_vec.begin(), std::find(two_pows_vec.begin(), two_pows_vec.end(), n));
//    SortFirstTwoPowN(nums, t_n_pow);
    std::uint32_t start_i = 0;
//    std::uint32_t moves_cnt = 0;
    std::vector<std::uint16_t> moves;
    moves.reserve(1e5);
    SortFirst2PowN(moves, sorted_nums, nums, pow2of(nums.size()), 0);
//    while (true) {
//        if (*nums.begin() > *std::next(nums.begin()) && start_i != 1) {
//            nums.splice(nums.begin(), nums, std::next(nums.begin()));
//            moves.emplace_back(2);
//        }
//        for (auto num: nums) std::cout << num << " ";
//        std::cout << "\n";
//        if (is_sorted(nums.begin(), nums.end())) break;
//        nums.splice(nums.begin(), nums, std::prev(nums.end()));
//        ++start_i;
//        if (start_i == n) start_i = 0;
//        moves.emplace_back(n);
//    }
//    for (auto num: nums) std::cout << num << " ";
//    std::cout << "\n";
    std::cout << moves.size() << "\n";
    for (auto move: moves) std::cout << move << " ";

//    for (auto num: nums) std::cout << num << " ";
//    while (!is_sorted(nums)) {
//        auto max_nums_it = std::max_element(on_two_pow_iters.begin(), on_two_pow_iters.end(),
//                                            [](const std::list<std::uint32_t>::iterator &a,
//                                               const std::list<std::uint32_t>::iterator &b) {
//                                                return *a < *b;
//                                            });
//        nums.splice(nums.begin(), nums, std::next(*max_nums_it));
//        on_two_pow_iters.clear();
//        auto tt_it = nums.begin();
//        for (std::uint32_t i = 0; i < n; ++i, ++tt_it)
//            if (two_pows.find(i + 1) != two_pows.end())
//                on_two_pow_iters.push_back(tt_it);
//        for (auto num: nums) std::cout << num << " ";
//    }
    return 0;
}