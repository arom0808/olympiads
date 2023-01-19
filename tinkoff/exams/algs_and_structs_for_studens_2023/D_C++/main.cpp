#include <iostream>
#include <vector>
#include <algorithm>

struct Solution {
    std::uint32_t min_x;
    std::uint32_t dividers_count;

    bool operator<(const Solution &other) const {
        return this->min_x < other.min_x;
    }

    bool operator==(const Solution &other) const {
        return this->min_x == other.min_x && this->dividers_count == other.dividers_count;
    }

    explicit Solution(std::uint32_t min_x = 0, std::uint32_t dividers_count = 0)
            : min_x(min_x), dividers_count(dividers_count) {}
};

int main() {
    std::vector<Solution> solutions{Solution{1, 1},
                                    Solution{2, 2},
                                    Solution{3, 2},
                                    Solution{4, 3},
                                    Solution{6, 4},
                                    Solution{8, 4},
                                    Solution{10, 4},
                                    Solution{12, 6},
                                    Solution{18, 6},
                                    Solution{20, 6},
                                    Solution{24, 8},
                                    Solution{30, 8},
                                    Solution{36, 9},
                                    Solution{48, 10},
                                    Solution{60, 12},
                                    Solution{72, 12},
                                    Solution{84, 12},
                                    Solution{90, 12},
                                    Solution{96, 12},
                                    Solution{108, 12},
                                    Solution{120, 16},
                                    Solution{168, 16},
                                    Solution{180, 18},
                                    Solution{240, 20},
                                    Solution{336, 20},
                                    Solution{360, 24},
                                    Solution{420, 24},
                                    Solution{480, 24},
                                    Solution{504, 24},
                                    Solution{540, 24},
                                    Solution{600, 24},
                                    Solution{630, 24},
                                    Solution{660, 24},
                                    Solution{672, 24},
                                    Solution{720, 30},
                                    Solution{840, 32},
                                    Solution{1080, 32},
                                    Solution{1260, 36},
                                    Solution{1440, 36},
                                    Solution{1680, 40},
                                    Solution{2160, 40},
                                    Solution{2520, 48},
                                    Solution{3360, 48},
                                    Solution{3780, 48},
                                    Solution{3960, 48},
                                    Solution{4200, 48},
                                    Solution{4320, 48},
                                    Solution{4620, 48},
                                    Solution{4680, 48},
                                    Solution{5040, 60},
                                    Solution{7560, 64},
                                    Solution{9240, 64},
                                    Solution{10080, 72},
                                    Solution{12600, 72},
                                    Solution{13860, 72},
                                    Solution{15120, 80},
                                    Solution{18480, 80},
                                    Solution{20160, 84},
                                    Solution{25200, 90},
                                    Solution{27720, 96},
                                    Solution{30240, 96},
                                    Solution{32760, 96},
                                    Solution{36960, 96},
                                    Solution{37800, 96},
                                    Solution{40320, 96},
                                    Solution{41580, 96},
                                    Solution{42840, 96},
                                    Solution{43680, 96},
                                    Solution{45360, 100},
                                    Solution{50400, 108},
                                    Solution{55440, 120},
                                    Solution{65520, 120},
                                    Solution{75600, 120},
                                    Solution{83160, 128},
                                    Solution{98280, 128}};
    std::uint32_t n;
    std::cin >> n;
    auto next_it = std::upper_bound(solutions.begin(), solutions.end(), Solution{n, 0});
    auto it = std::prev(next_it);
    std::cout << it->min_x << std::endl << it->dividers_count;
    return 0;
}



//std::uint32_t DividersCount(std::uint32_t x) {
//    std::uint32_t res = 0;
//    for (std::uint32_t divider = 1; divider <= x; ++divider) if (x % divider == 0) ++res;
//    return res;
//}

//    std::uint32_t n = 100000;
//    while (n > 0) {
//        std::uint32_t need_x = 1, need_x_dividers_count = 1, temp_dividers_count;
//        for (std::uint32_t x = n; x >= 1; --x) {
//            temp_dividers_count = DividersCount(x);
//            if (temp_dividers_count > need_x_dividers_count) {
//                need_x_dividers_count = temp_dividers_count;
//                need_x = x;
//            }
//        }
//        std::cout << need_x << ": " << need_x_dividers_count << std::endl;
//        solutions.emplace(need_x, need_x_dividers_count);
//        n = need_x - 1;
//    }
//    std::ofstream result_f("result_file.txt");
//    result_f << "{";
//    for (const auto &sol: solutions) result_f << "{" << sol.min_x << ", " << sol.dividers_count << "}, ";
//    result_f << "}";
//    result_f.close();