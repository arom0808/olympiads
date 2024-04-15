#include <iostream>
#include <vector>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    uint32_t n = a.size(), m = b.size();
    vector<vector<uint32_t>> dp(n + 1, vector<uint32_t>(m + 1, 0));
    for (uint32_t i = 0; i <= n; ++i) {
        for (uint32_t j = 0; j <= m; ++j) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else dp[i][j] = min(min(dp[i][j - 1] + 1, dp[i - 1][j] + 1), dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
        }
    }
    cout << dp[n][m];
    return 0;
}
