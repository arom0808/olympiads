#include <iostream>
#include <vector>

//std::uint32_t GetDpValue(std::vector<std::vector<std::uint32_t>> &dp, std::vector<std::vector<bool>> &visited,
//                         std::vector<std::uint32_t> &prices, std::vector<std::uint32_t> &effects,
//                         std::uint32_t i, std::uint32_t j) {
//    if (visited[i][j]) return dp[i][j];
//    visited[i][j] = true;
//    std::uint32_t pre_max = 0;
//    if (i > 0) pre_max = GetDpValue(dp, visited, prices, effects, i - 1, j);
//    std::uint32_t add_max = 0;
//    if (prices[i] <= j + 1) {
//        if (prices[i] == j + 1 || i == 0) add_max = effects[i];
//        else add_max = effects[i] + dp[i - 1][j - prices[i]];
//        GetDpValue(dp, visited, prices, effects, i - 1, j - prices[i])
//    }
//    dp[i][j] = std::max(pre_max, add_max);
//}

//int main() {
//    std::uint32_t N, K;
//    std::cin >> N >> K;
//    std::vector<std::vector<std::uint64_t>> dp(N, std::vector<std::uint64_t>(K, 0));
//    std::vector<std::vector<bool>> visited(N, std::vector<bool>(K, false));
//    std::vector<std::uint64_t> prices(N), effects(N);
//    for (std::uint32_t i = 0; i < N; ++i) std::cin >> prices[i] >> effects[i];
//    for (std::uint32_t i = 0; i < N; ++i) {
//        for (std::uint32_t j = 0; j < K; ++j) {
//            std::uint32_t pre_max = 0;
//            if (i > 0) pre_max = dp[i - 1][j];
//            std::uint32_t add_max = 0;
//            if (prices[i] <= j + 1) {
//                if (prices[i] == j + 1 || i == 0) add_max = effects[i];
//                else add_max = effects[i] + dp[i - 1][j - prices[i]];
//            }
//            dp[i][j] = std::max(pre_max, add_max);
//        }
//    }
//    for (std::uint32_t i = 0; i < K; ++i) {
//        std::cout << dp[N - 1][i] << " ";
//    }
//    return 0;
//}

int main() {
    std::uint64_t N, K;
    std::cin >> N >> K;
    std::vector<std::uint32_t> prices(N), effects(N);
    std::uint32_t max_price = 0;
    for (std::uint64_t i = 0; i < N; ++i) {
        std::cin >> prices[i] >> effects[i];
        if (prices[i] > max_price) max_price = prices[i];
    }
    ++max_price;
    std::vector<std::vector<std::uint_least64_t>> dp(N, std::vector<std::uint_least64_t>(max_price, 0));
    for (std::uint64_t j = 0; j < K; ++j) {
        for (std::uint64_t i = 0; i < N; ++i) {
            std::uint64_t pre_max = 0;
            if (i > 0) pre_max = dp[i - 1][j % max_price];
            std::uint64_t add_max = 0;
            if (prices[i] <= j + 1) {
                if (prices[i] == j + 1 || i == 0) add_max = effects[i];
                else add_max = effects[i] + dp[i - 1][(j - prices[i]) % max_price];
            }
            dp[i][j % max_price] = std::max(pre_max, add_max);
        }
        std::cout << dp[N - 1][j % max_price] << " ";
    }
    return 0;
}
