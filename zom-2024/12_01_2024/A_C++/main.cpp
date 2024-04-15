#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t n, m;
    cin >> n >> m;
    vector<uint32_t> nums(n);
    for (auto &num: nums) cin >> num;
    uint32_t bad_cnt = 0;
    for (uint32_t i = 1; i < n; ++i) if (nums[i - 1] > nums[i]) ++bad_cnt;
    char c;
    for (uint32_t i = 0, k, x; i < m; ++i) {
        cin >> c;
        if (c == '?') cout << (bad_cnt ? "NO\n" : "YES\n");
        else {
            cin >> k >> x;
            if (--k > 0) {
                if (nums[k - 1] > nums[k] && nums[k - 1] <= x) --bad_cnt;
                else if (nums[k - 1] <= nums[k] && nums[k - 1] > x) ++bad_cnt;
            }
            if (k + 1 < n) {
                if (nums[k] > nums[k + 1] && x <= nums[k + 1]) --bad_cnt;
                else if (nums[k] <= nums[k + 1] && x > nums[k + 1]) ++bad_cnt;
            }
            nums[k] = x;
        }
    }
    return 0;
}
