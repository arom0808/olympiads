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

std::uint32_t get_res(std::uint32_t n, std::uint32_t k) {
    std::set<std::uint32_t> set_dividers;
    for (std::uint32_t i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            set_dividers.insert(i);
            set_dividers.insert(n / i);
        }
    }
    std::vector<std::uint32_t> dividers(set_dividers.begin(), set_dividers.end());
    if (dividers.size() < k) return 0;
    std::vector<std::vector<std::vector<std::uint32_t>>>
            dp(dividers.size(), std::vector<std::vector<std::uint32_t>>(k + 1));
    for (std::uint32_t i = 0; i < dividers.size(); ++i) {
        dp[i][1].push_back(dividers[i]);
        for (std::uint32_t pre_i = 0; pre_i < i; ++pre_i) {
            if (gcd(dividers[pre_i], dividers[i]) != 1) continue;
            for (std::uint32_t j = 2; j <= k; ++j) {
                for (const auto &mult: dp[pre_i][j - 1]) {
                    auto n_m = static_cast<std::uint64_t>(mult) * dividers[i];
                    if (n_m <= n) dp[i][j].push_back(n_m);
                }
            }
        }
    }
    std::uint32_t res = 0;
    for (const auto &i: dp) res+= i.back().size();
    return res;
}

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;
    std::cout << get_res(n, k);
    return 0;
}
