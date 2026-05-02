#include <iostream>

using namespace std;

constexpr int maxn = 5000, inf = 2e9;
int arr[maxn];
int dp[maxn + 1][maxn + 1];
int opt[maxn + 1][maxn + 1];
int pf[maxn + 1];

// void rec_solve(int len, int l, int r, int ql, int qr) {
//     if (l >= r) return;
//     int m = (l + r) / 2;
//     int mv = inf;
//     for (int flen = ql; flen <= qr; ++flen)
//         if (int cv = dp[flen][m] + dp[len - flen - 1][m + flen + 1] - arr[m + flen]; cv < mv)
//             mv = cv, opt[len][m] = flen;
//     dp[len][m] = mv + pf[len + m] - pf[m];
//     rec_solve(len, l, m, opt[len][m], qr);
//     rec_solve(len, m + 1, r, ql, opt[len][m] ? opt[len][m] : len - 1);
// }

bool solve() {
    int n;
    cin >> n;
    if (cin.eof()) return false;
    pf[0] = 0;
    for (int i = 0; i < n; ++i) cin >> arr[i], pf[i + 1] = pf[i] + arr[i];
    for (int i = 0; i < n; ++i) dp[i][i] = 0, opt[i][i] = -1;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) dp[i][j] = 0, opt[i][j] = -1;
    // for (int len = 1; len <= n; ++len) rec_solve(len, 0, n - len + 1, 0, len - 1);
    for (int j = 1; j <= n; ++j) {
        for (int i = j - 1; i >= 0; --i) {
            int fv = opt[i][j - 1], sv = opt[i + 1][j];
            if (fv == -1) fv = i;
            if (sv == -1) sv = j - 1;
            int mv = inf;
            for (int k = fv; k <= sv; ++k) {
                int cv = dp[i][k] + dp[k + 1][j] - arr[k];
                if (cv < mv) mv = cv, opt[i][j] = k;
            }
            dp[i][j] = mv + pf[j] - pf[i];
        }
    }
    // for (int len = 1; len <= n; ++len) {
    // for (int i = 0; i + len <= n; ++i) {
    // }
    // }
    // for (int i = 0; i < n; ++i) {
    // for (int j = i + 1; j < n; ++j) {
    // int mv = inf;
    // for (int flen = 0; flen < j - i; ++flen) {
    // int cv = dp[i][i + flen] + dp[i + flen + 1][j - i - flen - 1] - arr[i + flen];
    // if (cv < mv) mv = cv, opt[i][j] = flen;
    // }
    // }
    // }
    // for (int len = 1; len <= n; ++len) {
    // for (int i = 0; i + len <= n; ++i) {
    // int mv = inf;
    // for (int flen = 0; flen < len; ++flen) {
    // int cv = dp[flen][i] + dp[len - flen - 1][i + flen + 1] - arr[i + flen];
    // if (cv < mv) mv = cv, opt[len][i] = flen;
    // }
    // dp[len][i] = mv + pf[len + i] - pf[i];
    // }
    // }
    // cout << "\n";
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j <= n; ++j) {
    //         cout << opt[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j <= n; ++j) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    cout << dp[0][n] << "\n";
    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    // solve();
    while (solve()) {
    }
    return 0;
}
