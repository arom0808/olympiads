#include <iostream>
#include <vector>

bool IsCowsFit(const std::vector<std::uint32_t> &stoiles, std::uint32_t K, std::uint32_t min_distance) {
    std::uint32_t pre_stoilo_x = stoiles.front();
    --K;
    if (K == 0) return true;
    for (std::uint32_t i = 1; i < stoiles.size() && K != 0; ++i) {
        if (stoiles[i] - pre_stoilo_x >= min_distance) {
            --K;
            pre_stoilo_x = stoiles[i];
        }
    }
    return K == 0;
}

std::uint32_t GetMinimumDistance(const std::vector<std::uint32_t> &stoiles, std::uint32_t K) {
    std::uint32_t l = 0, r = stoiles.back(), middle = (l + r) / 2;
    while (l != r) {
        if (IsCowsFit(stoiles, K, middle)) l = middle;
        else r = middle - 1;
        middle = (l + r) / 2 + (l + r) % 2;
    }
    return l;
}

int main() {
    std::uint32_t N, K;
    std::cin >> N >> K;
    std::vector<std::uint32_t> stoiles(N);
    for (auto &&stoilo: stoiles) std::cin >> stoilo;
    std::cout << GetMinimumDistance(stoiles, K);
    return 0;
}
