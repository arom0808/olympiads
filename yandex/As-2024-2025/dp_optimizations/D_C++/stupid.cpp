#include <iostream>

using namespace std;
using ll = int64_t;

constexpr int maxn = 1e5+1, maxk = 21;
constexpr ll inf = 1e18;
int n, k;
int arr[maxn];
ll dp[maxk][maxn];
int opt[maxk][maxn];

ll calc_seg(int l, int r) {
    ll res = 0;
    for (int i = l; i < r; ++i)
        for (int j = i + 1; j < r; ++j)
            if (arr[i] == arr[j])
                ++res;
    return res;
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    for (int i = 0; i <= k; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = inf;
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, k); ++j) {
            for (int k = i - 1; k >= j - 1; --k) {
                ll cv = dp[j - 1][k] + calc_seg(k, i);
                if (cv < dp[j][i]) {
                    dp[j][i] = cv;
                    opt[j][i] = k;
                }
            }
        }
    }
    cout << dp[k][n];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    solve();
//#ifdef LOCAL
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w",stdout);
//    int t;
//    cin >> t;
//    while (t--) solve();
//#else
//    solve();
//#endif
    return 0;
}