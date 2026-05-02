#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = int64_t;

constexpr ll maxa = 2e6 + 1, maxloga = 7;
constexpr ll inf = 2e18, pri = 1e9;

namespace ST {
    ll vals[maxloga][maxa];
    ll size;

    void init(ll _size) {
        size = _size;
        for (ll k = 0; (1ll << (3 * k)) <= size; ++k) for (ll i = 0; i < size; ++i) vals[k][i] = inf;
    }

    void add_val(ll pos, ll val) {
        vals[0][pos] = val;
        for (ll k = 1; pos + (1ll << (3 * k)) <= size; ++k)
            for (ll i = 0; pos + (i + 1) * (1ll << (3 * (k - 1))) <= size && i < 8; ++i)
                vals[k][pos] = std::min(vals[k][pos], vals[k - 1][pos + i * (1ll << (3 * (k - 1)))]);
    }

    ll min_val(ll a, ll b) {
        if (a >= b) return inf;
        ll k = 0;
        while ((1ll << (3 * (k + 1))) <= b - a) ++k;
        ll res = vals[k][a];
        for (ll pos = b - (1ll << (3 * k)); pos >= a; pos -= (1ll << (3 * k))) res = std::min(res, vals[k][pos]);
        return res;
    }
}

struct Exp {
    ll l, r, c;
};

ll dp[maxa];

void solve() {
    ll n, a;
    cin >> n >> a;
    ST::init(a + 1);
    vector<Exp> exps(n);
    for (auto &[l,r,c]: exps) cin >> l >> r >> c;
    for (ll i = a; i >= 0; --i) {
        for (auto [l,r,c]: exps) {
            if (i + r > a) continue;
            dp[i] = std::max(dp[i], ST::min_val(i + l, i + r + 1) - c - i * pri);
        }
        dp[i] += i * pri;
        ST::add_val(i, dp[i]);
    }
    cout << dp[0] << "\n";
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
