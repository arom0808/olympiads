#include <algorithm>
#include <iostream>

using namespace std;
using ll = int64_t;

constexpr int maxn = 1e5, maxp = 100;
constexpr ll inf = 1e18;
int n, m, p;
int ds[maxn];
pair<int, int> cats[maxn];
ll arr[maxn];
ll arr_pf[maxn + 1];

ll seg_cost(int l, int r) {
    return 1ll * (r - l + 1) * arr[r] - (arr_pf[r + 1] - arr_pf[l]);
}

ll dp[maxp + 1][maxn + 1];
int opt[maxp + 2][maxn + 2];

void rec_dp_solve(int level, int l, int r, int rl, int rr) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    dp[level][mid] = inf;
    for (int k = rl; k <= rr; ++k) {
        ll cval = seg_cost(k, mid - 1) + dp[level - 1][k];
        if (cval < dp[level][mid]) {
            dp[level][mid] = cval;
            opt[level][mid] = k;
        }
    }
    rec_dp_solve(level, l, mid, rl, opt[level][mid]);
    rec_dp_solve(level, mid + 1, r, opt[level][mid], rr);
}

void solve() {
    cin >> n >> m >> p;
    ds[0] = 0;
    for (int i = 1; i < n; ++i) cin >> ds[i], ds[i] += ds[i - 1];
    for (int i = 0; i < m; ++i) {
        cin >> cats[i].first >> cats[i].second, --cats[i].first;
        arr[i] = cats[i].second - ds[cats[i].first];
    }
    sort(arr, arr + m);
    arr_pf[0] = 0;
    for (int i = 0; i < m; ++i) arr_pf[i + 1] = arr_pf[i] + arr[i];
    for (int i = 0; i <= p; ++i) for (int j = 0; j <= m; ++j) dp[i][j] = inf, opt[i][j] = 0;
    for (int i = 0; i <= p; ++i) dp[i][0] = 0, opt[i][m + 1] = m;
    for (int i = 1; i <= p; ++i) rec_dp_solve(i, 0, m + 1, 0, m);
    cout << dp[p][m] << "\n";
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
