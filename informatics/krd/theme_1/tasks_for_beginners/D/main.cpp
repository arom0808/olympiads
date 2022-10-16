#include <iostream>
#include <vector>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> sides(n);
    for (auto &&side: sides) std::cin >> side;
    std::uint32_t result = 0;
    for (std::uint32_t first_side_id = 0; first_side_id < n - 2; ++first_side_id) {
        for (std::uint32_t second_side_id = first_side_id + 1; second_side_id < n - 1; ++second_side_id) {
            for (std::uint32_t third_side_id = second_side_id + 1; third_side_id < n; ++third_side_id) {
                std::uint32_t first_side = sides[first_side_id],
                        second_side = sides[second_side_id],
                        third_side = sides[third_side_id];
                if (first_side + second_side <= third_side) continue;
                if (first_side + third_side <= second_side) continue;
                if (second_side + third_side <= first_side) continue;
                ++result;
            }
        }
    }
    std::cout << result;
    return 0;
}
