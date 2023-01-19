#include <iostream>
#include <vector>

std::vector<std::uint32_t> a_nums{10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                                  25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
                                  46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66,
                                  67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87,
                                  88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 110, 210, 310, 410, 510, 610, 710,
                                  810, 910};

int main() {
    std::uint32_t k;
    std::cin >> k;
    std::vector<std::uint32_t> results(k);
    std::uint32_t l, r;
    for (auto &&result: results) {
        std::cin >> l >> r;
        std::uint32_t first = a_nums.size(), second = a_nums.size();
        for (std::uint32_t i = 0; i < a_nums.size(); ++i) {
            if (a_nums[i] >= l) {
                first = i;
                break;
            }
        }
        for (std::int32_t i = a_nums.size() - 1; i >= 0; --i) {
            if (a_nums[i] <= r) {
                second = i;
                break;
            }
        }
        if (first == a_nums.size() || second == a_nums.size() || first > second) {
            result = 0;
            continue;
        }
        result = second - first + 1;
    }
    for (const auto &result: results) std::cout << result << "\n";
    return 0;
}
