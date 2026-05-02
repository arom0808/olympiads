#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

using ll = std::int64_t;
using ld = long double;

constexpr int maxn = 1e5, maxk = 100;

int n, k;
int arr[maxn];
ll pf[maxn + 1];
ll sq_pf[maxn + 1];
ld dp[maxk + 1][maxn + 1];
int opt[maxk + 1][maxn + 1];


ld opt_seg_x(int l, int r) {
    return static_cast<ld>(pf[r] - pf[l]) / (r - l);
}

ld val_for_seg(int l, int r, ld x) {
    return x * x * (r - l) - x * 2 * (pf[r] - pf[l]) + (sq_pf[r] - sq_pf[l]);
}

ld opt_val_for_seg(int l, int r) {
    if (r == l) return 0;
    return val_for_seg(l, r, opt_seg_x(l, r));
}

void rec(int l, int r, int lev, int ql, int qr) {
    if (l >= r) return;
    int m = (l + r) / 2;
    opt[lev][m] = 0, dp[lev][m] = opt_val_for_seg(0, m);
    for (int i = ql; i < qr && i <= m; ++i)
        if (ld cv = dp[lev - 1][i] + opt_val_for_seg(i, m); cv < dp[lev][m])
            opt[lev][m] = i, dp[lev][m] = cv;
    if (r - l > 1) {
        rec(l, m, lev, ql, opt[lev][m] + 1);
        rec(m + 1, r, lev, opt[lev][m], qr);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    cin >> n >> k;
    pf[0] = 0, sq_pf[0] = 0;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    sort(begin(arr), next(begin(arr), n));
    for (int i = 0; i < n; ++i) pf[i + 1] = pf[i] + arr[i], sq_pf[i + 1] = sq_pf[i] + 1ll * arr[i] * arr[i];
    dp[1][0] = opt[1][0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = opt_val_for_seg(0, i);
        opt[1][i] = 0;
    }
    // for (int i = 2; i <= k; ++i) {
    //     for (int j = 0; j <= n; ++j) {
    //         dp[i][j] = 1e25;
    //         for (int r = 0; r <= j; ++r) {
    //             auto ccv = dp[i - 1][r] + opt_val_for_seg(r, j);
    //             if (ccv < dp[i][j]) {
    //                 dp[i][j] = ccv;
    //                 opt[i][j] = r;
    //             }
    //         }
    //     }
    // }
    for (int i = 2; i <= k; ++i) {
        dp[i][0] = opt[i][0] = 0;
        rec(0, n + 1, i, 0, n + 1);
    }
    // for (int i = 0; i <= k; ++i) {
    //     for (int j = 0; j <= n; ++j) cout << opt[i][j] << " ";
    //     cout << "\n";
    // }
    cout << fixed << setprecision(15) << dp[k][n] << "\n";
    return 0;
}
