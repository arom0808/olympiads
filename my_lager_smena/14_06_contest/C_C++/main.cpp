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

//void SortFirstTwoPowN(std::list<std::uint32_t> &nums, std::uint32_t n) {
//    if (n == 1) {
//        if (*nums.begin() > *std::next(nums.begin()))
//            nums.splice(nums.begin(), nums, std::next(nums.begin()));
//    } else {
//        SortFirstTwoPowN(nums, n - 1);
//        auto s_for_move = std::next(nums.begin(), two_pows_vec[n] - 1);
//        for (std::uint32_t i = 0; i < two_pows_vec[n - 1]; ++i) {
//            s_for_move = std::prev(s_for_move);
//            nums.splice(nums.begin(), nums, std::next(s_for_move));
//        }
//        SortFirstTwoPowN(nums, n - 1);
//        auto mid = std::next(nums.begin(), two_pows_vec[n - 1] - 1),
//                right = std::next(mid, two_pows_vec[n - 1]);
//        for (std::uint32_t moved = 0; moved < two_pows_vec[n]; ++moved) {
//            if (moved < two_pows_vec[n - 1]) {
//                auto to_move = mid;
//                if (*right > *mid) to_move = right;
//                mid = std::prev(mid);
//                if (to_move == right) right = std::prev(right);
//                nums.splice(nums.begin(), nums, to_move);
//            } else {
//                auto to_move = right;
//                mid = std::prev(mid);
//                right = std::prev(right);
//                nums.splice(nums.begin(), nums, to_move);
//            }
//        }
//        auto max_it = nums.begin();
//        for (auto it = nums.begin(); it != nums.end(); ++it) if (*it >= *max_it) max_it = it;
//        while (max_it != std::prev(nums.end())) {
//            nums.splice(nums.begin(), nums, std::prev(nums.end()));
//        }
//}
//}

int main() {
    std::list<std::uint32_t> nums;
    std::uint32_t n, g;
    std::cin >> n >> g;
    for (std::uint32_t i = 0, temp; i < n; ++i) {
        std::cin >> temp;
        nums.push_back(temp);
    }
//    std::uint32_t t_n_pow = std::distance(two_pows_vec.begin(), std::find(two_pows_vec.begin(), two_pows_vec.end(), n));
//    SortFirstTwoPowN(nums, t_n_pow);
    std::uint32_t start_i = 0;
//    std::uint32_t moves_cnt = 0;
    std::vector<std::uint16_t> moves;
    moves.reserve(1e6);
    while (true) {
        for (auto t_pow: two_pows_vec) {
            if (t_pow == 1 || t_pow > n) continue;
            auto it = std::next(nums.begin(), t_pow - 1);
            if (*nums.begin() > *it && (start_i == 0 || start_i >= t_pow)) {
                nums.splice(nums.begin(), nums, it);
                moves.emplace_back(t_pow);
            }
        }
        if (is_sorted(nums.begin(), nums.end())) break;
        nums.splice(nums.begin(), nums, std::prev(nums.end()));
        ++start_i;
        if (start_i == n) start_i = 0;
        moves.emplace_back(n);
    }
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
