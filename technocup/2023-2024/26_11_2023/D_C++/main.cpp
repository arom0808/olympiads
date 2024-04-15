#include <iostream>
#include <vector>

using namespace std;

const uint64_t mod = 998244353ull;

int main() {
    uint32_t n;
    cin >> n;
    vector<vector<vector<uint64_t>>> dp(2, vector<vector<uint64_t>>(3, vector<uint64_t>(n + 1, 0)));
    dp[0][0][1] = 1;
    dp[0][1][1] = 1;
    dp[0][2][1] = 2;
    dp[1][2][1] = 1;
    for (uint32_t i = 1; i < n; ++i) {
        for (uint32_t j = 0; j < 3; ++j) {
            for (uint32_t k = 0; k < 2; ++k) {
                dp[k][j][i + 1] = (dp[k][j][i + 1] + dp[k][j][i]) % mod;
                dp[k][(j + 2) % 3][i + 1] = (dp[k][(j + 2) % 3][i + 1] + dp[k][j][i]) % mod;
                dp[k][(j + 4) % 3][i + 1] = (dp[k][(j + 4) % 3][i + 1] + dp[k][j][i]) % mod;
                dp[1][(j + 5) % 3][i + 1] = (dp[1][(j + 5) % 3][i + 1] + dp[k][j][i]) % mod;
                dp[k][(j + 6) % 3][i + 1] = (dp[k][(j + 6) % 3][i + 1] + dp[k][j][i]) % mod;
                dp[k][(j + 8) % 3][i + 1] = (dp[k][(j + 8) % 3][i + 1] + dp[k][j][i]) % mod;
            }
        }
    }
    cout << (dp[1][1][n] + dp[1][2][n]) % mod;
    return 0;
}
