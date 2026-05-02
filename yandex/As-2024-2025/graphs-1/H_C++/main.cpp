#include <iostream>
#include <deque>

using namespace std;
using ll = int64_t;

constexpr int maxa = 2e5, inf = 1e9;

ll dist[maxa];

ll ceil(ll a, ll b) {
    return (a + b - 1) / b;
}

void solve() {
    ll n, a, b, c;
    cin >> n >> a >> b >> c;
    if (b > a) swap(a, b);
    if (c > a) swap(a, c);
    for (ll i = 0; i < a; ++i) dist[i] = inf;
    dist[1] = 0;
    deque<ll> d;
    d.push_back(1);
    while (!d.empty()) {
        auto v = d.front();
        d.pop_front();
        for (ll i = 0, u = (v + b) % a, k = (v + b) >= a; i < 2; ++i, u = (v + c) % a, k = (v + c) >= a) {
            if (dist[u] <= dist[v] + k) continue;
            dist[u] = dist[v] + k;
            if (!k) d.push_front(u);
            else d.push_back(u);
        }
    }
    ll ans = 0;
    for (ll i = 0; i < a; ++i) {
        if (dist[i] == inf) continue;
        ll vv = n - (a * dist[i] - 1 + i);
        if (vv < 0) continue;
        ans += ceil(vv, a);
    }
    cout << ans << "\n";
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
