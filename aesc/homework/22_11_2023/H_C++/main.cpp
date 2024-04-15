#include <iostream>
#include <vector>
#include <numeric>

inline bool check(std::uint32_t s1, std::uint32_t s2, std::uint32_t n) {
    auto z1 = s1 & s2, z2 = ~s1 & ~s2 & (1u << n) - 1;
    return !(z1 >> 1 & z1 | z2 >> 1 & z2);
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    if (n > m) std::swap(n, m);
    std::vector<std::uint32_t> now(1 << n, 1), next(1 << n, 0);
    for (std::uint32_t l = 0; l + 1 < m; ++l) {
        for (std::uint32_t i = 0; i < (1 << n); ++i)
            for (std::uint32_t j = 0; j < (1 << n); ++j)
                if (check(i, j, n))
                    next[j] += now[i];
        now.swap(next);
        std::fill(next.begin(), next.end(), 0u);
    }
    std::cout << std::accumulate(now.begin(), now.end(), 0u);
    return 0;
}
