#include <iostream>
#include <vector>

std::uint32_t
GetProfit(const std::vector<std::int32_t> &a, const std::vector<std::int32_t> &b, std::uint32_t i, std::uint32_t j,
          std::uint32_t X) {
    return X / a[i] * b[j] + (X % a[i]);
}

int main() {
    std::uint32_t N, X;
    std::cin >> N >> X;
    std::vector<std::int32_t> a(N), b(N);
    for (auto &&e: a) std::cin >> e;
    for (auto &&e: b) std::cin >> e;
    std::uint32_t ibest = 0, jbest = 0, imin = 0;
    for (std::uint32_t j = 1; j < a.size(); ++j) {
        if (a[j] < a[imin]) imin = j;
        if (GetProfit(a, b, imin, j, X) > GetProfit(a, b, ibest, jbest, X)) {
            jbest = j;
            ibest = imin;
        }
    }
    std::uint32_t sum_if_sell = GetProfit(a, b, ibest, jbest, X);
    if (sum_if_sell > X) std::cout << sum_if_sell << "\n" << ibest + 1 << " " << jbest + 1;
    else std::cout << X << "\n-1 -1";
    return 0;
}
