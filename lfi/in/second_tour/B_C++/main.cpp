#include <iostream>
#include <cmath>
#include <unordered_set>
#include <set>
#include <vector>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::uint32_t m = std::ceil(std::sqrt(static_cast<double>(n)) / 2.0);
    std::unordered_set<std::uint32_t> sums;
    std::set<std::uint32_t> allowed_values;
    for (std::uint32_t i = 1; i <= n; ++i) allowed_values.insert(i);
    std::vector<std::uint32_t> results(m, 0);
    results[0] = 1;
    allowed_values.erase(1);
    results[1] = 3;
    allowed_values.erase(3);
    sums.insert(4);
    allowed_values.erase(2);
    for (std::uint32_t i = 1; i < results.size(); ++i) {
        auto it = allowed_values.begin();
        results[i] = *it;
        allowed_values.erase(it);
        if (i > 0) for (std::uint32_t j = 0; j < i; ++j) sums.insert(results[j] + results[i]);
        for (std::uint32_t j = 0; j < i; ++j) {
            for (const auto &sum: sums) {
                if (sum > results[j]) allowed_values.erase(sum - results[j]);
            }
        }
    }
    std::cout << "Ost elems cnt: " << allowed_values.size() << "\n";
    std::cout << m << "\n";
    for (const auto &res: results) std::cout << res << " ";
    return 0;
}
