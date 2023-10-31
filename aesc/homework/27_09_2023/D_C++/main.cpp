#include <iostream>
#include <vector>
#include <limits>

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;

    std::vector<std::pair<std::uint32_t, std::uint32_t>> prime_divs;
    for (std::uint64_t i = 2; i * i <= k;) {
        if (k % i == 0) {
            if (!prime_divs.empty() && prime_divs.back().first == i) ++prime_divs.back().second;
            else prime_divs.emplace_back(i, 1);
            k /= i;
        } else ++i;
    }
    if (!prime_divs.empty() && prime_divs.back().first == k) ++prime_divs.back().second;
    else prime_divs.emplace_back(k, 1);

    std::vector<std::uint32_t> fact_pr_divs_cnt(prime_divs.size(), 0);
    for (std::uint32_t i = 0; i < prime_divs.size(); ++i)
        for (std::uint64_t pr_pow = prime_divs[i].first; pr_pow <= n; pr_pow *= prime_divs[i].first)
            fact_pr_divs_cnt[i] += n / pr_pow;

    std::uint32_t res = std::numeric_limits<std::uint32_t>::max();
    for (std::uint32_t i = 0; i < prime_divs.size(); ++i)
        res = std::min(res, fact_pr_divs_cnt[i] / prime_divs[i].second);
    std::cout << res;
    return 0;
}
