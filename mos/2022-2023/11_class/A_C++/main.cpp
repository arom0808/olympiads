#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream input_f("a2.txt");
    std::ofstream output_f("my_a2_ans.txt");
    std::uint32_t t;
    input_f >> t;
    std::vector<std::vector<std::vector<bool>>> results(t);
    for (auto &&result: results) {
        std::uint32_t R, C, A, B;
        input_f >> R >> C >> A >> B;
        std::uint32_t height = R * A, width = C * B;
        result.resize(height, std::vector<bool>(width, false));
        bool row_first_value = true;
        for (std::uint32_t big_y = 0; big_y < R; ++big_y) {
            bool value = row_first_value;
            for (std::uint32_t big_x = 0; big_x < C; ++big_x) {
                if (value) {
                    for (std::uint32_t y = big_y * A; y < (big_y + 1) * A; ++y) {
                        for (std::uint32_t x = big_x * B; x < (big_x + 1) * B; ++x) {
                            result[y][x] = value;
                        }
                    }
                }
                value = !value;
            }
            row_first_value = !row_first_value;
        }
    }
    for (std::uint32_t i = 0; i < t; ++i) {
        for (std::uint32_t y = 0; y < results[i].size(); ++y) {
            for (auto &&x: results[i][y]) output_f << (x ? 'X' : '.');
            if (i < t - 1 || y < results[i].size() - 1) output_f << "\n";
        }
        if (i < t - 1) output_f << "\n";
    }
}
