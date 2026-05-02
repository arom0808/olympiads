#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

constexpr int maxn = 310;

int t, n, k1, k2;

int best_res = 1e9;

bool table[maxn][maxn];
int white_pf[maxn][maxn];
vector<int> best_cols, cur_cols;
mt19937 rng(13234);

void rec_sol(int col, int white_cnt, int last_col, int now_res) {
    if (best_res <= k1 || now_res >= best_res) return;
    if (col == n) {
        if (white_cnt != n * n / 2) return;
        best_res = now_res, best_cols = cur_cols;
        return;
    }
    int r = std::min(n, (n * n / 2 - white_cnt) / (n - col));
    int l = std::max(last_col, n * n / 2 - white_cnt - (n - col - 1) * n);
    for (int v = l; v <= r; ++v) {
        cur_cols[col] = v;
        rec_sol(col + 1, white_cnt + v, v, now_res + v - white_pf[col][v]);
    }
}

void solve() {
    // cout <<
    // "0000000011\n0000000111\n0000000111\n0000000111\n0000000111\n0000000111\n0000000111\n1111111111\n1111111111\n1111111111";
    cin >> t >> n >> k1 >> k2;
    cur_cols.resize(n);
    best_cols.resize(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> table[i][j];
    for (int col = 0; col < n; ++col)
        for (int i = 0; i < n; ++i)
            white_pf[col][i + 1] = white_pf[col][i] + table[n - 1 - i][col];
    for (int i = 0; i < n; ++i) best_cols[i] = n / 2;
    if (t == 1) {
        rec_sol(0, 0, 0, 0);
    } else if (t == 2) {
        int cwc = 0;
        int i = 0;
        for (; i * 3 < n; ++i)
            best_cols[i] = n / 4, cwc += best_cols[i];
        for (; i * 3 < n * 2; ++i)
            best_cols[i] = n / 2, cwc += best_cols[i];
        int cc = (n * n / 2 - cwc) / (n / 3);
        for (; i + 1 < n; ++i)
            best_cols[i] = cc, cwc + best_cols[i];
        best_cols[n - 1] = n * n / 2 - cwc;
    }
    // rec_sol(0, 0, 0, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (n - i - 1 < best_cols[j]) cout << "1 ";
            else cout << "0 ";
        }
        cout << "\n";
    }
    // cout << best_res << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
