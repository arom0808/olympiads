#include <iostream>

bool is_zero_exists(std::uint64_t n) {
    if (n % 10 == 0) return true;
    while (n / 10 != 0) {
        n /= 10;
        if (n % 10 == 0) return true;
    }
    return false;
}

std::uint32_t el_sum(std::uint64_t n) {
    std::uint32_t res = 0;
    res += n % 10;
    while (n / 10 != 0) {
        n /= 10;
        res += n % 10;
    }
    return res;
}

int main() {
    std::uint64_t vars_cnt = 0;
    std::uint64_t prev = 1;
    std::uint64_t max = 111111111120ULL;
    for (std::uint64_t i = 0; i < max; ++i) {
        if (is_zero_exists(i)) continue;
        if (el_sum(i) == 12) ++vars_cnt;
        if (i >= prev * 10) {
            std::cout << "i: " << i << std::endl;
            std::cout << "var_cnt:" << vars_cnt << std::endl;
            prev *= 10;
        }
    }
    std::cout << vars_cnt << std::endl;
    return 0;
}
