#include <iostream>

using namespace std;

constexpr int maxn = 2e5, pmaxn = 300;
using ll = long long;


int nums[maxn];
int n, k;
ll dp[pmaxn + 1][pmaxn + 1];

void solve1() {
    for (int i = 1; i < n; ++i) {
        for (int cnt = 2; cnt <= i + 1 && cnt <= k; ++cnt) {
            for (int pre_i = i - 1; pre_i >= 0 && pre_i >= cnt - 2; --pre_i) {
                dp[i][cnt] = std::max(dp[i][cnt], dp[pre_i][cnt - 1] + (nums[pre_i] ^ nums[i]));
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i) ans = std::max(ans, dp[i][k]);
    cout << ans << "\n";
}

void solve2() {
    ll ans = 0;
    for (int i = 0; i + 1 < n; ++i) ans += nums[i] ^ nums[i + 1];
    cout << ans << "\n";
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    if (n <= 300) solve1();
    else solve2();
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
