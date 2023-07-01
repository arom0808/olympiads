#include <iostream>
#include <vector>

int main() {
    std::uint32_t N;
    std::cin >> N;
    ++N;
    std::vector<std::uint32_t> dp(N, 0);
    dp[0] = 1;
    for (std::uint32_t i = 2; i < N; ++i) {
        dp[i] += dp[i - 2];
        if (i > 2) dp[i] += dp[i - 3];
    }
    std::cout << dp.back();
    return 0;
}
