#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>

using namespace std;
using ll = long long;

inline ll ceil(ll a, ll b) {
    return (a + b - 1) / b;
}

constexpr int N = 1e7;
bool inpr[(N + 1) * 2];

void solve() {
    ll n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return;
    }
    for (ll i = 2; i <= n; ++i) {
        if (inpr[i]) continue;
        for (ll j = i * i; j <= n; j += i) inpr[i] = true;
        for (ll j = ceil(n * n, i) * i; j <= n * n + n; j += i) inpr[j - n * n + n + 1] = true;
    }
    int ans = 0;
    for (ll i = n + 1; i <= 2 * n; ++i) if (!inpr[i]) ++ans;
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
