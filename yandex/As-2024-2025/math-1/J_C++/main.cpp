#include <iostream>

using namespace std;
using ll = long long;

struct GCDAns {
    ll k1, k2, gcd_val;
};

GCDAns _my_gcd(ll a, ll b) {
    if (!b) return {1, 0, a};
    auto [k1,k2,gcd_val] = _my_gcd(b, a % b);
    return {k2, k1 - k2 * (a / b), gcd_val};
}

GCDAns my_gcd(ll a, ll b) {
    bool swapped = false;
    if (a < b) swap(a, b), swapped = true;
    GCDAns res = _my_gcd(a, b);
    if (swapped) swap(res.k1, res.k2);
    return res;
}

void solve() {
    ll a, b, n, m;
    cin >> a >> b >> n >> m;
    if (b < a) swap(a, b), swap(n, m);
    auto [k1,k2,gcd_val] = my_gcd(n, m);
    if ((b - a) % gcd_val) {
        cout << "NO\n";
        return;
    }
    k1 *= (b - a) / gcd_val, k2 *= -(b - a) / gcd_val;
    ll p = n * m / gcd_val;
    ll x0 = ((a + k1 * n) % p + p) % p;
    cout << "YES " << x0 << " " << p << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
