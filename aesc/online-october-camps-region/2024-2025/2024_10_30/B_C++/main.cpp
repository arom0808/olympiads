#include <iostream>

using namespace std;
using ll = int64_t;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    ll n, x;
    cin >> n >> x;
    if ((n - 1) * (n - 2) / 2 < x) {
        cout << "-1\n";
        return 0;
    }
    ll kl = 0, kr = n - 2;
    while (kr - kl != 1) {
        ll km = (kl + kr) / 2;
        if (km * (km + 1) / 2 < x) kl = km;
        else kr = km;
    }
    ll k = kr;
    ll dl = k * (k + 1) / 2 - x;
    ll lp = n - 1 - dl;
    for (ll i = 0; i < n; ++i) {
        if (i < n - k - 1) {
            cout << n - i << " ";
        } else {
            if (i < lp) cout << i - n + k + 2 << " ";
            else if (i == lp) cout << k + 1 << " ";
            else cout << i - n + k + 1 << " ";
        }
    }
    cout << "\n";
    return 0;
}
