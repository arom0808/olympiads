#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using Results = std::vector<std::uint32_t>;

inline std::uint32_t cube(const std::uint32_t &v) { return v * v * v; }

bool OnlyCbrtTry(const std::uint32_t &N, std::uint32_t previous_sum, Results &results) {
    auto cbrt = static_cast<std::uint32_t>(std::floor(std::cbrt(static_cast<double>(N - previous_sum))));
    for (auto i = cbrt + 1; i >= cbrt; --i) {
        if (previous_sum + cube(i) == N) {
            results = {i};
            return true;
        }
    }
    return false;
}

bool
RecEnum(std::uint32_t cubes_count, const std::uint32_t &N, std::uint32_t previous_sum, const std::uint32_t &max_cbrt,
        Results &results) {
    if (previous_sum >= N || cubes_count == 0)
        return false;
    auto oct = OnlyCbrtTry(N, previous_sum, results);
    if (cubes_count == 1 || oct)
        return oct;
    auto max = static_cast<std::uint32_t>(std::ceil(std::cbrt(static_cast<double>(N - previous_sum)))) + 1;
    for (std::uint32_t i = max, pr_and_cb = previous_sum + cube(i); i > 0; --i, pr_and_cb = previous_sum + cube(i)) {
        if (pr_and_cb > N)
            continue;
        if (pr_and_cb == N) {
            results = {i};
            return true;
        }
        auto r = RecEnum(cubes_count - 1, N, pr_and_cb, max_cbrt, results);
        if (r) {
            results.push_back(i);
            return true;
        }
    }
    return false;
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    auto max_cbrt = static_cast<std::uint32_t>(std::ceil(std::cbrt(static_cast<double>(N))));
    if (cube(max_cbrt) <= N)
        ++max_cbrt;
    Results results;
    auto res = RecEnum(8, N, 0, max_cbrt, results);
    if (res)
        for (const auto &v: results)
            std::cout << v << " ";
    else
        std::cout << "IMPOSSIBLE";
    return 0;
}
