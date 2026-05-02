#include <iostream>
#include <algorithm>

using namespace std;

using ll = int64_t;

constexpr int maxn = 1e5;

ll x1, y1, x2, y2, n, m;
ll mr1, mr2;
ll r1s[maxn], r2s[maxn];
// pair<ll, ll> ars[maxn];

bool casaet(ll d1, ll d2) {
    return (d1 + d2) * (d1 + d2) >= (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

bool two_cross(ll d1, ll d2) {
    return (d1 + d2) * (d1 + d2) > (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

ll lower_bound_of(ll dist) {
    ll l = 0, r = n;
    while (r - l != 1) {
        auto mid = (l + r) / 2;
        if (two_cross(r1s[mid], dist)) r = mid;
        else l = mid;
    }
    return l;
}

ll upper_bound_of(ll dist) {
    ll l = -1, r = n - 1;
    while (r - l != 1) {
        auto mid = (l + r) / 2;
        if (casaet(r1s[mid], dist)) r = mid;
        else l = mid;
    }
    return r;
}

void solve() {
    cin >> x1 >> y1 >> n;
    mr1 = mr2 = 0;
    for (ll i = 0; i < n; i++) cin >> r1s[i], mr1 = std::max<ll>(mr1, r1s[i]);
    cin >> x2 >> y2 >> m;
    for (ll i = 0; i < m; i++) cin >> r2s[i], mr2 = std::max<ll>(mr2, r2s[i]);
    ll sqd = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    if (sqd >= (mr1 + mr2) * (mr1 + mr2)) {
        cout << n + m << "\n";
        return;
    }
    if (mr1 < mr2) swap(x1, x2), swap(y1, y2), swap(mr1, mr2), swap(r1s, r2s), swap(n, m);
    auto fp = lower_bound_of(mr2), sp = upper_bound_of(mr2);
    if (casaet(r1s[fp], mr2) && casaet(r1s[sp], mr2)) cout << n + m + 1 << "\n";
    else cout << n + m << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
