#include <iostream>

std::pair<bool, std::uint64_t> MyDecision(std::int64_t k) {
    std::uint64_t res;
    bool is_res_exists;
    if (k == 0) {
        res = 0;
        is_res_exists = true;
    } else if (k > 0) {
        is_res_exists = false;
        res = 0xffffffffffffffffULL;
        for (std::uint64_t b_minus_a = 1, b_plus_a = k / b_minus_a;
             b_minus_a <= b_plus_a; ++b_minus_a, b_plus_a = k / b_minus_a) {
            if (b_minus_a * b_plus_a == k) {
                std::uint64_t two_b = b_minus_a + b_plus_a;
                if (two_b % 2 == 0) {
                    is_res_exists = true;
                    if (two_b / 2 < res) res = two_b / 2;
                }
            }
        }
    } else {
        is_res_exists = false;
        res = 0xffffffffffffffffULL;
        k = -k;
        for (std::uint64_t a_minus_b = 1, a_plus_b = k / a_minus_b;
             a_minus_b <= a_plus_b; ++a_minus_b, a_plus_b = k / a_minus_b) {
            if (a_minus_b * a_plus_b == k) {
                std::uint64_t two_b = a_plus_b - a_minus_b;
                if (two_b % 2 == 0) {
                    is_res_exists = true;
                    if (two_b / 2 < res) res = two_b / 2;
                }
            }
        }
    }
    return {is_res_exists, res};
}

int main() {
    std::int64_t k;
    std::cin >> k;
    auto res = MyDecision(k);
    if (!res.first) std::cout << "none";
    else std::cout << res.second;
    return 0;
}
