#include <iostream>

using namespace std;

using ll = int64_t;

constexpr ll mod = 1e9 + 7;
constexpr int maxn = 350;
int n;
ll dpgood[maxn + 1][maxn + 1], dpbad[maxn + 1][maxn + 1], cnk[maxn + 1][maxn + 1];
ll mult_cnts[maxn + 1][maxn + 1];
ll temp_mult_cnts[maxn + 1];

ll binpow(ll a, ll p) {
    ll res = 1;
    while (p) {
        if (p & 1) res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}

void init_mult_cnts() {
    for (int i = 0; i < maxn; ++i) for (int j = 0; j < maxn; ++j) mult_cnts[i][j] = 0;
    for (int _num = 2; _num <= maxn; ++_num) {
        int num = _num, dd = 2;
        while (dd * dd <= num) {
            if (num % dd == 0) {
                num /= dd;
                ++mult_cnts[_num][dd];
            } else ++dd;
        }
        if (num != 1) ++mult_cnts[_num][num];
    }
    for (int i = 1; i <= maxn; ++i) for (int j = 0; j <= maxn; ++j) mult_cnts[i][j] += mult_cnts[i - 1][j];
}

void temp_del_cnts(int n, int k) {
    for (int i = 0; i <= maxn; ++i) temp_mult_cnts[i] = mult_cnts[n][i] - mult_cnts[k][i] - mult_cnts[n - k][i];
}

void calc_cnk(int n, int k) {
    if (k > n) {
        cnk[n][k] = 0;
        return;
    }
    temp_del_cnts(n, k);
    cnk[n][k] = 1;
    for (int i = 0; i <= maxn; ++i) cnk[n][k] = cnk[n][k] * binpow(i, temp_mult_cnts[i]) % mod;
}

void cnk_init() {
    for (int n = 0; n <= maxn; ++n) for (int k = 0; k <= maxn; ++k) calc_cnk(n, k);
}

void solve() {
    cin >> n;
    init_mult_cnts();
    cnk_init();
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) dpgood[i][j] = dpbad[i][j] = 0;
    for (int i = 0; i <= n; ++i) dpgood[1][i] = (i == 1) ? n : 0, dpbad[1][i] = (i != 1) ? cnk[n][i] : 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= j; ++k) {
                if (k != i) {
                    dpbad[i][j] += cnk[n - (j - k)][k] * dpbad[i - 1][j - k] % mod;
                    dpbad[i][j] %= mod;
                } else {
                    dpgood[i][j] += cnk[n - (j - i)][i] * dpbad[i - 1][j - i] % mod;
                    dpgood[i][j] %= mod;
                }
                dpgood[i][j] += cnk[n - (j - k)][k] * dpgood[i - 1][j - k] % mod;
                dpgood[i][j] %= mod;
            }
        }
    }
    cout << dpgood[n][n] << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
