#include <iostream>

using namespace std;
using ll = int64_t;

constexpr int maxn = 2e5, maxk = 21;
constexpr ll inf = 1e18;
int n, k;
int arr[maxn];
ll dp[maxk][maxn];
int opt[maxk][maxn];

struct SMS {
    int l = 0, r = 0;
    ll cans = 0;
    int cnts[maxn + 1];

    static ll ans_by_cnt(int cnt) {
        if (cnt < 2) return 0;
        return 1ll * cnt * (cnt - 1) / 2;
    }

    void shift_to(int nl, int nr) {
        while (l > nl) --l, cans -= ans_by_cnt(cnts[arr[l]]), cans += ans_by_cnt(++cnts[arr[l]]);
        while (r < nr) cans -= ans_by_cnt(cnts[arr[r]]), cans += ans_by_cnt(++cnts[arr[r]]), ++r;
        while (l < nl) cans -= ans_by_cnt(cnts[arr[l]]), cans += ans_by_cnt(--cnts[arr[l]]), ++l;
        while (r > nr) --r, cans -= ans_by_cnt(cnts[arr[r]]), cans += ans_by_cnt(--cnts[arr[r]]);
    }
};

void rec_sol(int l, int r, int ql, int qr, int level, SMS &sms) {
    if (l >= r) return;
    int m = (l + r) / 2;
    for (int k = std::max(level - 1, ql); k < m && k <= qr; ++k) {
        sms.shift_to(k, m);
        if (ll cv = dp[level - 1][k] + sms.cans; cv < dp[level][m])
            dp[level][m] = cv, opt[level][m] = k;
    }
    rec_sol(l, m, ql, opt[level][m], level, sms);
    rec_sol(m + 1, r, opt[level][m], qr, level, sms);
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    for (int i = 0; i <= k; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = inf;
    dp[0][0] = 0;
    SMS sms;
    for (int i = 1; i <= k; ++i) rec_sol(1, n + 1, i - 1, n - 1, i, sms);
    cout << dp[k][n];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w",stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
