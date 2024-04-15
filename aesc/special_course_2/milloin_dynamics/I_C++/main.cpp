#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

using namespace std;

const int32_t inf = 2e9, minf = -2e9;

int main() {
    int32_t n;
    cin >> n;
    vector<int32_t> nums(n);
    for (auto &num: nums) {
        cin >> num;
        num = -num;
    }
    vector<int32_t> dp(n + 1, inf), pos(n + 1), prev(n);
    pos[0] = dp[0] = minf;
    for (int32_t i = 0; i < n; ++i) {
        int32_t pp = distance(dp.begin(), upper_bound(dp.begin(), dp.end(), nums[i]));
        if (pp <= n && nums[i] < dp[pp]) {
            dp[pp] = nums[i];
            pos[pp] = i;
            prev[i] = pos[pp - 1];
        }
    }
    int32_t len = distance(dp.begin(), lower_bound(dp.begin(), dp.end(), inf)) - 1;
    vector<int32_t> res;
    res.reserve(len);
    for (int32_t p = pos[len]; p >= 0; p = prev[p]) res.push_back(p);
    cout << len << "\n";
    for (auto &e: ranges::reverse_view(res)) cout << e + 1 << " ";
    return 0;
}