#include <iostream>
#include <vector>

int main() {
    std::uint32_t N, K;
    std::cin >> N >> K;
    std::vector<std::uint32_t> a(N);
    for (auto &&e: a) std::cin >> e;
    std::uint32_t ibest = 0, jbest = K + 1;
    std::uint32_t imax = 0;
    for (std::uint32_t j = K + 2; j < a.size(); ++j) {
        if (a[j - K - 1] > a[imax]) imax = j - K - 1;
        if (a[j] + a[imax] > a[ibest] + a[jbest]) {
            jbest = j;
            ibest = imax;
        }
    }
    std::cout << ibest + 1 << " " << jbest + 1;
    return 0;
}
