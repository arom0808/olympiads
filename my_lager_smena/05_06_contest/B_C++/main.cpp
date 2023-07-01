#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::uint32_t Q, M, K;
    std::cin >> Q >> M >> K;
    std::vector<std::uint32_t> kyp_on_poles(M), kyp_on_lines(K);
    for (auto &&r: kyp_on_poles) std::cin >> r;
    for (auto &&r: kyp_on_lines) std::cin >> r;
    std::sort(kyp_on_poles.begin(), kyp_on_poles.end());
    std::vector<std::vector<std::uint32_t>> dp(M, std::vector<std::uint32_t>());
    std::uint32_t kyp_used = 0, olyves_give = 0;
    for (auto r: kyp_on_poles) {

    }
    return 0;
}
