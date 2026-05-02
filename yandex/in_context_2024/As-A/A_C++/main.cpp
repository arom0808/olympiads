#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const int32_t inf = 1e9 + 10;

int32_t n;
vector<int32_t> nums;
vector<int32_t> dp1, dp2;
vector<int32_t> prev1, prev2;
vector<int32_t> seq1, seq2;

bool cmp(int32_t a, int32_t b) {
    return nums[a] < nums[b];
}

void make_dp(vector<int32_t> &dp, vector<int32_t> &prev) {
    for (int32_t i = 0; i < n; ++i) {
        int32_t pos = distance(dp.begin(), lower_bound(dp.begin(), dp.end(), i, &cmp));
        dp[pos] = i;
        if (pos > 0) prev[i] = dp[pos - 1];
    }
}

void make_seq(const vector<int32_t> &dp, const vector<int32_t> &prev, vector<int32_t> &seq) {
    seq.clear();
    int32_t pos = *std::prev(lower_bound(dp.begin(), dp.end(), n + 1, &cmp));
    seq.push_back(pos);
    while (prev[pos] != pos && prev[pos] != n) seq.push_back(pos = prev[pos]);
}

bool check1(const vector<int32_t> &seq) {
    return seq.front() > 0 || seq.back() < n - 1;
}

bool check2(const vector<int32_t> &seq) {
    for (int32_t i = 0; i + 1 < seq.size(); ++i)
        if (seq[i + 1] - seq[i] > 1 && nums[seq[i + 1]] - nums[seq[i]] > 1)
            return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    nums.resize(n + 2), dp1.resize(n + 1), dp2.resize(n + 1), prev1.resize(n), prev2.resize(n);
    for (int32_t i = 0; i < n; ++i) cin >> nums[i];
    nums[n] = -inf, nums[n + 1] = inf;
    dp1.front() = n, dp2.front() = n;
    fill(next(dp1.begin()), dp1.end(), n + 1), fill(next(dp2.begin()), dp2.end(), n + 1);
    iota(prev1.begin(), prev1.end(), 0), iota(prev2.begin(), prev2.end(), 0);
    make_dp(dp1, prev1);
    for (int32_t i = 0; i < n; ++i) nums[i] = -nums[i];
    reverse(nums.begin(), next(nums.begin(), n));
    make_dp(dp2, prev2);
    for (int32_t i = 0; i < n; ++i) nums[i] = -nums[i];
    reverse(nums.begin(), next(nums.begin(), n));
    make_seq(dp1, prev1, seq1), make_seq(dp2, prev2, seq2);
    reverse(seq1.begin(), seq1.end());
    for (auto &el: seq2) el = n - 1 - el;
    if (check1(seq1) || check1(seq2) || check2(seq1) || check2(seq2)) cout << seq1.size() + 1 << "\n";
    else cout << seq1.size() << "\n";
    return 0;
}
