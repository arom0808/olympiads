#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

vector<ll> fvs;

ll ans = 1e9;

void rec_sol(ll cv, ll pos, ll clen) {
    if (pos == -1) {
        if (cv == 0) ans = std::min(ans, clen);
        return;
    }
    rec_sol(cv, pos - 1, clen);
    rec_sol(cv + fvs[pos], pos - 1, clen + 1);
    rec_sol(cv - fvs[pos], pos - 1, clen + 1);
}

void test_solve() {
    ans = 1e9;
    ll n;
    cin >> n;
    auto i = upper_bound(fvs.begin(), fvs.end(), n) - fvs.begin();
    rec_sol(n, std::min<ll>(i + 2, fvs.size() - 1), 0);
    cout << ans << "\n";
}

void solve() {
    fvs.emplace_back(1);
    fvs.emplace_back(2);
    while (true) {
        ll nf = fvs[fvs.size() - 2] + fvs.back();
        fvs.emplace_back(nf);
        if (nf > 4e17) break;
    }
    ll t;
    cin >> t;
    while (t--) test_solve();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
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