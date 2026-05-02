#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

namespace DD {
    vector<ll> vals;

    void insert(int before, ll val) {
        vals.insert(vals.begin() + before, val);
    }

    void set_val(int from, int to, ll val) {
        for (int i = from; i < to; ++i) vals[i] = val;
    }

    void set_progr(int from, int to, ll x) {
        ll mx = x;
        for (int i = from; i < to; ++i) vals[i] += mx, mx += x;
    }

    ll sum(int from, int to) {
        ll res = 0;
        for (int i = from; i < to; ++i) res += vals[i];
        return res;
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0, val; i < n; ++i) {
        cin >> val;
        DD::insert(i, val);
    }
    int t, a, b, c, x;
    for (int i = 0; i < q; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b >> x;
            DD::set_val(a - 1, b, x);
        } else if (t == 2) {
            cin >> a >> b >> x;
            DD::set_progr(a - 1, b, x);
        } else if (t == 3) {
            cin >> c >> x;
            DD::insert(c - 1, x);
        } else {
            cin >> a >> b;
            cout << DD::sum(a - 1, b) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
