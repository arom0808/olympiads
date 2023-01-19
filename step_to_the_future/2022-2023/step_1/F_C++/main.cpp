#include <iostream>
#include <vector>

void
TankersVariants(const std::vector<std::uint32_t> &tankers, std::vector<bool> &is_used, std::uint32_t Y,
                std::uint32_t tank_id,
                std::uint32_t cur_oil_count, std::uint32_t &result) {
    if (tank_id == 0) {
        if (cur_oil_count - Y == 0) ++result;
        return;
    }
    for (std::uint32_t i = 0; i < tankers.size(); ++i) {
        if (is_used[i]) continue;
        if (cur_oil_count * 2 >= tankers[i]) {
            is_used[i] = true;
            std::uint32_t next_oil_cnt = (cur_oil_count >= tankers[i] ? cur_oil_count - tankers[i] : 0) + Y;
            TankersVariants(tankers, is_used, Y, tank_id - 1, next_oil_cnt, result);
            is_used[i] = false;
        }
    }
}

int main() {
    std::uint32_t N, Y;
    std::cin >> N >> Y;
    std::vector<std::uint32_t> tankers(N);
    for (auto &&tanker: tankers) std::cin >> tanker;
    std::vector<bool> is_used(N, false);
    std::uint32_t result = 0;
    TankersVariants(tankers, is_used, Y, N, Y, result);
    std::cout << result;
    return 0;
}
