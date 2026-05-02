#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr ll maxn = 1030, maxm = 2050;

ll m;
ll pf[maxm][maxm];
ll dp[maxm][maxm];
ll tr[maxm][maxm];
vector<ll> xs, ys;

int zip(ll val, const vector<ll> &vec) {
    return lower_bound(vec.begin(), vec.end(), val) - vec.begin();
}

bool try_k(ll k) {
    dp[0][ys.size() - 1] = pf[0][ys.size()] - k * (m + 1);
    if (dp[0][ys.size() - 1] < 0)
        return false;
    for (ll i = ys.size() - 2; i >= 0; --i) {
        dp[0][i] = std::min(pf[0][i + 1] - k * (ys[i] + 1), dp[0][i + 1]);
        if (dp[0][i] < 0)
            return false;
    }
    for (ll i = 1; i < xs.size(); ++i) {
        dp[i][ys.size() - 1] = pf[i][ys.size()] + dp[i - 1][ys.size() - 1] - k * (m - xs[i] + 1);
        if (dp[i][ys.size() - 1] < 0)
            return false;
        for (ll j = ys.size() - 2; j >= 0; --j) {
            dp[i][j] = std::min(pf[i][j + 1] + dp[i - 1][j] - k * (ys[j] - xs[i] + 1), dp[i][j + 1]);
            if (dp[i][j] < 0)
                return false;
        }
    }
    return true;
}

struct InpS {
    ll x, y, s;

    friend istream &operator>>(istream &is, InpS &st) {
        is >> st.x >> st.y >> st.s;
        if (st.x > st.y) swap(st.x, st.y);
        return is;
    }
};

void solve() {
    ll v;
    cin >> m >> v;
    ll S = 0;
    vector<InpS> inps(v);
    for (auto &inp: inps) cin >> inp;
    for (auto [x,y,s]: inps) xs.push_back(x);
    for (auto [x,y,s]: inps) if (x) xs.push_back(x - 1);
    for (auto [x,y,s]: inps) ys.push_back(y);
    for (auto [x,y,s]: inps) if (y) ys.push_back(y - 1);
    xs.push_back(0), ys.push_back(0);
    xs.push_back(m), ys.push_back(m);
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (auto &[x,y,s]: inps) x = zip(x, xs), y = zip(y, ys);
    for (auto [x,y,s]: inps) {
        tr[x][y] += s;
        S += s;
    }
    for (ll i = 0; i < xs.size(); ++i) for (ll j = 0; j < ys.size(); ++j) pf[i][j + 1] = pf[i][j] + tr[i][j];
    ll l = 0, r = S / ((m + 1) * (m + 2) / 2) + 1;
    while (r - l != 1) {
        ll k = (l + r) / 2;
        if (try_k(k)) l = k;
        else r = k;
    }
    cout << l << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
