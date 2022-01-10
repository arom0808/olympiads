#include <iostream>
#include <cmath>
#include <vector>

int main() {
    const auto one_del_three = static_cast<long double>(1) / static_cast<long double>(3);
    std::uint64_t a, b, k;
    std::cin >> a >> b >> k;
    auto min_square_root = static_cast<std::uint64_t>(ceill(sqrtl(a)));
    auto min_cube_root = static_cast<std::uint64_t>(ceill(powl(a, one_del_three)));
    auto max_square_root = static_cast<std::uint64_t>(floorl(sqrtl(b)));
    auto max_cube_root = static_cast<std::uint64_t>(floorl(powl(b, one_del_three)));
    if ((min_square_root - 1) * (min_square_root - 1) >= a)
        --min_square_root;
    if ((min_cube_root - 1) * (min_cube_root - 1) * (min_cube_root - 1) >= a)
        --min_cube_root;
    if ((max_square_root + 1) * (max_square_root + 1) <= b)
        ++max_square_root;
    if ((max_cube_root + 1) * (max_cube_root + 1) * (max_cube_root + 1) <= b)
        ++max_cube_root;
    std::vector<std::uint64_t> cubes{};
    cubes.reserve(max_cube_root - min_cube_root + 1);
    for (auto cube_root = min_cube_root; cube_root <= max_cube_root; ++cube_root)
        cubes.push_back(cube_root * cube_root * cube_root);
    std::uint64_t result = 0;
    std::uint64_t last_first_cube_index = 0;
    for (auto square_root = min_square_root, square = square_root * square_root;
         square_root <= max_square_root; ++square_root, square = square_root * square_root) {
        bool is_first_cube_founded = false;
        for (auto i = last_first_cube_index; i < cubes.size(); ++i) {
            if (std::max(square, cubes[i]) - std::min(square, cubes[i]) <= k) {
                if (!is_first_cube_founded) {
                    is_first_cube_founded = true;
                    last_first_cube_index = i;
                }
                ++result;
            } else if (is_first_cube_founded)
                break;
        }
    }
    std::cout << result;
    return 0;
}
