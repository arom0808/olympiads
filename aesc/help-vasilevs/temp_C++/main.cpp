#include <iostream>

using namespace std;
using ll = long long;

constexpr ll maxt = 1e8, mod = 1e9 + 7;

ll t[maxt];
ll a, b, c, d;

ll bin_pow(ll x, ll p) {
    ll res = 1;
    while (p) {
        if (p & 1) res = res * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return bin_pow(x, mod - 2);
}

ll C(ll n, ll k) {
    return t[n] * inv(t[k]) % mod * inv(t[n - k]) % mod;
}

int main() {
    t[0] = t[1] = 1;
    for (ll i = 2; i < maxt; ++i) t[i] = t[i - 1] * i % mod;
    cin >> a >> b >> c >> d;
    ll ans = 0;
    for (ll x = c, y = b - d - 1; x < a && y >= 0; ++x, --y) {
        ans = (ans + C(x + y, y) * C(b - y + a - x - 2, a - x - 1) % mod) % mod;
    }
    cout << ans << "\n";
    return 0;
}

// 8 8 4 4
// 1716
//
// 132 102 131 50
// 567011456
//
// 1444 9696 1185 4567
// 132493463

// 102088 365556 1001 3003
// 352424287

// 1234567 7654321 23654 1111222
// 305090907
