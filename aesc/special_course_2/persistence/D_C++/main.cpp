#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdint>

using namespace std;

const int32_t maxn = 3e5;

namespace st {
    struct Node {
        vector<int32_t> vals;

        int32_t count_less(int32_t k) {
            return static_cast<int32_t>(distance(vals.begin(), lower_bound(vals.begin(), vals.end(), k)));
        }
    };

    Node tree[maxn * 4];
    int32_t size;

    void init(int32_t id, int32_t l, int32_t r, const vector<int32_t> &vals) {
        if (l >= r) return;
        auto &nvals = tree[id].vals;
        nvals.clear();
        nvals.reserve(r - l);
        if (r - l == 1) {
            nvals.push_back(vals[l]);
            return;
        }
        init(id * 2, l, (l + r) / 2, vals);
        init(id * 2 + 1, (l + r) / 2, r, vals);
        const auto &lvals = tree[id * 2].vals, &rvals = tree[id * 2 + 1].vals;
        for (int32_t i1 = 0, i2 = 0; i1 < lvals.size() || i2 < rvals.size();) {
            if (i1 < lvals.size() && (i2 >= rvals.size() || lvals[i1] < rvals[i2])) nvals.push_back(lvals[i1++]);
            else nvals.push_back(rvals[i2++]);
        }
    }

    void assign(const vector<int32_t> &vals) {
        size = vals.size();
        init(1, 0, size, vals);
    }

    int32_t _count_less(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b, int32_t k) {
        if (l >= r || r <= a || b <= l) return 0;
        if (a <= l && r <= b) return tree[id].count_less(k);
        return _count_less(id * 2, l, (l + r) / 2, a, b, k) + _count_less(id * 2 + 1, (l + r) / 2, r, a, b, k);
    }

    int32_t count_less(int32_t a, int32_t b, int32_t k) {
        return _count_less(1, 0, size, a, b, k);
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    vector<int32_t> nums(n);
    for (auto &v: nums) cin >> v;
    vector<int32_t> pre_pos(n, -1);
    map<int32_t, int32_t> pre_pos_map;
    for (int32_t i = 0; i < n; ++i) {
        auto it = pre_pos_map.find(nums[i]);
        if (it != pre_pos_map.end()) pre_pos[i] = it->second;
        pre_pos_map.insert_or_assign(nums[i], i);
    }
    st::assign(pre_pos);
    int32_t q;
    cin >> q;
    for (int32_t i = 0, a, b; i < q; ++i) {
        cin >> a >> b, --a;
        cout << st::count_less(a, b, a) << endl;
    }
    return 0;
}


//
//namespace Clever {
//    vector<int32_t> nums;
//    vector<int32_t> pre_pos;
//    map<int32_t, int32_t> pre_pos_map;
//
//    void assign(const vector<int32_t> &_nums) {
//        nums = _nums;
//        pre_pos.assign(nums.size(), -1);
//        pre_pos_map.clear();
//        for (int32_t i = 0; i < nums.size(); ++i) {
//            auto it = pre_pos_map.find(nums[i]);
//            if (it != pre_pos_map.end()) pre_pos[i] = it->second;
//            pre_pos_map.insert_or_assign(nums[i], i);
//        }
//        st::assign(pre_pos);
//    }
//
//    int32_t count_dif(int32_t a, int32_t b) {
//        return st::count_less(a, b, a);
//    }
//}
//
//namespace Stupid {
//    vector<int32_t> nums;
//
//    void assign(const vector<int32_t> &_nums) {
//        nums = _nums;
//    }
//
//    int32_t count_dif(int32_t a, int32_t b) {
//        set<int32_t> s;
//        for (int32_t i = a; i < b; ++i) s.insert(nums[i]);
//        return s.size();
//    }
//}
//
//namespace Test {
//    uint32_t seed = 12431432;
//    mt19937 rng(seed);
//
//    int32_t randint(int32_t a, int32_t b) {
//        return uniform_int_distribution(a, b)(rng);
//    }
//
//    struct InData {
//        vector<int32_t> nums;
//        vector<pair<int32_t, int32_t>> ques;
//    };
//
//    InData gen_input() {
//        int32_t n = randint(1, 4);
//        vector<int32_t> nums(n);
//        for (auto &v: nums) v = randint(1, 4);
//        int32_t q = randint(1, 4);
//        vector<pair<int32_t, int32_t>> ques(q);
//        for (auto &[l, r]: ques) {
//            l = randint(0, n - 1);
//            r = randint(l + 1, n);
//        }
//        return {nums, ques};
//    }
//
//    void print_input(const InData &data) {
//        cout << data.nums.size() << "\n";
//        for (auto v: data.nums) cout << v << " ";
//        cout << "\n" << data.ques.size() << "\n";
//        for (auto [l, r]: data.ques) cout << l + 1 << " " << r << "\n";
//        cout << "\n";
//    }
//
//    void print_output(const vector<int32_t> &r) {
//        for (auto v: r) cout << v << "\n";
//    }
//
//    void Test() {
//        while (true) {
//            auto [nums, ques] = gen_input();
//            Stupid::assign(nums);
//            Clever::assign(nums);
//            vector<int32_t> r1, r2;
//            for (auto [l, r]: ques) r1.push_back(Stupid::count_dif(l, r));
//            for (auto [l, r]: ques) r2.push_back(Clever::count_dif(l, r));
//            if (r1 != r2) {
//                cout << "Inputs:\n";
//                print_input({nums, ques});
//                cout << "Stupid out:\n";
//                print_output(r1);
//                cout << "Clever out:\n";
//                print_output(r2);
//                break;
//            }
//        }
//    }
//}