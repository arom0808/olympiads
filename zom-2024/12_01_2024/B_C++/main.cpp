#include <iostream>
#include <vector>
#include <random>

using namespace std;

const int64_t c6 = 1e6;

int64_t ok_sol(const vector<int64_t> &nums, int64_t k) {
    int64_t res = 0;
    for (int64_t i = 0; i < nums.size() - k + 1; ++i)
        for (int64_t j = 0; j < k / 2; ++j)
            res += nums[i + j] != nums[i + k - j - 1];
    return res;
}

int64_t my_sol(const vector<int64_t> &nums, int64_t k) {
    if (k == 1) return 0;
    vector<int64_t> from_0_cnts(c6 + 1, 0), from_1_cnts(c6 + 1, 0);
    int64_t n = nums.size(), res = 0, fr_0_cnt = 0, fr_1_cnt = 0;
    int64_t fr_0_left = -1, fr_0_right = -1, fr_1_left = -1, fr_1_right = -1;
    for (int64_t i = k / 2 + 1; i < n; ++i) {
        int64_t need_left = max(i % 2, max(k - i - 1, i - k + 1));
        int64_t need_right = min(i - 2, 2 * n - i - k);
        if (need_left > need_right) continue;
        auto &cnts = (i % 2 == 0 ? from_0_cnts : from_1_cnts);
        auto &now_cnt = (i % 2 == 0 ? fr_0_cnt : fr_1_cnt);
        auto &now_left = (i % 2 == 0 ? fr_0_left : fr_1_left), &now_right = (i % 2 == 0 ? fr_0_right : fr_1_right);
        if (now_left == -1) {
            for (int64_t j = need_left; j <= need_right; j += 2) ++cnts[nums[j]], ++now_cnt;
            now_left = need_left, now_right = need_right;
        } else {
            while (now_right < need_right) ++cnts[nums[now_right += 2]], ++now_cnt;
            while (now_left > need_left) ++cnts[nums[now_left -= 2]], ++now_cnt;
            while (now_right > need_right) --cnts[nums[(now_right -= 2) + 2]], --now_cnt;
            while (now_left < need_left) --cnts[nums[(now_left += 2) - 2]], --now_cnt;
        }
        res += now_cnt - cnts[nums[i]];
    }
    return res;
}

namespace Test {
    random_device dev;
    mt19937 rng(dev());

    int64_t randint(int64_t a, int64_t b) { return uniform_int_distribution(a, b)(rng); }

    pair<vector<int64_t>, int64_t> gen() {
        const int max_nn = 10;
        int64_t n = randint(1, max_nn), k;
        do k = randint(1, n); while (k % 2 == 0);
        vector<int64_t> nums(n);
        for (auto &num: nums) num = randint(1, max_nn);
        return {nums, k};
    }

    void Test() {
        while (true) {
            auto [nums, k] = gen();
            int64_t ok_res = ok_sol(nums, k), my_res = my_sol(nums, k);
            if (my_res != ok_res) {
                cout << nums.size() << " " << k << "\n";
                for (auto &num: nums) cout << num << " ";
                cout << "\n\nok: " << ok_res << "\nmy: " << my_res;
                break;
            }
        }
    }
}

int main() {
//    Test::Test();
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> nums(n);
    for (auto &num: nums) cin >> num;
    if (k == 1) {
        cout << 0;
        return 0;
    }
    cout << my_sol(nums, k);


//    for (int32_t i = 0; i + 3 < k; ++i) {
//        if (i % 2 == 0) ++from_0_cnts[nums[i]];
//        else ++from_1_cnts[nums[i]];
//    }
//    for (int32_t i = k - 1; i <= n - k / 2; ++i) {
//        if (i - k - 1 >= 0) {
//            if (i % 2 == 0) --from_0_cnts[nums[i - k - 1]];
//            else --from_1_cnts[nums[i - k - 1]];
//        }
//        if (i % 2 == 0) ++from_0_cnts[nums[i - 2]];
//        else ++from_1_cnts[nums[i - 2]];
//        res += k / 2 - (i % 2 == 0 ? from_0_cnts[nums[i]] : from_1_cnts[nums[i]]);
//    }
//    for (int32_t i = 1; i < k / 2; ++i) res += nums[i] != nums[k - i - 1];
//    for (int32_t i = (k - 1 <= n - k / 2 ? n - k / 2 + 1 : k - 1); i < n; ++i) {
//
//    }
//    cout << res;
    return 0;
}
