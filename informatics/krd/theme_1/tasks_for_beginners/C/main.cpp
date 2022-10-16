#include <iostream>

int main() {
    std::uint32_t number;
    std::cin >> number;
    for (std::uint32_t three_count = 0; three_count * 3 <= number; ++three_count) {
        std::uint32_t five_count = (number - (three_count * 3)) / 5;
        if (three_count * 3 + five_count * 5 == number) {
            std::cout << three_count << " " << five_count;
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE";
    return 0;
}
