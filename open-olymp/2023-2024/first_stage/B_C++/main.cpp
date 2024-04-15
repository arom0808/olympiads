//#pragma GCC optimize("Ofast")
//#pragma GCC optimize(O3)
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
//#pragma GCC optimize("vpt")
//#pragma GCC optimize("rename-registers")
//#pragma GCC optimize("move-loop-invariants")
//#pragma GCC optimize("unswitch-loops")
//#pragma GCC optimize("function-sections")
//#pragma GCC optimize("data-sections")
//#pragma GCC optimize("branch-target-load-optimize")
//#pragma GCC optimize("branch-target-load-optimize2")
//#pragma GCC optimize("btr-bb-exclusive")
//#pragma GCC optimize("inline")
//#pragma GCC optimize("-fgcse")
//#pragma GCC optimize("-fgcse-lm")
//#pragma GCC optimize("-fipa-sra")
//#pragma GCC optimize("-ftree-pre")
//#pragma GCC optimize("-ftree-vrp")
//#pragma GCC optimize("-fpeephole2")
//#pragma GCC optimize("-ffast-math")
//#pragma GCC optimize("-fsched-spec")
//#pragma GCC optimize("-falign-jumps")
//#pragma GCC optimize("-falign-loops")
//#pragma GCC optimize("-falign-labels")
//#pragma GCC optimize("-fdevirtualize")
//#pragma GCC optimize("-fcaller-saves")
//#pragma GCC optimize("-fcrossjumping")
//#pragma GCC optimize("-fthread-jumps")
//#pragma GCC optimize("-freorder-blocks")
//#pragma GCC optimize("-fschedule-insns")
//#pragma GCC optimize("inline-functions")
//#pragma GCC optimize("-ftree-tail-merge")
//#pragma GCC optimize("-fschedule-insns2")
//#pragma GCC optimize("-fstrict-aliasing")
//#pragma GCC optimize("-falign-functions")
//#pragma GCC optimize("-fcse-follow-jumps")
//#pragma GCC optimize("-fsched-interblock")
//#pragma GCC optimize("-fpartial-inlining")
//#pragma GCC optimize("no-stack-protector")
//#pragma GCC optimize("-freorder-functions")
//#pragma GCC optimize("-findirect-inlining")
//#pragma GCC optimize("-fhoist-adjacent-loads")
//#pragma GCC optimize("-frerun-cse-after-loop")
//#pragma GCC optimize("inline-small-functions")
//#pragma GCC optimize("-finline-small-functions")
//#pragma GCC optimize("-ftree-switch-conversion")
//#pragma GCC optimize("-foptimize-sibling-calls")
//#pragma GCC optimize("-fexpensive-optimizations")
//#pragma GCC optimize("inline-functions-called-once")
//#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <iostream>
#include <vector>
#include <random>
#include <deque>

using namespace std;

template<typename T>
class SegmentTree {
private:
    vector<T> sums, sets;
    vector<bool> is_set;
    uint32_t size;

    void
    init_node(uint32_t node_id, uint32_t left, uint32_t right, const vector<T> &arr) {
        if (left >= right) sums[node_id] = 0;
        else if (left + 1 == right) sums[node_id] = arr[left];
        else {
            init_node(node_id * 2, left, (left + right) / 2, arr);
            init_node(node_id * 2 + 1, (left + right) / 2, right, arr);
            sums[node_id] = sums[node_id * 2] + sums[node_id * 2 + 1];
        }
    }

    void modify_transfer(uint32_t node_id, uint32_t node_left, uint32_t node_right) {
        if (node_left >= node_right || node_left + 1 == node_right || !is_set[node_id]) return;
        sets[node_id * 2] = sets[node_id * 2 + 1] = sets[node_id];
        sums[node_id * 2] = sets[node_id] * ((node_left + node_right) / 2 - node_left);
        sums[node_id * 2 + 1] = sets[node_id] * (node_right - (node_left + node_right) / 2);
        is_set[node_id * 2] = is_set[node_id * 2 + 1] = true;
        is_set[node_id] = false;
    }

