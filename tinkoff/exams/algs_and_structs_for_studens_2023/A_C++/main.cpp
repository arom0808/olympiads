#include <iostream>

std::uint32_t UintPow(std::uint32_t base, std::uint32_t exp) {
    std::uint32_t result = 1;
    for (std::uint32_t i = 0; i < exp; ++i) result *= base;
    return result;
}

std::uint32_t MySolution(std::uint32_t n) {
    if (n < 3) return 0;
    if (n % 3 != 0) return 0;
    return UintPow(2, n / 3);
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::cout << MySolution(n);
    return 0;
}
