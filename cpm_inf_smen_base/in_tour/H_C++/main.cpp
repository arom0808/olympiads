#include <iostream>
#include <string>
#include <vector>
#include <limits>

const std::uint32_t uint32_max = std::numeric_limits<std::uint32_t>::max();

//std::uint32_t GetDP(const std::string &pattern, std::vector<std::vector<std::uint32_t>> &dp, std::uint32_t length,
//                    std::uint32_t balance) {
//    if (dp[length][balance] != uint32_max) return dp[length][balance];
//    if (pattern[length] == '(') {
//        if (length == 0 || balance == 0) dp[length][balance] = 0;
//        else dp[length][balance] = GetDP(pattern, dp, length - 1, balance - 1);
//    } else if (pattern[length] == ')') {
//        if (length == 0 || balance >= pattern.size()) dp[length][balance] = 0;
//        else dp[length][balance] = GetDP(pattern, dp, length - 1, balance + 1);
//    } else {
//        dp[length][balance] = 0;
//        if (length > 0 && balance > 0) dp[length][balance] += GetDP(pattern, dp, length - 1, balance - 1);
//        if (length > 0 && balance < pattern.size()) dp[length][balance] += GetDP(pattern, dp, length - 1, balance + 1);
//    }
//    return dp[length][balance];
//}

int main() {
    std::string pattern;
    std::cin >> pattern;
    std::vector<std::vector<std::uint32_t>> dp(pattern.size() + 1,
                                               std::vector<std::uint32_t>(pattern.size() + 1, uint32_max));
    for (std::uint32_t i = 0; i <= pattern.size(); ++i) dp[0][i] = 0;
    dp[0][0] = 1;
    for (std::uint32_t i = 0; i <= pattern.size(); ++i) {
        for (std::uint32_t j = 0; j <= pattern.size(); ++j) {
            if (dp[i][j] != uint32_max) continue;
            if (pattern[i] == '(') {
                if (i == 0 || j == 0) dp[i][j] = 0;
                else dp[i][j] = dp[i - 1][j - 1];
            } else if (pattern[i] == ')') {
                if (i == 0 || j >= pattern.size()) dp[i][j] = 0;
                else dp[i][j] = dp[i - 1][j + 1];
            } else {
                dp[i][j] = 0;
                if (i > 0 && j > 0) dp[i][j] += dp[i - 1][j - 1];
                if (i > 0 && j < pattern.size()) dp[i][j] += dp[i - 1][j + 1];
            }
        }
    }
    std::cout << dp[pattern.size()][0];
    return 0;
}
