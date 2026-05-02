#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>

using namespace std;

constexpr int maxn = 1e8;

int bin_pow(int a, int p, int m) {
    int res = 1;
    while (p) {
        if (p & 1) res = 1ll * res * a % m;
        a = 1ll * a * a % m;
        p >>= 1;
    }
    return res;
}

int inv(int v, int m) {
    return bin_pow(v, m - 2, m);
}

int inv_facts[maxn + 1];

void solve() {
    int p;
    cin >> p;
    if (p == 1) {
        cout << "0\n";
        return;
    }
    int cfact = p - 1;
    inv_facts[p - 1] = inv(cfact, p);
    for (int i = p - 2; i >= 0; --i) inv_facts[i] = 1ll * inv_facts[i + 1] * (i + 1) % p;
    int cs = 0;
    cfact = 1;
    for (int i = 1; i < p; ++i) {
        cs = (cs + 1ll * inv_facts[i] * cfact % p) % p;
        cfact = 1ll * cfact * i % p;
        if (i % 100 == 0 || i + 1 == p) cout << cs << " ", cs = 0;
    }
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
