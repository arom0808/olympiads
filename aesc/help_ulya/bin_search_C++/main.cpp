#include <iostream>

using namespace std;
using ll = long long;

int main() {
    ll n, k;
    cin >> n >> k;
    ll l = -1, r = 1e10;
    while (r - l != 1) {
        ll m = (l + r) / 2;
        if ((k + m) * 3 >= n + m) r = m;
        else l = m;
    }
    cout << r << "\n";
    return 0;
}
