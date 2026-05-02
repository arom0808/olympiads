#include <iostream>

using namespace std;
using ll = long long;

constexpr int maxn = 60;

int n, m;
ll nums[maxn];
ll pf[maxn + 1];
ll dp[maxn + 1][maxn + 1];

bool can_with_mask(ll mask) {
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = 0;
    dp[0][0] = (1ll << 60) - 1;
    for (int cnc = 1; cnc <= n; ++cnc)
        for (int sc = 1; sc <= m && sc <= cnc; ++sc)
            for (int pnc = cnc - 1; pnc >= 0 && pnc >= sc - 1; --pnc)
                if ((dp[pnc][sc - 1] & (pf[cnc] - pf[pnc]) & mask) == mask)
                    dp[cnc][sc] = dp[pnc][sc - 1] & (pf[cnc] - pf[pnc]) & mask;
    return (dp[n][m] & mask) == mask;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    for (int i = 0; i < n; ++i) pf[i + 1] = pf[i] + nums[i];
    ll mask = 0;
    for (int i = 59; i >= 0; --i) if (can_with_mask(mask | (1ll << i))) mask |= (1ll << i);
    cout << mask << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
