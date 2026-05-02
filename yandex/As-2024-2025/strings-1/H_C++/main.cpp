#include <iostream>

using namespace std;

constexpr int maxn = 2e5;
int n;
int a[maxn], b[maxn];
int ap[maxn], bp[maxn];
int ts[maxn * 3 + 1];
int z[maxn * 3 + 1];

void z_f() {
    int l = 0, r = 0;
    for (int i = 1; i < n * 3 + 1; ++i) {
        z[i] = std::max(std::min(z[i - l], r - i), 0);
        while (i + z[i] < n * 3 + 1 && ts[i + z[i]] == ts[z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) ap[i] = a[i] ^ (i + 1 == n ? a[0] : a[i + 1]);
    for (int i = 0; i < n; ++i) bp[i] = b[i] ^ (i + 1 == n ? b[0] : b[i + 1]);
    for (int i = 0; i < n; ++i) ts[i] = bp[i];
    ts[n] = (1 << 30) + 1;
    for (int i = 0; i < n; ++i) ts[n + 1 + i] = ap[i];
    for (int i = 0; i < n; ++i) ts[2 * n + 1 + i] = ap[i];
    z_f();
    for (int i = 0; i < n; ++i) if (z[n + 1 + i] >= n) cout << i << " " << (a[i] ^ b[0]) << "\n";
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
