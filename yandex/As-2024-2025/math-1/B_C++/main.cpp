#include <iostream>

using namespace std;
using ll = long long;

struct GK {
    ll ka, kb, gcv;
};

GK _gcd(ll a, ll b) {
    if (!b) return {1, 0, a};
    auto [ka,kb,gcv] = _gcd(b, a % b);
    return {kb, ka - a / b * kb, gcv};
}

GK gcd(ll a, ll b) {
    bool swapped = a < b;
    if (swapped) swap(a, b);
    auto res = _gcd(a, b);
    if (swapped) swap(res.ka, res.kb);
    return res;
}

ll ceil(ll a, ll b) {
    if (b < 0) a = -a, b = -b;
    if (a < 0) return a / b;
    return (a + b - 1) / b;
}

ll floor(ll a, ll b) {
    if (b < 0) a = -a, b = -b;
    if (a < 0) return -ceil(-a, b);
    return a / b;
}

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    bool ra = a < 0, rb = b < 0;
    if (ra) a = -a;
    if (rb) b = -b;
    if (c < 0) ra = !ra, rb = !rb, c = -c;
    auto [x0,y0,gcv] = gcd(a, b);
    if (c % gcv != 0) {
        cout << "Impossible\n";
        return;
    }
    x0 *= c / gcv, y0 *= c / gcv;
    ll k = ra ? ceil(x0, b / gcv) : floor(x0, b / gcv);
    ll x = x0 - k * (b / gcv), y = k * (a / gcv) + y0;
    if (ra) x = -x;
    if (rb) y = -y;
    cout << x << " " << y << "\n";
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
