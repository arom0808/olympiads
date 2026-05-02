#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <random>
#include <set>

using namespace std;
using ll = long long;

constexpr int maxm = 1e5 + 10;

ll n, m;

pair<ll, ll> flows[maxm];
ll pf[maxm];

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) cin >> flows[i].first >> flows[i].second;
    sort(flows, flows + m);
    for (int i = 0; i < m; ++i) pf[i + 1] = pf[i] + flows[i].first;
    ll ans = 0;
    for (int i = 0; i < m; ++i) {
        ll top_a_cnt = flows + m - upper_bound(flows, flows + m, make_pair(flows[i].second, 0ll));
        ll cnt = n;
        top_a_cnt = std::min(top_a_cnt, n);
        ll val = 0;
        if (i < m - top_a_cnt) {
            if (top_a_cnt == n) top_a_cnt = std::max(0ll, top_a_cnt - 1);
            val += flows[i].first;
            --cnt;
        }
        val += pf[m] - pf[m - top_a_cnt] + flows[i].second * (cnt - top_a_cnt);
        ans = max(ans, val);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
