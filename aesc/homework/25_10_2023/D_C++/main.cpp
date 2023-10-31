
#include <iostream>

std::uint32_t translate_from_p_to_dec(std::uint32_t p_num, std::uint32_t p) {
    std::uint32_t res = 0, p_pow = 1;
    while (p_num != 0) {
        res += (p_num % 10) * p_pow;
        p_num /= 10;
        p_pow *= p;
    }
    return res;
}

std::uint32_t dig_cnt(std::uint32_t num) {
    std::uint32_t res = 0;
    do {
        num /= 10;
        ++res;
    } while (num != 0);
    return res;
}

std::uint32_t reverse_num(std::uint32_t num) {
    std::uint32_t res = 0;
    while (num != 0) {
        res = res * 10 + num % 10;
        num /= 10;
    }
    return res;
}

std::uint32_t get_min_max_p(std::uint32_t dec_num, std::uint32_t rev_dec_num, bool minmax) {
    std::uint32_t l = 2, r = dec_num, dnl = dig_cnt(dec_num);
    while (l < r) {
        std::uint32_t m = (l + r) / 2 + (l + r) % 2, nl = dig_cnt(translate_from_p_to_dec(rev_dec_num, m));
        if (minmax ? nl > dnl : nl >= dnl) r = m - 1;
        else l = m + 1;
    }
    return l;
}

int main() {
    std::uint32_t dec_num;
    std::cin >> dec_num;
    std::uint32_t rev_dec_num = reverse_num(dec_num);
    auto min_p = get_min_max_p(dec_num, rev_dec_num, false), max_p = get_min_max_p(dec_num, rev_dec_num, true);
    for (std::uint32_t p = min_p; p <= max_p; ++p)
        if (translate_from_p_to_dec(rev_dec_num, p) == dec_num)
            std::cout << p << "\n";
    return 0;
}