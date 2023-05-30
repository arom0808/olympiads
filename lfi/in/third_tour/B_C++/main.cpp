#include <iostream>
#include <cmath>

int main() {
    std::int64_t R;
    std::cin >> R;
    std::uint64_t res = 0;
    for (std::int64_t m = 1; m < R; ++m)
        res += static_cast<std::int64_t>(std::sqrt(static_cast<long double>(R * R - m * m)));
    std::cout << (1 + (res + R) * 4);
    return 0;
}
