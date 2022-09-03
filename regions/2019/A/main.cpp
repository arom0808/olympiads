#include <iostream>

int main() {
    std::uint32_t l, r, a;
    std::cin >> l >> r >> a;
    std::uint64_t res = 0;
    for (std::uint32_t i = l; i < r; ++i) res += (r - i) / a;
    std::cout << res;
    return 0;
}
