#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int64_t maxn = 2000;
int64_t n;
int64_t weights[maxn];
int64_t swi[maxn];
int64_t dp[maxn + 1][maxn + 1];


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int64_t i = 0; i < n; ++i) cin >> weights[i];
    iota(begin(swi), next(begin(swi), n), 0);
    sort(begin(swi), next(begin(swi), n), [](int64_t a, int64_t b) { return weights[a] > weights[b]; });
    dp[0][0] = 0;
    for (int64_t l = 0; l <= n; ++l) {
        for (int64_t r = 0; l + r <= n; ++r) {
            if (r < n && l + r < n)
                dp[l][r + 1] = max(dp[l][r + 1],
                                   dp[l][r] + weights[swi[l + r]] * std::abs(swi[l + r] - (n - r - 1)));
            if (l < n && l + r < n)
                dp[l + 1][r] = max(dp[l + 1][r], dp[l][r] + weights[swi[l + r]] * std::abs(swi[l + r] - l));
        }
    }
    int64_t max_res = 0;
    for (int64_t l = 0; l <= n; ++l) max_res = max(max_res, dp[l][n - l]);
    cout << max_res << "\n";
    return 0;
}
