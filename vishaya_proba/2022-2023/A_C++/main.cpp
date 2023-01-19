#include <iostream>

std::uint32_t FirstMethodCount(std::uint32_t n, std::uint32_t m) {
    return n * (m - 1);
}

std::uint32_t SecondMethodCount(std::uint32_t n, std::uint32_t m) {
    std::uint32_t result = 0;
    for (std::uint32_t i = 0; i / n <= m; i += n)
        if (i % m != 0) ++result;
    return result;
}

std::uint32_t GetCutCount(std::uint32_t n, std::uint32_t m) {
    if (n / m > 0) n -= (n / m) * m;
    if (n == 0) return 0;
    std::uint32_t min_result = FirstMethodCount(n, m);
    min_result = std::min(min_result, SecondMethodCount(n, m));
    return min_result;
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::uint32_t result = GetCutCount(n, m);
    std::cout << result;
    return 0;
}
