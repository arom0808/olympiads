#include <iostream>
#include <vector>
#include <limits>

int main() {
    std::uint32_t n, b;
    std::cin >> n >> b;
    std::vector<std::pair<std::uint32_t, std::uint32_t>> b_divs;
    for (std::uint32_t i = 2; i * i <= b;) {
        if (b % i == 0) {
            if (!b_divs.empty() && b_divs.back().first == i) ++b_divs.back().second;
            else b_divs.emplace_back(i, 1);
            b /= i;
        } else ++i;
    }
    if (!b_divs.empty() && b_divs.back().first == b) ++b_divs.back().second;
    else b_divs.emplace_back(b, 1);
    std::vector<std::uint32_t> h_div_cnts(b_divs.size(), 0);
    for (std::uint32_t i = 0, num; i < n; ++i) {
        std::cin >> num;
        for (std::uint32_t j = 0; j < b_divs.size(); ++j) {
            while (num % b_divs[j].first == 0) {
                ++h_div_cnts[j];
                num /= b_divs[j].first;
            }
        }
    }
    std::uint32_t res = std::numeric_limits<std::uint32_t>::max();
    for (std::uint32_t i = 0; i < b_divs.size(); ++i)
        res = std::min(res, h_div_cnts[i] / b_divs[i].second);
    std::cout << res;
    return 0;
}
