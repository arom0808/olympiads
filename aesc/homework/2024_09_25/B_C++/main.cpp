#include <iostream>
#include <algorithm>

using namespace std;

const int32_t maxn = 10, inf = 1e9;
int32_t n;
int32_t g[maxn][maxn];
int32_t dp[1 << maxn][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int32_t i = 0; i < n; ++i)
        for (int32_t j = 0; j < n; ++j)
            cin >> g[i][j], g[i][j] = (g[i][j] ? g[i][j] : inf);
    for (auto &row: dp) for (auto &el: row) el = inf;
    dp[0][0] = dp[1][0] = 0;
    for (int32_t mask = 1; mask < (1 << n); ++mask) {
        for (int32_t v = 0; v < n; ++v) {
            if (!((mask >> v) & 1)) continue;
            for (int32_t u = 0; u < n; ++u) {
                if (v == u || (u != 0 && !((mask >> u) & 1))) continue;
                dp[mask][v] = std::min(dp[mask][v], dp[mask & (~(1 << v))][u] + g[u][v]);
            }
        }
    }
    if (dp[(1 << n) - 1][0] < inf) cout << dp[(1 << n) - 1][0] << "\n";
    else cout << "-1\n";
    return 0;
}
