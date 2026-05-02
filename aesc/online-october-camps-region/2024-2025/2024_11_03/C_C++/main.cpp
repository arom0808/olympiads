#include <iostream>

using namespace std;

using ll = int64_t;

constexpr int maxn = 5001;
constexpr ll inf = 1e18;

ll dp[maxn][maxn];
int sposs[maxn];
int n, scnt;
string temp_s;
int mta[maxn];
ll mtpfs[maxn];

ll move_time(int from, int to) {
    if (from > to) swap(from, to);
    return mtpfs[to] - mtpfs[from];
}

void solve() {
    cin >> n;
    cin >> temp_s;
    scnt = 0;
    for (int i = 0; i < n; ++i) if (temp_s[i] == 'A') sposs[scnt++] = i;
    mtpfs[0] = 0;
    for (int i = 0; i + 1 < n; ++i) cin >> mta[i], mtpfs[i + 1] = mtpfs[i] + mta[i];
    for (int i = 0; i <= scnt; ++i) for (int j = 0; j <= n; ++j) dp[i][j] = inf;
    for (int i = 1; i <= n; ++i)
        dp[1][i] = std::min(dp[1][i - 1], move_time(sposs[0], i - 1));
    for (int i = 2; i <= scnt; ++i) {
        for (int j = 2 * i - 1; j <= n; ++j) {
            dp[i][j] = std::min(dp[i][j - 1], dp[i - 1][j - 2] + move_time(sposs[i - 1], j - 1));
        }
    }
    ll ans = inf;
    for (int j = 2 * scnt - 1; j <= n; ++j) ans = std::min(ans, dp[scnt][j]);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
