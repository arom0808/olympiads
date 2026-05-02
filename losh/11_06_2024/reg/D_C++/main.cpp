#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;


int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int64_t n;
    cin >> n;
    vector<int64_t> nums(n);
    for (auto &num: nums) cin >> num;
    vector<vector<int64_t>> poss(n);
    vector<int64_t> orig_num(n);
    for (int64_t i = 0; i < n; ++i) poss[nums[i]].push_back(i);
    for (int64_t num = 0, i = 0; i < n; ++i) {
        for (int pos: poss[i]) nums[pos] = num++, orig_num[nums[pos]] = i;
    }
    vector<int64_t> cnts(n);
    int64_t max_res = 0;
    for (int64_t i = 0; i < n; ++i) {
        ordered_set o_s;
        cnts.clear();
        cnts.resize(n);
        for (int64_t j = i; j < n; ++j) {
            o_s.insert(nums[j]);
            ++cnts[orig_num[nums[j]]];
            if ((j - i + 1) % 2 == 1) {
                int64_t m = orig_num[*o_s.find_by_order((j - i) / 2)];
                if (cnts[m] > max_res) max_res = cnts[m];
            } else {
                int64_t m1 = orig_num[*o_s.find_by_order((j - i) / 2)],
                        m2 = orig_num[*o_s.find_by_order((j - i) / 2 + 1)];
                if (cnts[m1] > max_res) max_res = cnts[m1];
                if (cnts[m2] > max_res) max_res = cnts[m2];
            }
        }
    }
    cout << max_res;
    return 0;
}
