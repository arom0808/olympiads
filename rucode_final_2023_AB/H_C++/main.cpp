#include <iostream>

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::uint32_t res = 0;
    while (n > 0 || m > 0) {
        for (std::uint32_t i = 0; i < 3; ++i) if (n > 0) --n;
        for (std::uint32_t i = 0; i < 3; ++i) if (m > 0) --m;
        if (n > m && n > 0) --n;
        else if (m > 0) --m;
        res += 2;
    }
    std::cout << res - 1;
    return 0;
}
