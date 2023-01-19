#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

bool
IsBrigsFix(std::vector<std::uint32_t> &heigts, std::uint32_t R, std::uint32_t C, std::uint32_t max_height_diff) {
    if (C == 1) return true;
    std::uint32_t first_i = heigts.size() - R * C;
    do {
        bool is_full_ok = true;
        for (std::uint32_t i = 0; i < R; ++i) {
            std::uint32_t max = 0, min = std::numeric_limits<std::uint32_t>::max();
            for (std::uint32_t j = 0; j < C; ++j) {
                std::uint32_t num = heigts[first_i + i * C + j];
                if (num > max) max = num;
                if (num < min) min = num;
            }
            if (max - min > max_height_diff) {
                is_full_ok = false;
                break;
            }
        }
        if (is_full_ok) return true;
    } while (std::next_permutation(heigts.begin(), heigts.end()));
    return false;
}

std::uint32_t GetMinHeightDiff(std::vector<std::uint32_t> &heigts, std::uint32_t R, std::uint32_t C) {
    std::uint32_t l = 0, r = heigts.back() - heigts.front(), middle = (l + r) / 2;
    while (l != r) {
        if (IsBrigsFix(heigts, R, C, middle)) r = middle;
        else l = middle + 1;
        middle = (l + r) / 2;
    }
    return l;
}

int main() {
    std::uint32_t N, R, C;
    std::cin >> N >> R >> C;
    std::vector<std::uint32_t> heights(N);
    for (auto &&h: heights) std::cin >> h;
    std::sort(heights.begin(), heights.end());
    std::cout << GetMinHeightDiff(heights, R, C);
    return 0;
}
