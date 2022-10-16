#include <iostream>
#include <fstream>

//std::uint64_t GetVariantsCount(std::uint32_t number, std::uint32_t digits_count) {
//    if (digits_count == 0) return 0;
//    if (digits_count == 1) { if (number < 10) { return 1; } else { return 0; }}
//    std::uint64_t max_number_with_this_digits_count = 1;
//    for (std::uint32_t i = 0; i < digits_count; --i) max_number_with_this_digits_count *= 10;
//    --max_number_with_this_digits_count;
//    if (number > max_number_with_this_digits_count) return 0;
//}
//
//std::uint64_t FastMethod() {
//    std::uint64_t result_variants = 0;
//    for (std::uint32_t i = 2; i <= 12; ++i)
//        result_variants += GetVariantsCount(12, i);
//    return result_variants;
//}

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

std::uint32_t digits_count(std::uint64_t n) {
    std::uint32_t res = 0;
    for (; n != 0; n /= 10, ++res);
    return res;
}

std::uint64_t SlowMethod() {
    std::uint64_t vars_cnt = 0;
    std::uint64_t prev = 1;
    std::uint64_t max = 111111111120ULL;
    for (std::uint64_t i = 0; i < max; ++i) {
        if (is_zero_exists(i)) continue;
        if (el_sum(i) == 12) ++vars_cnt;
        if (i >= prev * 10) {
            std::cout << "i: " << i << ", digits_count: " << digits_count(i) << std::endl;
            std::cout << "var_cnt:" << vars_cnt << std::endl;
            prev *= 10;
        }
    }
    return vars_cnt;
}

int main() {
    std::uint64_t slow_method_result = SlowMethod();
    std::ofstream result("result.txt");
    std::cout << slow_method_result << std::endl;
    result << slow_method_result << std::endl;
    result.close();
    return 0;
}
