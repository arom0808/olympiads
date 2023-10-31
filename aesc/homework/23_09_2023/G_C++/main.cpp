#include <iostream>
#include <vector>
#include <set>

void get_multipliers(std::uint64_t n, std::vector<std::uint64_t> &multipliers) {
    multipliers.reserve(100);
    while (n != 1) {
        std::uint32_t pre_mult_size = multipliers.size();
        for (std::uint64_t multiplier = 2; multiplier * multiplier <= n; ++multiplier) {
            if (n % multiplier == 0) {
                multipliers.push_back(multiplier);
                n /= multiplier;
                break;
            }
        }
        if (multipliers.size() == pre_mult_size) {
            multipliers.push_back(n);
            n /= n;
        }
    }
}

std::uint64_t pow_mod(std::uint64_t x, std::uint64_t n, std::uint64_t p) {
    std::uint64_t res = 1 % p;
    for (std::uint64_t t_p = x % p; n != 0; n /= 2, t_p = (t_p * t_p) % p)
        if (n % 2 == 1)
            res = (res * t_p) % p;
    return res;
}


std::uint64_t get_n(std::uint64_t a) {
    std::vector<std::uint64_t> full_vec_multipliers;
    get_multipliers(a, full_vec_multipliers);
    std::set<std::uint64_t> set_multipliers(full_vec_multipliers.begin(), full_vec_multipliers.end());
    set_multipliers.emplace(1);
    std::uint64_t fm = 1;
    for (const auto &mult: set_multipliers) fm *= mult;
    for (std::uint64_t n = fm; n <= a; n += fm)
        if (pow_mod(n, n, a) == 0)
            return n;
    return a;
}

int main() {
    std::uint64_t a;
    std::cin >> a;
    std::cout << get_n(a);
    return 0;
}