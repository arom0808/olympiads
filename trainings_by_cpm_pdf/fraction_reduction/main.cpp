#include <iostream>

std::uint32_t gcd(std::uint32_t a, std::uint32_t b) {
    if (a > b) std::swap(a, b);
    while (b > 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    std::int32_t a, b;
    std::cin >> a >> b;
    auto n_gcd = static_cast<std::int32_t>(gcd(std::abs(a), std::abs(b)));
    std::cout << (a / n_gcd) << " " << (b / n_gcd);
    return 0;
}
