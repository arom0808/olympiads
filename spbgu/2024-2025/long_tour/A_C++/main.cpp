#pragma GCC optimize("Ofast")

#include <iostream>

using namespace std;

using ll = long long;

void make_step(ll &a, ll &b) {
    if (b != a) a += (b - a) * 2;
}

void make_steps(ll &a, ll &b, ll &c, ll &i, ll t) {
    if (a == b) i = t;
    else if (c - b > (b - a) * 2 && t - i > 2) {
        ll st_cnt = std::min((t - i) / 2, (c - b - 1) / ((b - a) * 2));
        ll dd = b - a;
        a += st_cnt * 2 * dd;
        b += st_cnt * 2 * dd;
        i += st_cnt * 2;
    } else {
        make_step(a, b);
        ++i;
    }
}

void solve() {
    ll a, b, c, t;
    cin >> a >> b >> c >> t;
    for (ll i = 0; i < t;) {
        if (a <= b && a <= c) {
            if (b <= c) make_steps(a, b, c, i, t);
            else make_steps(a, c, b, i, t);
        } else if (b <= a && b <= c) {
            if (a <= c) make_steps(b, a, c, i, t);
            else make_steps(b, c, a, i, t);
        } else {
            if (a <= b) make_steps(c, a, b, i, t);
            else make_steps(c, b, a, i, t);
        }
    }
    cout << a << " " << b << " " << c << "\n";
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
