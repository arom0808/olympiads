#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

using ll = long long;

constexpr ll maxn = 510;

int n;
int vals[maxn];

int dp[maxn][2];

bool check_cnt(int cnt) {
    for (int i = 0; i <= n; ++i) for (int j = 0; j < 2; ++j) dp[i][j] = -1;
    dp[0][0] = dp[0][1] = cnt;
    for (int i = 0; i < n; ++i) {
        dp[i + 1][0] = std::max(dp[i + 1][0], dp[i][1]);
        if (vals[i] == 1) {
            if (dp[i][0] != -1 && dp[i][0]) dp[i + 1][1] = std::max(dp[i + 1][1], dp[i][0]);
            if (dp[i][1] != -1 && dp[i][1]) dp[i + 1][1] = std::max(dp[i + 1][1], dp[i][1]);
        } else {
            if (dp[i][0] != -1 && dp[i][0] < cnt) dp[i + 1][1] = std::max(dp[i + 1][1], dp[i][0]);
            else if (dp[i][0] != -1) dp[i + 1][1] = std::max(dp[i + 1][1], dp[i][0] - 1);
            if (dp[i][1] != -1 && dp[i][1] < cnt) dp[i + 1][1] = std::max(dp[i + 1][1], dp[i][1]);
            else if (dp[i][1] != -1) dp[i + 1][1] = std::max(dp[i + 1][1], dp[i][1] - 1);
        }
    }
    return dp[n][0] >= 0 || dp[n][1] >= 0;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> vals[i];
    int l = 1, r = n + 1;
    while (r - l != 1) {
        int mid = (l + r) >> 1;
        if (check_cnt(mid)) l = mid;
        else r = mid;
    }
    cout << l;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    // cin >> t;
    while (t--) solve();
    return 0;
}
