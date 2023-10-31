#include <iostream>
#include <set>
#include <vector>

std::uint32_t gcd(std::uint32_t a, std::uint32_t b) {
    while (b > 0) {
        std::uint32_t c = a;
        a = b;
        b = c % b;
    }
    return a;
}

int main() {
    std::set<std::uint32_t> set_dividers;
    std::uint32_t n;
    std::cin >> n;
    for (std::uint32_t i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            set_dividers.insert(i);
            set_dividers.insert(n / i);
        }
    }
    std::uint32_t res = 0;
    std::vector<std::uint32_t> dividers(set_dividers.begin(), set_dividers.end());
    for (std::uint32_t ia = 0; ia + 1 < dividers.size(); ++ia)
        for (std::uint32_t ib = ia + 1; ib < dividers.size(); ++ib)
            if (dividers[ia] * dividers[ib] <= n && gcd(dividers[ia], dividers[ib]) == 1)
                ++res;
    std::cout << res;
    return 0;
}