    void _set(uint32_t node_id, uint32_t node_left, uint32_t node_right, uint32_t req_left, uint32_t req_right, T val) {
        if (node_left >= node_right || req_right <= node_left || req_left >= node_right) return;
        if (req_left <= node_left && req_right >= node_right) {
            sets[node_id] = val;
            sums[node_id] = val * (node_right - node_left);
            is_set[node_id] = true;
            return;
        }
        modify_transfer(node_id, node_left, node_right);
        _set(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
        _set(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
        sums[node_id] = sums[node_id * 2] + sums[node_id * 2 + 1];
    }


    T _sum(uint32_t node_id, uint32_t node_left, uint32_t node_right, uint32_t req_left, uint32_t req_right) {
        if (node_left >= node_right || req_right <= node_left || req_left >= node_right) return 0;
        modify_transfer(node_id, node_left, node_right);
        if (req_left <= node_left && req_right >= node_right) return sums[node_id];
        return _sum(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right) +
               _sum(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right);
    }


public:
    explicit SegmentTree(const vector<T> &arr)
            : sums(arr.size() * 4, 0), sets(arr.size() * 4, 0), is_set(arr.size() * 4, false), size(arr.size()) {
        init_node(1, 0, arr.size(), arr);
    }

    void set(uint32_t left, uint32_t right, T val) {
        _set(1, 0, size, left, right, val);
    }

    T sum(uint32_t left, uint32_t right) {
        return _sum(1, 0, size, left, right);
    }
};

template<typename T>
class PrefSum {
    vector<T> sums;

public:
    explicit PrefSum(const vector<T> &nums) : sums(nums.size() + 1, 0) {
        for (uint32_t i = 0; i < nums.size(); ++i) sums[i + 1] = sums[i] + nums[i];
    }

    T sum(uint32_t l, uint32_t r) { return sums[r] - sums[l]; }
};

class Sol {
    SegmentTree<uint64_t> nums;
    PrefSum<uint64_t> ps;
    uint32_t n;
    deque<pair<uint32_t, uint32_t>> que;
    bool was_changed = false;
public:

    void set(uint32_t l, uint32_t r, uint32_t k, uint64_t v) {
        que.emplace_back(0, n);
        while (!que.empty()) {
            auto [p_mask, nbit] = que.front();
            que.pop_front();
            if (r < p_mask || l > (p_mask | ((1u << nbit) - 1))) continue;
            if (l <= p_mask && r >= (p_mask | ((1u << nbit) - 1))) {
                was_changed = true;
                nums.set((p_mask ^ k) & (~((1u << nbit) - 1)),
                         (((p_mask ^ k) & (~((1u << nbit) - 1))) | ((1u << nbit) - 1)) + 1, v);
                continue;
            }
            if (nbit == 0) continue;
            que.emplace_back(p_mask, nbit - 1);
            que.emplace_back(p_mask | (1u << (nbit - 1)), nbit - 1);
        }
    }

    uint64_t sum(uint32_t l, uint32_t r, uint32_t k) {
        uint64_t res = 0;
        que.emplace_back(0, n);
        while (!que.empty()) {
            auto [p_mask, nbit] = que.front();
            que.pop_front();
            if (r < p_mask || l > (p_mask | ((1u << nbit) - 1))) continue;
            if (l <= p_mask && r >= (p_mask | ((1u << nbit) - 1))) {
                if (was_changed)
                    res += nums.sum((p_mask ^ k) & (~((1u << nbit) - 1)),
                                    (((p_mask ^ k) & (~((1u << nbit) - 1))) | ((1u << nbit) - 1)) + 1);
                else
                    res += ps.sum((p_mask ^ k) & (~((1u << nbit) - 1)),
                                  (((p_mask ^ k) & (~((1u << nbit) - 1))) | ((1u << nbit) - 1)) + 1);
                continue;
            }
            if (nbit == 0) continue;
            que.emplace_back(p_mask, nbit - 1);
            que.emplace_back(p_mask | (1u << (nbit - 1)), nbit - 1);
        }
        return res;
    }

    Sol(uint32_t n, const vector<uint64_t> &nums) : n(n), nums(nums), ps(nums) {}
};

class StupidSol {
    vector<uint64_t> nums;
    uint32_t n;
public:

    void set(uint32_t l, uint32_t r, uint32_t k, uint64_t v) {
        for (uint32_t i = l; i <= r; ++i) nums[i ^ k] = v;
    }

    uint64_t sum(uint32_t l, uint32_t r, uint32_t k) {
        uint64_t res = 0;
        for (uint32_t i = l; i <= r; ++i) res += nums[i ^ k];
        return res;
    }

    StupidSol(uint32_t n, const vector<uint64_t> &nums) : n(n), nums(nums) {}
};


namespace Dev {
    random_device dev;
    mt19937 rng(dev());

    uint32_t rand_num(uint32_t min, uint32_t max) {
        return uniform_int_distribution(min, max)(rng);
    }

    template<typename T>
    class RightSegTree {
        vector<T> nums;

    public:
        explicit RightSegTree(vector<T> arr) : nums(std::move(arr)) {}

        void set(uint32_t left, uint32_t right, T val) {
            for (uint32_t i = left; i < right; ++i) nums[i] = val;
        }

        T sum(uint32_t left, uint32_t right) {
            T res = 0;
            for (uint32_t i = left; i < right; ++i) res += nums[i];
            return res;
        }
    };

    void Test1() {
        while (true) {
            auto len = rand_num(1, 100);
            vector<uint32_t> nums(len), res1, res2;
            for (auto &&num: nums) num = rand_num(0, 100);
            cout << len << "\n";
            for (const auto &num: nums) cout << num << " ";
            SegmentTree st(nums);
            RightSegTree rst(nums);
            auto req_cnt = rand_num(1, 100);
            cout << "\n" << req_cnt << "\n";
            for (uint32_t i = 0; i < req_cnt; ++i) {
                uint32_t l = rand_num(0, len - 1), r = rand_num(l, len);
                if (rand_num(0, 1)) {
                    cout << "m " << l + 1 << " " << r + 1 << "\n";
                    res1.push_back(st.sum(l, r));
                    res2.push_back(rst.sum(l, r));
                } else {
                    uint32_t add = rand_num(0, 100);
                    cout << "a " << l + 1 << " " << r + 1 << " " << add << "\n";
                    st.set(l, r, add);
                    rst.set(l, r, add);
                }
            }
            cout << "\nMy res:\n";
            for (const auto &res: res1) cout << res << "\n";
            cout << "\nRight res:\n";
            for (const auto &res: res2) cout << res << "\n";
            if (res1 != res2) return;
            cout << "\n-------------------------------------\n";
        }
    }

//    void Test2() {
//        while (true) {
//            uint32_t n = rand_num(0, 5), len = 1u << n;
//            cout << n << "\n";
//            vector<uint32_t> nums(len);
//            for (auto &num: nums) {
//                num = rand_num(0, 100);
//                cout << num << " ";
//            }
//            uint32_t q = rand_num(1, 100);
//            cout << "\n" << q << "\n";
//            StupidSol stsol(n, nums);
//            Sol sol(n, nums);
//            uint32_t l, r, k, v;
//            vector<uint32_t> res1, res2;
//            res1.reserve(q);
//            res2.reserve(q);
//            for (uint32_t i = 0; i < q; ++i) {
//                l = rand_num(0, len - 1);
//                r = rand_num(l, len - 1);
//                k = rand_num(0, len - 1);
//                if (rand_num(0, 1)) {
//                    v = rand_num(0, 100);
//                    cout << "1 " << l << " " << r << " " << k << " " << v << "\n";
//                    sol.set(l, r, k, v);
//                    stsol.set(l, r, k, v);
//                } else {
//                    cout << "2 " << l << " " << r << " " << k << "\n";
//                    res1.push_back(sol.sum(l, r, k));
//                    res2.push_back(stsol.sum(l, r, k));
//                }
//            }
//            cout << "\nMy res:\n";
//            for (const auto &res: res1) cout << res << "\n";
//            cout << "\nRight res:\n";
//            for (const auto &res: res2) cout << res << "\n";
//            if (res1 != res2) return;
//            cout << "\n-------------------------------------\n";
//        }
//    }
}

int main() {
//    Dev::Test2();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t n;
    cin >> n;
    vector<uint64_t> nums(1u << n);
    for (auto &num: nums) cin >> num;
    Sol sol(n, nums);
    uint32_t q;
    cin >> q;
    uint64_t t, l, r, k, v;
    for (uint32_t i = 0; i < q; ++i) {
        cin >> t >> l >> r >> k;
        if (t == 1) {
            cin >> v;
            sol.set(l, r, k, v);
        } else cout << sol.sum(l, r, k) << "\n";
    }
    return 0;
}