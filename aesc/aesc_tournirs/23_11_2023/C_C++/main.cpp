#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class PrefSum {
public:
    vector<uint64_t> sums;

    [[nodiscard]] inline uint64_t sum(uint32_t l, uint32_t r) const {
        if (l > 0) return sums[r - 1] - sums[l - 1];
        if (r > 0) return sums[r - 1];
        return 0;
    }

    explicit PrefSum(const vector<uint32_t> &nums) : sums(nums.size()) {
        for (uint32_t i = 0; i < nums.size(); ++i) sums[i] = (i > 0 ? sums[i - 1] : 0ull) + nums[i];
    }
};



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t n, a, b;
    cin >> n >> a >> b;
    vector<uint32_t> nums(n);
    for (auto &num: nums) cin >> num;
    PrefSum sums(nums);
    uint32_t max_el = *max_element(nums.begin(), nums.end());

    vector<vector<vector<bool>> dp(n, vector<vector<bool>>())
    return 0;
}

//
//vector<uint64_t> raw_ks(b - a + 1);
//for (uint32_t i = 0; i < raw_ks.size(); ++i) raw_ks[i] = min_for_k(nums, sums, max_el, a + i);
//if (raw_ks.front() == 0) {
//cout << 0;
//return 0;
//}
//uint64_t min_lg = 64;
//for (auto min_max_el: raw_ks) min_lg = min(min_lg, __lg(min_max_el));
//vector<uint32_t> ks;
//ks.reserve(b - a + 1);
//for (uint32_t i = 0; i < raw_ks.size(); ++i)
//if (__lg(raw_ks[i]) == min_lg)
//ks.emplace_back(a + i);
//uint64_t now_min_res = (1ull << (min_lg + 1)) - 1;
//for (auto k: ks) {
//uint64_t now_sure_ones = 0;
//for (int32_t i = min_lg; i >= 0; --i)
//if (!try_recursion(nums, sums, k, now_sure_ones | ((1ull << i) - 1)))
//now_sure_ones |= 1ull << i;
//if (now_sure_ones < now_min_res) now_min_res = now_sure_ones;
//}
//cout << now_min_res;
//
//bool check_for_k_s(const vector<uint32_t> &nums, const PrefSum &sums, uint32_t k, uint64_t s) {
//    uint32_t now_start = 0;
//    for (uint32_t el = 0; el < k; ++el) {
//        uint32_t l = now_start + 1, r = nums.size() - (k - el - 1);
//        while (l != r) {
//            auto m = (l + r) / 2 + (l + r) % 2;
//            auto this_sum = sums.sum(now_start, m);
//            if (this_sum > s) r = m - 1;
//            else l = m;
//        }
//        if (sums.sum(now_start, l) > s) return false;
//        now_start = l;
//    }
//    return now_start == nums.size();
//}
//
//uint64_t min_for_k(const vector<uint32_t> &nums, const PrefSum &sums, uint32_t max_el, uint32_t k) {
//    uint64_t ls = max_el, rs = sums.sum(0, nums.size());
//    while (ls != rs) {
//        auto ms = (ls + rs) / 2;
//        if (check_for_k_s(nums, sums, k, ms)) rs = ms;
//        else ls = ms + 1;
//    }
//    return ls;
//}
//
//bool try_recursion(const vector<uint32_t> &nums, const PrefSum &sums, uint32_t k, uint64_t ntr,
//                   uint32_t now_start = 0, uint32_t el = 0) {
//    if (el == k) return now_start == nums.size();
//    for (uint32_t n_s = now_start + 1; n_s <= nums.size() - (k - el - 1); ++n_s) {
//        if (sums.sum(now_start, n_s) > ntr)
//            return false;
//        if ((sums.sum(now_start, n_s) | ntr) == ntr && try_recursion(nums, sums, k, ntr, n_s, el + 1))
//            return true;
//    }
//    return false;
//}