#include <iostream>

int main() {
    std::cout << ((-static_cast<long double>(0)) == static_cast<long double>(0));
    std::uint32_t t;
    std::cin >> t;
    for (std::uint32_t i = 0; i < t; ++i) {
        std::uint64_t a = 0, b = 0, c = 0, n, m;
        std::cin >> n;
        for (std::uint64_t k = 1ull << 61; k > 0; k >>= 1) {
            if (3 * k <= n) m = 3;
            else if (3 * (k - 1) >= n) m = 0;
            else if (3 * (k - 1) + k >= n) m = 1;
            else m = 2;
            if (m >= 1) a |= k;
            if (m >= 2) b |= k;
            if (m == 3) c |= k;
            n -= m * k;
        }
        std::cout << a << " " << b << " " << c << "\n";
    }
    return 0;
}