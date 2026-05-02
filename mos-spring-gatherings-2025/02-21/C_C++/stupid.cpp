#include <iostream>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

constexpr ll INF = 1e9;

void solve() {
    ll n, d, t;
    cin >> n >> d >> t;
    d = min(d, n - 1);
    ++d;
    vector<ll> a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<ll>> cost(n + 1, vector<ll>(n + 1));
    for (ll l = 0; l < n; ++l) {
        ll last_t = INF;
        ll cur_cost = 0;
        for (ll r = l + 1; r <= n; ++r) {
            ll cur_t = min(a[r - 1], last_t + 1);
            if (cur_t <= t) {
                ++cur_cost;
            }
            last_t = cur_t;
            cost[l][r] = cur_cost;
        }
    }
    vector<vector<ll>> dp(d + 1, vector<ll>(n + 1, INF));
    for (ll i = 0; i <= n; ++i) {
        dp[1][i] = cost[0][i];
    }
    for (ll i = 2; i <= d; ++i) {
        for (ll j = 1; j <= n; ++j) {
            for (ll k = j - 1; k >= 0; --k) {
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + cost[k][j]);
            }
        }
    }
    ll ans = dp[d][n];
    cout << ans<<"\n";
}



int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
