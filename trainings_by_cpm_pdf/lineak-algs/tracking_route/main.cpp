#include <iostream>
#include <vector>
#include <limits>

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;
    std::vector<std::uint32_t> h(n);
    for (auto &&e: h) std::cin >> e;
    std::uint32_t up_cnt = 0, min_up_cnt = std::numeric_limits<std::uint32_t>::max();
    for (std::uint32_t i = 1; i < n; ++i) {
        if (h[i] > h[i - 1]) ++up_cnt;
        if (i >= k) if (h[i - k + 1] > h[i - k]) --up_cnt;
        if (i + 1 >= k) if (up_cnt < min_up_cnt) min_up_cnt = up_cnt;
    }
    std::cout << min_up_cnt;
    return 0;
}
