#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 300;
int arr[maxn];

namespace Stupid {
    int n, m, k;
    int transformed_arr[maxn];
    vector<int> transformed;
    int best_res = 0;

    void make_transformed_arr() {
        int next_tr = 0;
        for (int i = 0; i < n; ++i) {
            if (next_tr < transformed.size() && transformed[next_tr] == i) {
                transformed_arr[next_tr++] = arr[i];
            } else {
                transformed_arr[transformed.size() + i - next_tr] = arr[i];
            }
        }
    }

    // void rec_sol(int level) {
    //     if (level == n) {
    //         make_transformed_arr();
    //         int res = 0;
    //         for (int i = 0; i < n; ++i) if ((n - i) % k == 0) res += transformed_arr[i];
    //         best_res = std::max(best_res, res);
    //         return;
    //     }
    //     rec_sol(level + 1);
    //     if (transformed.size() + 1 <= m) {
    //         transformed.push_back(level);
    //         rec_sol(level + 1);
    //         transformed.pop_back();
    //     }
    // }

    void solve() {
        cin >> n >> m >> k;
        best_res = 0;
        for (int i = 0; i < n; ++i) cin >> arr[i];
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (__builtin_popcount(mask) > m) continue;
            transformed.clear();
            for (int i = 0; i < n; ++i) if ((mask >> i) & 1) transformed.push_back(i);
            make_transformed_arr();
            int res = 0;
            for (int i = n - 1; i >= 0; --i) if ((n - i) % k == 0) res += transformed_arr[i];
            best_res = std::max(best_res, res);
        }
        // rec_sol(0);
        int fsum = 0;
        for (int i = 0; i < n; ++i) fsum += arr[i];
        cout << fsum - best_res << "\n";
    }
}

// int now_dp[maxn + 1][maxn + 1], prev_dp[maxn + 1][maxn + 1];

void solve() {
    Stupid::solve();
    // int n, m, k;
    // cin >> n >> m >> k;
    // for (int i = 0; i < n; ++i) cin >> arr[i];
    // for (int len = 1; len <= n; ++len) {
    //     for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) now_dp[i][j] = 0;
    //     for (int in_cnt = 0; in_cnt <= len; ++in_cnt) {
    //         for (int out_cnt = 0; out_cnt <= n - len; ++out_cnt) {
    //             if (in_cnt < len)
    //                 now_dp[in_cnt][out_cnt] =
    //                         std::max(now_dp[in_cnt][out_cnt],
    //                                  prev_dp[in_cnt][out_cnt] + (((len - in_cnt) % k == 0) ? arr[n - len] : 0));
    //             if (in_cnt > 0)
    //                 now_dp[in_cnt][out_cnt] =
    //                         std::max(now_dp[in_cnt][out_cnt],
    //                                  prev_dp[in_cnt - 1][out_cnt + 1] + ((n - out_cnt) % k == 0 ? arr[n - len] : 0));
    //         }
    //     }
    //     swap(now_dp, prev_dp);
    // }
    // int best_res = 0;
    // for (int in_cnt = 0; in_cnt <= std::min(n, m); ++in_cnt) best_res = std::max(best_res, prev_dp[in_cnt][0]);
    // int fsum = 0;
    // for (int i = 0; i < n; ++i) fsum += arr[i];
    // cout << fsum - best_res << "\n";
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
