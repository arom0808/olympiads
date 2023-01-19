#include <iostream>
#include <vector>
#include <map>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> ratings(n);
    for (auto &&rate: ratings) std::cin >> rate;
    std::uint32_t q;
    std::cin >> q;
    std::vector<std::uint32_t> results(q);
    std::uint32_t li, ri;
    std::uint32_t l, r;
    std::map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t> cache_1;
    for (std::uint32_t i = 0; i < q; ++i) {
        std::cin >> li >> ri;
        if (i == 0) {
            l = li - 1;
            r = ri - 1;
        } else {
            l = (li + results[i - 1]) % n;
            r = (ri + results[i - 1]) % n;
        }
        if (l > r) std::swap(l, r);
        auto c1_it = cache_1.find({l, r});
        if (c1_it != cache_1.end()) {
            results[i] = c1_it->second;
            continue;
        }
        std::map<std::uint32_t, std::uint32_t> unique_numbers_count;
        for (std::uint32_t j = l; j <= r; ++j) {
            auto un_it = unique_numbers_count.find(ratings[j]);
            if (un_it == unique_numbers_count.end()) unique_numbers_count.emplace(ratings[j], 1);
            else ++un_it->second;
        }
        results[i] = r - l + 1;
        for (const auto &unique_rating_and_count: unique_numbers_count) {
            results[i] += unique_rating_and_count.second * (unique_rating_and_count.second - 1) / 2;
        }
        cache_1.emplace(std::pair<std::uint32_t, std::uint32_t>{l, r}, results[i]);
    }
    for (const auto &result: results) std::cout << result << "\n";
    return 0;
}
