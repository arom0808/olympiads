#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::int64_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::int64_t>> place(n, std::vector<std::int64_t>(m)),
            dp1(n, std::vector<std::int64_t>(m, 0)), dp2(n, std::vector<std::int64_t>(m, 0));
    for (auto &s: place) for (auto &c: s) std::cin >> c;
    for (std::int64_t i = 0; i < n; ++i)
        for (std::int64_t j = 0; j < m; ++j)
            dp1[i][j] = place[i][j] + std::max(i > 0 ? dp1[i - 1][j] : 0, j > 0 ? dp1[i][j - 1] : 0);
    for (std::int64_t i = n - 1; i >= 0; --i)
        for (std::int64_t j = m - 1; j >= 0; --j)
            dp2[i][j] = place[i][j] + std::max(i + 1 < n ? dp2[i + 1][j] : 0, j + 1 < m ? dp2[i][j + 1] : 0);
    std::int64_t res = 1e18;
    for (std::int64_t si = 1, sj = 0; sj + 1 < m; si + 1 < n ? ++si : ++sj) {
        std::int64_t max = 0, sec = 0;
        for (std::int64_t i = si, j = sj; i >= 0 && j < m; --i, ++j) {
            auto val = dp1[i][j] + dp2[i][j] - place[i][j];
            if (val > max) {
                sec = max;
                max = val;
            } else if (val > sec) sec = val;
        }
        if (sec < res) res = sec;
    }
    std::cout << res;
    return 0;
}