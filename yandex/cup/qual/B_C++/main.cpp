#include <iostream>

using namespace std;

using ll = long long;
const ll maxn = 2e5, inf = 1e9 + 10;
ll hs[maxn], up_cnt[maxn], down_cnt[maxn];

void sol() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> hs[i], up_cnt[i] = down_cnt[i] = 0;
    for (int i = 1; i < n; ++i) if (hs[i - 1] < hs[i]) up_cnt[i] = up_cnt[i - 1] + 1;
    for (int i = n - 2; i >= 0; --i) if (hs[i] > hs[i + 1]) down_cnt[i] = down_cnt[i + 1] + 1;
    ll ans = 0;
    for (int i = 0; i < n; ++i) ans += 1ll * up_cnt[i] * down_cnt[i];
    cout << ans << "\n";
    // cout << ans << "\n";
}

