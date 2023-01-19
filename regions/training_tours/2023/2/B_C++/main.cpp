#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>

std::random_device dev;
//auto seed = dev();
std::uint32_t seed = 2183301167;
std::mt19937 rng(seed);

void InputHousesFromKeyboard(std::vector<std::uint32_t> &raw_houses, std::uint32_t &K) {
    std::uint32_t N;
    std::cin >> N >> K;
    raw_houses.resize(N);
    for (auto &&raw_house: raw_houses) std::cin >> raw_house;
}

void TransformHouses(const std::vector<std::uint32_t> &raw_houses, std::uint32_t K,
                     std::vector<std::uint32_t> &houses) {
    auto reversed_raw_houses = raw_houses;
    std::reverse(reversed_raw_houses.begin(), reversed_raw_houses.end());
    reversed_raw_houses.erase(reversed_raw_houses.begin());
    if (!reversed_raw_houses.empty()) reversed_raw_houses.erase(std::prev(reversed_raw_houses.end()));
    houses.resize(raw_houses.size() + (K - 1) * (raw_houses.size() - 1), 0);
    auto res_it = houses.begin();
    for (std::uint32_t i_k = 0; i_k < K; ++i_k) {
        if (i_k % 2 == 0) res_it = std::copy(raw_houses.begin(), raw_houses.end(), res_it);
        else res_it = std::copy(reversed_raw_houses.begin(), reversed_raw_houses.end(), res_it);
    }
    if (K % 2 == 0) houses[houses.size() - 1] = raw_houses[0];
}

void GenerateRandomRawHouses(std::vector<std::uint32_t> &raw_houses, std::uint32_t &K) {
    std::uniform_int_distribution dist_N(1, 10), dist_K(1, 10);
    std::uint32_t N = dist_N(rng);
    K = dist_K(rng);
    raw_houses.resize(N);
    for (std::uint32_t i = 0; i < N; ++i) raw_houses[i] = i + 1;
    std::shuffle(raw_houses.begin(), raw_houses.end(), rng);
}

std::uint32_t RightSolution(const std::vector<std::uint32_t> &houses, std::uint32_t N) {
    std::vector<std::uint32_t> dp(houses.size() + 1, 0);
    for (std::uint32_t i = 0; i < houses.size(); ++i) {
        dp[i] = 1;
        for (std::uint32_t j = 0; j < i; ++j) if (houses[j] < houses[i]) dp[i] = std::max(dp[i], 1 + dp[j]);
    }
    std::uint32_t ans = *std::max_element(dp.begin(), dp.end());
    return ans;
}

std::uint32_t MySolution(const std::vector<std::uint32_t> &houses, std::uint32_t N) {
    std::uint32_t minus_inf = 0, plus_inf = std::numeric_limits<std::uint32_t>::max();
    std::vector<std::uint32_t> dp(N + 1, plus_inf);
    dp[0] = minus_inf;
    std::uint32_t max_res = 0;
    for (const auto &house: houses) {
        std::uint32_t j = std::distance(dp.begin(), std::upper_bound(dp.begin(), dp.end(), house));
        if (dp[j - 1] < house && house < dp[j]) {
            dp[j] = house;
            max_res = j;
        }
    }
    return max_res;
}

void PrintGeneratedRawHouses(const std::vector<std::uint32_t> &raw_houses, const std::uint32_t &K) {
    std::cout << "N: " << raw_houses.size() << ", K: " << K << std::endl;
    for (const auto &raw_house: raw_houses) std::cout << raw_house << " ";
    std::cout << std::endl;
}

void PrintTransformedHouses(const std::vector<std::uint32_t> &houses) {
    for (const auto &house: houses) std::cout << house << " ";
    std::cout << std::endl;
}

int main() {
    std::cout << "seed: " << seed << std::endl;
    std::vector<std::uint32_t> raw_houses, houses;
    std::uint32_t K;
//    InputHousesFromKeyboard(raw_houses, K);
    GenerateRandomRawHouses(raw_houses, K);
    PrintGeneratedRawHouses(raw_houses, K);
    TransformHouses(raw_houses, K, houses);
    PrintTransformedHouses(houses);

    std::uint32_t my_res = MySolution(houses, raw_houses.size());
    std::cout << "My: " << my_res << std::endl;

    std::uint32_t right_res = RightSolution(houses, raw_houses.size());
    std::cout << "Right: " << right_res << std::endl;

    return 0;
}
