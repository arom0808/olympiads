#include <iostream>

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::uint32_t prev_number, cur_number = 0, result = 0;
    for (std::uint32_t i = 0; i < N; ++i) {
        prev_number = cur_number;
        std::cin >> cur_number;
        if (cur_number == 100) if (prev_number != 100) ++result;
    }
    std::cout << result;
    return 0;
}
