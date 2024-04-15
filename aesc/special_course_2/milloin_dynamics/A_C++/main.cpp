#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main() {
    int64_t n, m;
    cin >> n;
    vector<int64_t> first_seq(n);
    for (auto &num: first_seq) cin >> num;
    cin >> m;
    vector<int64_t> sec_seq(m);
    for (auto &num: sec_seq) cin >> num;
    pair<int64_t, int64_t> res(0, 0);
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(m + 1, 0));
    for (int64_t i = 1; i <= n; ++i) {
        for (int64_t j = 1; j <= m; ++j) {
            if (first_seq[i - 1] == sec_seq[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (dp[i][j] > dp[res.first][res.second]) { res = {i, j}; }
        }
    }
    vector<int64_t> seq;
    seq.reserve(dp[res.first][res.second]);
    for (int64_t i = res.first, j = res.second; i > 0 && j > 0;) {
        if (first_seq[i - 1] == sec_seq[j - 1]) {
            seq.push_back(first_seq[i - 1]);
            --i;
            --j;
        } else {
            if (dp[i - 1][j] > dp[i][j - 1]) --i;
            else --j;
        }
    }
    cout << dp[res.first][res.second] << "\n";
    for (auto num: ranges::reverse_view(seq)) cout << num << " ";
    return 0;
}
