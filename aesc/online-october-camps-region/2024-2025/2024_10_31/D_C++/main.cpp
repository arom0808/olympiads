#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 50, inf = 1e9;

int n, k;
pair<int, int> minmax_row[maxn];
int dp[maxn + 1][maxn];
int max_ry = 0;

int main() {
    cin >> n >> k;
    for (int i = 0; i < maxn; ++i) minmax_row[i] = {maxn, 0};
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y, --x, --y;
        minmax_row[y].first = std::min(minmax_row[y].first, x);
        minmax_row[y].second = std::max(minmax_row[y].second, x);
        if (y > max_ry) max_ry = y;
    }
    for (int i = 0; i < maxn; ++i) if (minmax_row[i].first > minmax_row[i].second) minmax_row[i] = {-1, -1};
    for (int i = 0; i < maxn; ++i) dp[0][i] = i;
    for (int y = 1; y <= maxn; ++y) {
        for (int x = 0; x < maxn; ++x) {
            dp[y][x] = inf;
            for (int px = 0; px < maxn; ++px) {
                int dist;
                if (minmax_row[y - 1].first == -1) dist = std::abs(x - px) + 1;
                else {
                    int d1 = std::abs(px - minmax_row[y - 1].first) +
                             std::abs(minmax_row[y - 1].first - minmax_row[y - 1].second) +
                             std::abs(minmax_row[y - 1].second - x) + 1;
                    int d2 = std::abs(px - minmax_row[y - 1].second) +
                             std::abs(minmax_row[y - 1].second - minmax_row[y - 1].first) +
                             std::abs(minmax_row[y - 1].first - x) + 1;
                    dist = std::min(d1, d2);
                }
                dp[y][x] = std::min(dp[y][x], dist + dp[y - 1][px]);
            }
        }
    }
    int ans = inf;
    for (int x = 0; x < maxn; ++x) ans = std::min(ans, dp[max_ry + 1][x] - 1);
    cout << ans << "\n";
    return 0;
}
