#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, x, y;
    cin >> n >> x >> y;
    vector<pair<int32_t, int32_t>> nums(n);
    for (int32_t i = 0; i < n; ++i) cin >> nums[i].first, nums[i].second = i;
    sort(nums.begin(), nums.end(), [](const pair<int32_t, int32_t> &a, const pair<int32_t, int32_t> &b) {
        return a.first < b.first;
    });
    for (int32_t i1 = 0, i2 = n - 1; i1 < n; ++i1) {
        while (i2 > i1 && nums[i1].first + nums[i2].first > x) --i2;
        if (i1 == i2) break;
        if (abs(nums[i1].first - nums[i2].first) < y) continue;
        cout << nums[i1].second + 1 << " " << nums[i2].second + 1 << "\n";
        return 0;
    }
//    for (auto p1: nums) {
//        auto num1 = p1.first;
//        if (num1 > x) continue;
//        auto it = upper_bound(nums.begin(), nums.end(), pair<int32_t, int32_t>(x - num1, 0));
//        if (it == nums.begin()) continue;
//        else --it;
//        auto p2 = *it;
//        auto num2 = p2.first;
//        if (num1 + num2 > x) continue;
//        if (max(num1, num2) - min(num1, num2) < y) continue;
//        auto pos1 = p1.second, pos2 = p2.second;
//        if (pos1 > pos2) swap(pos1, pos2);
//        cout << pos1 + 1 << " " << pos2 + 1 << "\n";
//        return 0;
//    }
    cout << "0\n";
    return 0;
}
