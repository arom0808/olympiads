#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

vector<ll> fibs;

void init_fibs() {
    fibs.push_back(1), fibs.push_back(2);
    while (fibs.back() <= 4e17) fibs.push_back(fibs[fibs.size() - 2] + fibs[fibs.size() - 1]);
}

void solve() {
    ll n;
    cin >> n;
    ll ans = 0;
    while (n) {
        auto p1 = lower_bound(fibs.begin(), fibs.end(), n);
        ll f1 = *p1, f2 = *(p1 != fibs.begin() ? prev(p1) : p1);
        n = std::min(std::abs(f1 - n), std::abs(f2 - n));
        ++ans;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    init_fibs();
    cin >> t;
    while (t--) solve();
    return 0;
}
