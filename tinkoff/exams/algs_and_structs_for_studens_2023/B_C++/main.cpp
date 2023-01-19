#include <iostream>
#include <vector>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> cars(n);
    for (auto &&car: cars) std::cin >> car;
    std::uint32_t min = cars[0];
    for (const auto &car: cars) {
        if (car < min) min = car;
        std::cout << min << " ";
    }
    return 0;
}
