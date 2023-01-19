#include <iostream>

int main() {
    std::uint64_t S;
    std::cin >> S;
    std::uint32_t result = 0;
    std::uint64_t val;
    for (std::uint64_t n = 1; n * (n + 1) / 2 <= S; ++n) {
        val = S + S;
        if (val % n != 0) continue;
        val /= n;
        if (val <= n) continue;
        val = val - n + 1;
        if (val % 2 != 0) continue;
        if (val < 2) continue;
        ++result;
    }
    std::cout << result;
    return 0;
}
