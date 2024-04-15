#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int64_t n, t, s, q;
    cin >> n >> t >> s;
    vector<int64_t> nums(n), maxs(n), mins(n);
    for (auto &num: nums) cin >> num;
    cin >> q;
    int64_t first_used_group = -2, pre_group = -2, empty_cnt = 0, pre_max_ost = 1;
    for (int64_t i = n - 1; i >= 0; --i) {
        int64_t now_group = nums[i] >= t ? -1 : (t - nums[i] - 1) / s;
        if (first_used_group == -2) pre_group = first_used_group = now_group;
        if (i + 1 < n) {
            auto val = pre_max_ost + 1 - (now_group - pre_group);
            if (val <= 0) empty_cnt += 1 - val, pre_max_ost = 1;
            else pre_max_ost = val;
        }
        mins[i] = min(n - i, now_group - first_used_group + 1 - empty_cnt);
        maxs[i] = distance(lower_bound(nums.begin(), nums.end(), t - s * (first_used_group + n + empty_cnt - i)),
                           nums.end());
        pre_group = now_group;
    }
    for (int64_t i = 0, d, p; i < q; ++i) {
        cin >> d >> p;
        int64_t pos = distance(nums.begin(), lower_bound(nums.begin(), nums.end(), d));
        cout << (p >= mins[pos] && p <= maxs[pos] ? "Yes\n" : "No\n");
    }
}

//namespace Test {
//    struct InData {
//        int64_t t, s;
//        vector<int64_t> nums;
//        vector<pair<int64_t, int64_t>> reqs;
//    };
//
//    random_device dev;
//    mt19937 rng(dev());
//
//    int64_t randint(int64_t a, int64_t b) { return uniform_int_distribution(a, b)(rng); }
//
//    InData gen() {
//        int64_t n = 7;
//        set<int64_t> nums_set;
//        while (nums_set.size() < n) nums_set.insert(randint(1, n + 3));
//        vector<int64_t> nums(nums_set.begin(), nums_set.end());
//        int64_t q = randint(1, 5);
//        vector<pair<int64_t, int64_t>> reqs(q);
//        for (auto &[d, p]: reqs) p = randint(1, n), d = nums[randint(0, n - 1)];
//        return {randint(1, n + 3), randint(1, n + 3), nums, reqs};
//    }
//
//    void full_ok_sol(InData &in_data, vector<bool> &ans) {
//        auto [t, s, nums, reqs] = in_data;
//        ans.resize(reqs.size(), false);
//        vector<int64_t> poss(nums.size(), 0), solved(nums.size(), 0);
//        int64_t timer = 1;
//        do {
//            int64_t nt = t, suc = 0;
//            while (suc < nums.size()) {
//                int64_t lms = 0;
//                for (int64_t i = 0; i < nums.size(); ++i) {
//                    if (solved[i] == timer || nums[i] < nt) continue;
//                    if (nums[i] > lms) solved[i] = timer, lms = nums[i], poss[i] = ++suc;
//                }
//                nt -= s;
//            }
//            for (int64_t qi = 0; qi < reqs.size(); ++qi)
//                for (int64_t i = 0; i < nums.size(); ++i)
//                    if (reqs[qi].first == nums[i] && reqs[qi].second == poss[i]) ans[qi] = true;
//            ++timer;
//        } while (next_permutation(nums.begin(), nums.end()));
//    }
//
//    void my_sol(InData &in_data, vector<bool> &ans) {
//        auto [t, s, nums, reqs] = in_data;
//        ans.resize(reqs.size(), false);
//        int64_t n = nums.size();
//        vector<int64_t> maxs(n), mins(n), max_ost(n, 1);
//        int64_t first_used_group = -2, count_to_set = 0, max_to_set_id = n, groups_cnt = 0, empty_cnt = 0, pre_group = -2;
//        for (int64_t i = n - 1; i >= 0; --i) {
//            bool new_group = false;
//            if (first_used_group == -2) {
//                if (nums[i] >= t) first_used_group = -1;
//                else first_used_group = (t - nums[i] - 1) / s;
//                pre_group = first_used_group;
//            }
//            if (nums[i] >= t) { if (groups_cnt == 0) ++groups_cnt, new_group = true; }
//            else if (i == n - 1 || (t - nums[i + 1] - 1) / s != (t - nums[i] - 1) / s
//                     || ((t - nums[i + 1] - 1) < 0 && (t - nums[i] - 1) >= 0))
//                ++groups_cnt, new_group = true;
////            mins[i] = groups_cnt;
//            int64_t now_group = nums[i] >= t ? -1 : (t - nums[i] - 1) / s;
//            if (i + 1 < n) {
//                if (pre_group == now_group) max_ost[i] = max_ost[i + 1] + 1;
//                else {
//                    auto val = max_ost[i + 1] + 1 - (now_group - pre_group);
//                    if (val <= 0)
//                        empty_cnt += 1 - val;
//                    else max_ost[i] = val;
//                }
//            }
//            mins[i] = min(n - i, now_group - first_used_group + 1 - empty_cnt);
//            maxs[i] = distance(lower_bound(nums.begin(), nums.end(), t - s * (first_used_group + n + empty_cnt - i)),
//                               nums.end());
//            int64_t max2 = distance(lower_bound(nums.begin(), nums.end(), t - s * (now_group + 1)), nums.end());
//            if (max2 > maxs[i]) maxs[i] = max2;
//
//            pre_group = now_group;
////            ++count_to_set;
////            if (new_group && count_to_set <= now_group - first_used_group + 1) {
////                for (int64_t its = i + 1; its <= max_to_set_id && its < n; ++its)
////                    maxs[its] = n - i - 1;
////                count_to_set = 1;
////                max_to_set_id = i;
////                first_used_group = now_group;
////            }
////            if (n - i > now_group - first_used_group + 1) {
////                maxs[i] = distance(
////                        lower_bound(nums.begin(), nums.end(),
////                                    nums[i] < t ? t - ((t - nums[i] - 1) / s + 2) * s : t - s),
////                        nums.end());
////            } else {
////                maxs[i] = distance(
////                        lower_bound(nums.begin(), nums.end(), nums[i] < t ? t - ((t - nums[i] - 1) / s + 1) * s : t),
////                        nums.end());
////            }
//        }
////        for (int64_t its = 0; its <= max_to_set_id && its < n; ++its) maxs[its] = n;
//        for (int64_t i = 0; i < reqs.size(); ++i) {
//            auto [d, p] = reqs[i];
//            int64_t pos = distance(nums.begin(), lower_bound(nums.begin(), nums.end(), d));
//            ans[i] = p >= mins[pos] && p <= maxs[pos];
//        }
//    }
//
//    void Test() {
//        while (true) {
//            auto in_data_1 = gen(), in_data_2 = in_data_1;
//            vector<bool> ans1, ans2;
//            full_ok_sol(in_data_1, ans1);
//            my_sol(in_data_2, ans2);
//            if (ans1 != ans2) {
//                cout << in_data_1.nums.size() << " " << in_data_1.t << " " << in_data_1.s << "\n";
//                for (auto &num: in_data_1.nums) cout << num << " ";
//                cout << "\n" << in_data_1.reqs.size() << "\n";
//                for (auto &req: in_data_1.reqs) cout << req.first << " " << req.second << "\n";
//                cout << "\nok sol:\n";
//                for (auto a: ans1) cout << (a ? "Yes\n" : "No\n");
//                cout << "\nmy sol:\n";
//                for (auto a: ans2) cout << (a ? "Yes\n" : "No\n");
//                cout.flush();
//                my_sol(in_data_2, ans2);
//                break;
//            }
//        }
//    }
//};


