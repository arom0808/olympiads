#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

constexpr int maxn = 200;

// int dp[maxn], ps[maxn];
// int tarr[maxn];
// int timer = 0;

// void dp_init() {
//     dp[1] = 0;
//     for (int l = 2; l <= 5000; ++l) {
//         ++timer;
//         for (int i = (l + 1) >> 1; i < l; ++i) {
//             if (dp[i] < maxn) tarr[dp[i]] = timer;
//             if (!dp[i] && !ps[l]) ps[l] = i;
//         }
//         int mv = 0;
//         for (; mv < maxn; ++mv) if (tarr[mv] != timer) break;
//         dp[l] = mv;
//     }
// }

struct QueEl {
    int a, b, c;
};

bool dp[maxn][maxn][maxn];
QueEl to[maxn][maxn][maxn];

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            for (int k = 1; k <= c; ++k) {
                if (i == j && j == k && k == 1) continue;
                for (int ni = (i + 1) >> 1; ni < i && !dp[i][j][k]; ++ni) {
                    if (!dp[ni][j][k]) {
                        dp[i][j][k] = true;
                        to[i][j][k] = {ni, j, k};
                    }
                }
                for (int nj = (j + 1) >> 1; nj < j && !dp[i][j][k]; ++nj) {
                    if (!dp[i][nj][k]) {
                        dp[i][j][k] = true;
                        to[i][j][k] = {i, nj, k};
                    }
                }
                for (int nk = (k + 1) >> 1; nk < k && !dp[i][j][k]; ++nk) {
                    if (!dp[i][j][nk]) {
                        dp[i][j][k] = true;
                        to[i][j][k] = {i, j, nk};
                    }
                }
            }
        }
    }
    if (dp[a][b][c]) {
        cout << "YES\n";
        auto [na,nb,nc] = to[a][b][c];
        cout << na << " " << nb << " " << nc << "\n";
    } else cout << "NO\n";
    // if (dp[a] ^ dp[b] ^ dp[c]) {
    //     cout << "YES\n";
    //     if (!dp[a] && !dp[b] && !dp[c]) throw std::bad_alloc();
    //     if (dp[a]) cout << ps[a] << " " << b << " " << c << "\n";
    //     else if (dp[b]) cout << a << " " << ps[b] << " " << c << "\n";
    //     else if (dp[c]) cout << a << " " << b << " " << ps[c] << "\n";
    // } else {
    //     cout << "NO\n";
    // }
}

int main() {
    // dp_init();
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    cin >> t;
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    while (t--) solve();
    return 0;
}
