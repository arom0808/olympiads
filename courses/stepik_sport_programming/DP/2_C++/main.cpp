#include <iostream>
#include <vector>

int main() {
    std::uint64_t x, n;
    std::cin >> x >> n;
    std::vector<std::uint64_t> dp(n + 1);
    dp[0] = 0;
    for (std::uint64_t i = 1; i < x; ++i) dp[i] = 1;
    dp[x] = 2;
    if (n > x) for (std::uint64_t i = x + 1; i <= n; ++i) dp[i] = (dp[i - 1] + dp[i - x])%1000000000;
    std::cout << dp[n] << std::endl;
    std::cout << dp[n] % 1000000000;
    return 0;
}
