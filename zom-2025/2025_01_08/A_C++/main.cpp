#include <iostream>

using namespace std;
using ll = long long;

constexpr ll inf = 1e18;

ll a, b;

pair<ll, ll> check_x(ll x) {
    ll t = a % x;
    // ll y = x * 2;
    // while (true) {
    //     if (b % y == t) return {x, y};
    //     if (y > b) return {inf, inf};
    //     y += x;
    // }
    ll r = b - t;
    if (r % x != 0) return {inf, inf};
    r /= x;
    ll ans = inf;
    for (ll k = 2; k * k <= r; ++k) {
        if (r % k != 0) continue;
        if (b / (k * x) * k == r) ans = std::min(ans, k);
        if (b / (r / k * x) * (r / k) == r) ans = std::min(ans, r / k);
    }
    if (r > 1 && b / (r * x) * r == r) ans = std::min(ans, r);
    if (ans == inf) return {inf, inf};
    return {x, ans * x};
}

void solve() {
    cin >> a >> b;
    if (b == 1) {
        cout << "2 4\n";
        return;
    }
    pair<ll, ll> ans{inf, inf};
    ll bda = b - a;
    if (bda == 0) {
        ans = {a + 1, (a + 1) * 2};
        for (ll x = 2; x <= a + 10; ++x) {
            ans = std::min(ans, check_x(x));
            if (ans.first != inf) break;
        }
        if (ans.first == inf) cout << "-1 -1\n";
        else cout << ans.first << " " << ans.second << "\n";
        return;
    }
    for (ll i = 2; i * i <= bda; ++i) {
        if (bda % i == 0) {
            ans = std::min(ans, check_x(i));
            ans = std::min(ans, check_x(bda / i));
        }
    }
    if (bda != 1) ans = std::min(ans, check_x(bda));
    for (ll x = std::max<ll>(b - 10, 2); x <= b + 10; ++x) {
        ans = std::min(ans, check_x(x));
    }
    if (ans.first == inf) cout << "-1 -1\n";
    else cout << ans.first << " " << ans.second << "\n";
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
