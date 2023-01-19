#include <iostream>
#include <vector>
#include <algorithm>

const std::vector<std::uint32_t> easy_nums{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};

bool IsVeryEasy(std::uint64_t num) {
    std::uint32_t ones_count = 0, last_one = 64;
    for (size_t i = 0; i < 64; ++i, num >>= 1) {
        if ((num & 1ULL) == 1ULL) {
            ++ones_count;
            last_one = i;
        }
    }
    if (!std::binary_search(easy_nums.begin(), easy_nums.end(), ones_count)) return false;
    if (!std::binary_search(easy_nums.begin(), easy_nums.end(), (last_one + 1) - ones_count)) return false;
    return true;
}

int main() {
    std::uint64_t L, R;
    std::cin >> L >> R;
    std::uint64_t result = 0;
    for (std::uint64_t num = L; num <= R; ++num)
        if (IsVeryEasy(num)) ++result;
    std::cout << result;
    return 0;
}
