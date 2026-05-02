#include <iostream>

using namespace std;
using ll = long long;

constexpr int maxn = 1510;

bool table[maxn][maxn];
int pf[maxn][maxn];
int n, m, k;
ll ans = 0;

int rect_sum(int i0, int j0, int i1, int j1) {
    return pf[i1][j1] - pf[i0][j1] - pf[i1][j0] + pf[i0][j0];
}

void solve() {
    cin >> n >> m >> k;
    char c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> c;
            table[i][j] = c == '1';
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            pf[i + 1][j + 1] = pf[i][j + 1] + pf[i + 1][j] - pf[i][j] + table[i][j];
    for (int i0 = 0; i0 < n; ++i0) {
        for (int j0 = 0; j0 < m; ++j0) {
            for (int i1 = i0 + 1; i1 <= n; ++i1) {
                for (int j1 = j0 + 1; j1 <= m; ++j1) {
                    if (rect_sum(i0, j0, i1, j1) == k) ++ans;
                }
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
