#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 10000, inf = 1e9;

int arr[maxn];
int dp[maxn + 1][maxn + 1];
pair<int, int> dp2[maxn + 1];
bool used[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = -1;
    for (int i = 0; i < n; ++i) cin >> arr[i], dp[i][1] = arr[i];
    for (int len = 2; len <= n; ++len) {
        int fl1 = 1, fl2 = 1;
        for (int start = 0; start < n; ++start) {
            for (int flen = fl1; flen < len; ++flen) {
                int v1 = dp[start][flen], v2 = dp[start + flen][len - flen];
                if (v1 != -1 && v2 != -1 && v2 - v1 <= 1) {
                    fl1 = flen;
                    break;
                }
            }
            for (int flen = fl1; flen < len; ++flen) {
                int v1 = dp[start][flen], v2 = dp[start + flen][len - flen];
                if (v1 != -1 && v2 != -1 && v1 - v2 >= 1) {
                    fl2 = flen;
                    break;
                }
            }
            int v1 = dp[start][fl1], v2 = dp[start + fl1][len - fl1];
            if (v1 != -1 && v2 != -1 && std::abs(v1 - v2) == 1)
                dp[start][len] = std::max(std::max(v1, v2) + 1, dp[start][len]);
            v1 = dp[start][fl2], v2 = dp[start + fl2][len - fl2];
            if (v1 != -1 && v2 != -1 && std::abs(v1 - v2) == 1)
                dp[start][len] = std::max(std::max(v1, v2) + 1, dp[start][len]);
            fl1 = std::max(fl1 - 1, 1), fl2 = std::max(fl2 - 1, 1);
        }
    }
    dp2[0] = {0, 0};
    for (int pf_len = 1; pf_len <= n; ++pf_len) {
        dp2[pf_len] = {inf, inf};
        for (int last_len = 1; last_len <= pf_len; ++last_len) {
            if (dp[pf_len - last_len][last_len] == -1) continue;
            dp2[pf_len] = std::min(dp2[pf_len], make_pair(dp2[pf_len - last_len].first + 1, last_len));
        }
    }
    vector<int> ans;
    int ci = n;
    while (ci) {
        ans.push_back(dp[ci - dp2[ci].second][dp2[ci].second]);
        ci -= dp2[ci].second;
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto el: ans) cout << el << " ";
    cout << "\n";
    return 0;
}
