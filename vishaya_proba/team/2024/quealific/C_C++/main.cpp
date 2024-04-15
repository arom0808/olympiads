#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

void gen_dp(const vector<int64_t> &arr, vector<int64_t> &dp, int64_t sz, bool is_max) {
    multiset<int64_t> dp_set;
    int64_t dp_sum = 0;
    for (int64_t i = 0; i < sz; ++i) {
        dp_set.insert(arr[i]);
        dp_sum += arr[i];
    }
    dp[sz] = dp_sum;
    for (int64_t i = sz; i < arr.size(); ++i) {
        if (is_max) {
            if (arr[i] > *dp_set.begin()) {
                dp_sum -= *dp_set.begin();
                dp_set.erase(dp_set.begin());
                dp_set.insert(arr[i]);
                dp_sum += arr[i];
            }
        } else {
            if (arr[i] < *dp_set.rbegin()) {
                dp_sum -= *dp_set.rbegin();
                dp_set.erase(prev(dp_set.end()));
                dp_set.insert(arr[i]);
                dp_sum += arr[i];
            }
        };
        dp[i + 1] = dp_sum;
    }
}

void solve() {
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> arr(n);
    for (auto &num: arr) cin >> num;
    int64_t sz = (n - k) / 2;
    vector<int64_t> left_dp(n + 1, 0), right_dp(n + 1, 0);
    gen_dp(arr, left_dp, sz, true);
    reverse(arr.begin(), arr.end());
    gen_dp(arr, right_dp, sz, false);
    int64_t res = numeric_limits<int64_t>::min();
    for (int64_t s1 = sz; n - s1 >= sz; ++s1)
        if (left_dp[s1] - right_dp[n - s1] > res)
            res = left_dp[s1] - right_dp[n - s1];
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t t;
    cin >> t;
    while (t--) solve();
    return 0;
}
