#include <iostream>
#include <vector>
#include <numeric>
//#include <algorithm>
//#include <random>
//#include <functional>
//#include <fstream>
//
//std::random_device dev;
//std::uint32_t seed = dev();
//std::mt19937 rng(seed);
//
//template<typename InputType, typename OutType>
//std::pair<InputType, std::pair<OutType, OutType>> AutoTest(
//        const std::function<void(InputType &)> &generator_f,
//        const std::function<void(InputType &, OutType &)> &right_solution_f,
//        const std::function<void(InputType &, OutType &)> &my_solution_f,
//        const std::function<bool(OutType, OutType)> &is_result_equal_f = std::equal_to()) {
//    while (true) {
//        InputType input;
//        generator_f(input);
//        OutType right_res, my_res;
//        right_solution_f(input, right_res);
//        my_solution_f(input, my_res);
//        if (!is_result_equal_f(right_res, my_res)) return {input, {right_res, my_res}};
//    }
//}
//
//std::uint32_t BinSearchDoCount(std::vector<std::uint32_t> &array, std::int32_t left, std::int32_t right) {
//    if (right <= left) return 0;
//    auto q = array[(left + right) / 2];
//    auto i = left, j = right;
//    std::uint32_t result = 0;
//    while (i <= j) {
//        while (array[i] < q) {
//            ++i;
//            ++result;
//        }
//        while (q < array[j]) {
//            --j;
//            ++result;
//        }
//        if (i <= j) {
//            std::swap(array[i], array[j]);
//            ++i;
//            --j;
//        }
//    }
//    result += BinSearchDoCount(array, left, j);
//    result += BinSearchDoCount(array, i, right);
//    return result;
//}

void MySolution(std::uint32_t &n, std::vector<std::uint32_t> &res) {
    res.resize(n);
    auto positions = res;
    std::iota(positions.begin(), positions.end(), 0);
    for (std::uint32_t i = 0; i < res.size(); ++i) {
        auto const cur_pos = (res.size() - 1 + i) / 2;
        res[positions[cur_pos]] = i + 1;
        std::swap(positions[cur_pos], positions[i]);
    }
}

//void RightSolution(std::uint32_t &n, std::vector<std::uint32_t> &res) {
//    res.clear();
//    std::vector<std::uint32_t> nums(n);
//    std::iota(nums.begin(), nums.end(), 1);
//    std::uint32_t max_res = 0;
//    do {
//        auto copy_nums = nums;
//        std::uint32_t cur_res = BinSearchDoCount(copy_nums, 0, n - 1);
//        if (cur_res > max_res) {
//            max_res = cur_res;
//            res = nums;
//        }
//    } while (std::next_permutation(nums.begin(), nums.end()));
//}
//
//void Generator(std::uint32_t &n) {
//    std::uniform_int_distribution dist_n(10, 10);
//    n = dist_n(rng);
//}
//
//void WriteInput(const std::uint32_t &n) {
//    std::ofstream out("in.txt");
//    out << n;
//    out.close();
//}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> nums;
    MySolution(n, nums);
    for (const auto &num: nums) std::cout << num << " ";
//    std::cout << seed << std::endl;
//    auto IsEqualF = [](std::vector<std::uint32_t> a, std::vector<std::uint32_t> b) {
//        return BinSearchDoCount(a, 0, a.size() - 1) == BinSearchDoCount(b, 0, b.size() - 1);
//    };
//    auto not_right_example = AutoTest<std::uint32_t, std::vector<std::uint32_t>>
//            (&Generator, &RightSolution, &MySolution, IsEqualF);
//    auto right_copy = not_right_example.second.first, my_copy = not_right_example.second.second;
//    std::uint32_t right_do_cnt = BinSearchDoCount(right_copy, 0, right_copy.size() - 1),
//            my_do_cnt = BinSearchDoCount(my_copy, 0, my_copy.size() - 1);
//    std::cout << "Inputs:\n" << not_right_example.first << "\n";
//    std::cout << "\nRight solution:\n";
//    std::cout << "Do count: " << right_do_cnt << "\n";
//    for (const auto &ff: not_right_example.second.first) std::cout << ff << " ";
//    std::cout << "\n";
//    std::cout << "\nMy solution:\n";
//    std::cout << "Do count: " << my_do_cnt << "\n";
//    for (const auto &ff: not_right_example.second.second) std::cout << ff << " ";
//    std::cout << "\n";
//    WriteInput(not_right_example.first);
    return 0;
}
