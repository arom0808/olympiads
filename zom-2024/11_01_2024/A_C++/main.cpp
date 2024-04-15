#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    uint64_t n, A;
    cin >> n >> A;
    vector<pair<uint64_t, uint64_t>> ps(n);
    for (uint64_t i = 0; i < n; ++i) {
        cin >> ps[i].first;
        ps[i].second = i;
    }
    sort(ps.begin(), ps.end(), [](const pair<uint64_t, uint64_t> &a, const pair<uint64_t, uint64_t> &b) {
        return a.first < b.first;
    });
    vector<uint64_t> nums(n), inds(n);
    for (uint64_t i = 0; i < n; ++i) nums[i] = ps[i].first, inds[i] = ps[i].second;
    uint64_t max_res = 0, m1, m2;
    for (uint64_t i = 0; i < n; ++i) {
        uint64_t max_obr = A / nums[i];
        auto d = distance(nums.begin(), upper_bound(nums.begin(), nums.end(), max_obr));
        if (d-- == 0 || (d == i && d-- == 0)) continue;
        if (nums[i] * nums[d] > max_res) max_res = nums[i] * nums[d], m1 = inds[i], m2 = inds[d];
    }
    if (max_res == 0) cout << 0;
    else cout << max_res << "\n" << m1 + 1 << " " << m2 + 1;
    return 0;
}
