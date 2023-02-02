#include <iostream>
#include <vector>

bool IsKOk(const std::vector<std::uint32_t> &a, const std::vector<std::uint32_t> &b, std::uint32_t k) {
    for (std::uint32_t i = 0; i < a.size(); ++i)
        if ((a[i] / k + (a[i] % k != 0)) > (b[i] / k + (b[i] % k != 0))) return false;
    return true;
}

int main() {
    std::uint32_t t;
    std::cin >> t;
    std::vector<std::vector<std::uint32_t>> results(t);
    std::uint32_t n;
    std::vector<std::uint32_t> a, b;
    for (auto &&result: results) {
        std::cin >> n;
        a.resize(n);
        for (auto &&ff: a) std::cin >> ff;
        b.resize(n);
        for (auto &&ff: b) std::cin >> ff;
        result.reserve(n);
        for (std::uint32_t k = 1; k <= n; ++k)
            if (IsKOk(a, b, k)) result.push_back(k);
    }
    for (const auto &result: results) {
        std::cout << result.size() << "\n";
        for (const auto &v: result) std::cout << v << " ";
        std::cout << "\n";
    }
    return 0;
}
