#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int32_t n = a.size(), m = b.size();
    vector<vector<int32_t>> dp(n + 1, vector<int32_t>(m + 1, 0));
    for (int32_t i = 0; i <= n; ++i) {
        for (int32_t j = 0; j <= m; ++j) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else dp[i][j] = min(min(dp[i][j - 1] + 1, dp[i - 1][j] + 1), dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
        }
    }
    int32_t ic;
    cin >> ic;
    string temp_s;
    set<string> strs;
    for (uint32_t i = 0; i < ic; ++i) {
        cin >> temp_s;
        strs.emplace(std::move(temp_s));
    }
    
    return 0;
}