//    Test::Test();

//    int64_t n, t, s;
//    cin >> n >> t >> s;
//    vector<int64_t> nums(n);
//    for (int64_t i = 0; i < n; ++i) cin >> nums[i];
//    int64_t q;
//    cin >> q;
//    vector<pair<int64_t, int64_t>> reqs(q);
//    for (auto &req: reqs) cin >> req.first >> req.second;
//    Test::InData id{t, s, nums, reqs};
//    vector<bool> ans;
//    Test::my_sol(id, ans);
//    for (auto a: ans) cout << (a ? "Yes\n" : "No\n");


//    vector<int64_t> maxs(n), mins(n);
//    int64_t groups_cnt = 0;
//    for (int64_t i = n - 1; i >= 0; --i) {
//        bool new_group = false;
//        if (nums[i] >= t) { if (groups_cnt == 0) ++groups_cnt, new_group = true; }
//        else if (i == n - 1 || (t - nums[i + 1] - 1) / s != (t - nums[i] - 1) / s) ++groups_cnt, new_group = true;
//        mins[i] = groups_cnt;
//        if (new_group) {
//            maxs[i] = distance(
//                    lower_bound(nums.begin(), nums.end(), nums[i] < t ? t - ((t - nums[i] - 1) / s + 1) * s : t),
//                    nums.end());
//        } else {
//            maxs[i] = distance(
//                    lower_bound(nums.begin(), nums.end(), nums[i] < t ? t - ((t - nums[i] - 1) / s + 2) * s : t - s),
//                    nums.end());
//        }
//    }
//    int64_t q;
//    cin >> q;
//    for (int64_t i = 0, d, p; i < q; ++i) {
//        cin >> d >> p;
//        int64_t pos = distance(nums.begin(), lower_bound(nums.begin(), nums.end(), d));
//        if (p >= mins[pos] && p <= maxs[pos]) cout << "Yes\n";
//        else cout << "No\n";
//    }
