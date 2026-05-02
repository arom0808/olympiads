#include <iostream>

using namespace std;

constexpr int maxn = 110, n = 101;

int dp[maxn][maxn];
int tarr[maxn * maxn];
int timer = 0;

void dp_init() {
    dp[0][0] = 0;
    for (int i = 1; i < n; ++i) dp[i][0] = dp[0][i] = dp[i][i] = 1e9;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            // if (!i && !j) continue;
            ++timer;
            for (int u = 1; i - u >= 0 || j - u >= 0; ++u) {
                if (i - u >= 0 && dp[i - u][j] < maxn * maxn) tarr[dp[i - u][j]] = timer;
                if (j - u >= 0 && dp[i][j - u] < maxn * maxn) tarr[dp[i][j - u]] = timer;
                if (i - u >= 0 && j - u >= 0 && dp[i - u][j - u] < maxn * maxn) tarr[dp[i - u][j - u]] = timer;
            }
            int mv = 0;
            while (tarr[mv] == timer) ++mv;
            dp[i][j] = mv;
        }
    }
}

void solve() {
    int m;
    cin >> m;
    int xv = 0;
    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        xv ^= dp[x][y];
    }
    cout << (xv ? "Y" : "N") << "\n";
}

int main() {
    dp_init();
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    cin >> t;
#endif
    while (t--) solve();
    return 0;
}
