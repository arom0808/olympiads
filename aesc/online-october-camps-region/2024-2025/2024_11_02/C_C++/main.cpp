#include <iostream>
#include <algorithm>

using namespace std;
using ll = int64_t;

constexpr int maxn = 1e5;

int arr[maxn];
ll pf[maxn + 1], fs = 0;
int n;

template<typename T>
inline T ceil(T a, T b) {
    return (a + b - 1) / b;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    pf[0] = 0;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    sort(begin(arr), next(begin(arr), n), [](int a, int b) { return a > b; });
    for (int i = 0; i < n; ++i) pf[i + 1] = pf[i] + arr[i], fs += arr[i];
    int bp = 1, bq = 1;
    ll br = 1e18;
    for (int q = 1; q <= n; ++q) {
        int l = 0, r = q;
        while (r - l != 1) {
            int m = (l + r) / 2;
            ll cs = 0;
            for (int sp = m; sp < n; sp += q * 2) cs += pf[std::min(n, sp + q)] - pf[sp];
            if (cs < ceil<ll>(fs, 2)) r = m;
            else l = m;
        }
        ll cs = 0;
        for (int sp = r; sp < n; sp += q * 2) cs += pf[std::min(n, sp + q)] - pf[sp];
        if (br > std::abs(fs - cs * 2)) bp = r, bq = q, br = std::abs(fs - cs * 2);
        if (r > 1) {
            ll cs = 0;
            for (int sp = r - 1; sp < n; sp += q * 2) cs += pf[std::min(n, sp + q)] - pf[sp];
            if (br > std::abs(fs - cs * 2)) bp = r - 1, bq = q, br = std::abs(fs - cs * 2);
        }
    }
    // for (int p = 1; p <= n; ++p) {
    // for (int q = p; q <= n; ++q) {
    // ll cs = 0;
    // for (int sp = p; sp < n; sp += q * 2)
    // cs += pf[std::min(n, sp + q)] - pf[sp];
    // if (br > std::abs(fs - cs * 2)) bp = p, bq = q, br = std::abs(fs - cs * 2);
    // }
    // }
    cout << bp << " " << bq << "\n";
    return 0;
}
