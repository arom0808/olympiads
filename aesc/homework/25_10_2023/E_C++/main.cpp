#include <iostream>
#include <vector>
#include <string>
#include <map>

std::vector<std::string> dp(10001);

std::map<std::uint32_t, std::string> rims_nums{{1,    "I"},
                                               {5,    "V"},
                                               {10,   "X"},
                                               {50,   "L"},
                                               {100,  "C"},
                                               {500,  "D"},
                                               {1000, "M"}};

void dp_gen(std::uint32_t num) {
    if (!dp[num].empty() || num == 0) return;
    if (rims_nums.find(num) != rims_nums.end()) {
        dp[num] = rims_nums[num];
        return;
    }
    for (const auto &dig: rims_nums) {
        for (std::uint32_t plus = (num >= dig.first ? num - dig.first : 0), minus = dig.first + plus - num;
             plus < num && minus < num; ++plus, ++minus) {
            dp_gen(plus);
            dp_gen(minus);
            if (dp[num].empty() || dp[plus].size() + dp[minus].size() + 1 < dp[num].size())
                dp[num] = dp[minus] + dig.second + dp[plus];
        }
    }
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    dp_gen(n);
    std::cout << dp[n];
    return 0;
}
