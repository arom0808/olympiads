#include <iostream>
#include <vector>

using namespace std;

const int64_t mod = 1e9 + 7;

int main() {
    int64_t n, k;
    cin >> n >> k;
    int64_t lmax = min(n, k);
    vector<vector<int64_t>> dp(lmax + 1, vector<int64_t>(n, 0));
    vector<int64_t> sufsum1(n), sufsum2(n);
    dp[2][n - 2] = 2;
    for (int64_t i = 3; i <= lmax; ++i) {
        for (int64_t j = n - 1; j >= 0; --j) {
            if (j % 2 == 0) sufsum1[j] = ((j + 2 < n ? sufsum1[j + 2] : 0ll) + dp[i - 1][j]) % mod;
            else sufsum2[j] = ((j + 2 < n ? sufsum2[j + 2] : 0ll) + dp[i - 1][j]) % mod;
        }
        for (int64_t j = n - 1; j >= 0; --j) {
            if (j + 1 < n) {
                if ((j + 1) % 2 == 0) dp[i][j] += sufsum1[j + 1];
                else dp[i][j] += sufsum2[j + 1];
            }
            if (j + i - 1 < n) {
                if ((j + i - 1) % 2 == 0) dp[i][j] += sufsum1[j + i - 1];
                else dp[i][j] += sufsum2[j + i - 1];
            }
        }
    }
    vector<int64_t> al(lmax + 1, 0);
    for (int64_t i = 2; i <= lmax; ++i) for (int64_t j = 0; j < n; ++j) al[i] = (al[i] + dp[i][j]) % mod;
    int64_t res = 0;
    for (int64_t i = 2; i <= lmax; ++i) res = (res + al[i] * (k + 1 - i)) % mod;
    cout << res;
    return 0;
}
