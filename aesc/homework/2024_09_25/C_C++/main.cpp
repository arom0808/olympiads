#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

struct PV {
    long double x, y;

    explicit PV(long double x = 0, long double y = 0) : x(x), y(y) {}

    [[nodiscard]] long double dist(const PV &other) const {
        return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

const int32_t maxn = 15;
const long double inf = 1e18;
long double g[maxn][maxn], dp[1 << maxn][maxn];
int32_t pr[1 << maxn][maxn], ans[maxn + 1];
PV points[maxn];
int32_t n;


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int32_t i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;
    for (auto &row: dp) for (auto &el: row) el = inf;
    for (auto &row: pr) for (auto &el: row) el = -1;
    for (int32_t i = 0; i < n; ++i)
        for (int32_t j = i + 1; j < n; ++j)
            g[i][j] = g[j][i] = points[i].dist(points[j]);
    dp[0][0] = dp[1][0] = 0;
    pr[1][0] = 0;
    for (int32_t mask = 1; mask < (1 << n); ++mask) {
        for (int32_t v = 0; v < n; ++v) {
            if (!((mask >> v) & 1)) continue;
            for (int32_t u = 0; u < n; ++u) {
                if (v == u || (u != 0 && !((mask >> u) & 1))) continue;
                if (dp[mask][v] > dp[mask & (~(1 << v))][u] + g[u][v])
                    dp[mask][v] = dp[mask & (~(1 << v))][u] + g[u][v], pr[mask][v] = u;
            }
        }
    }
    for (int32_t i = 0, pre_mask, mask = (1 << n) - 1, v = 0;
         v != -1; pre_mask = mask, mask &= (~(1 << v)), v = pr[pre_mask][v], ++i)
        ans[i] = v;
    reverse(next(begin(ans)), next(begin(ans), n));
    cout << fixed << setprecision(20) << dp[(1 << n) - 1][0] << "\n";
    for (int32_t i = 1; i < n; ++i) cout << ans[i] + 1 << " ";
    return 0;
}
