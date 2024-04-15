#include <iostream>
#include <vector>

using namespace std;

int32_t gen_num(const vector<uint32_t> &ones, uint32_t bad_cnt) {
    if (bad_cnt > 0) return -1;
    int32_t res = 0;
    for (uint32_t i = 0; i < ones.size(); ++i) if (ones[i]) res |= 1 << i;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t n, q;
    cin >> n;
    vector<uint32_t> nums(n);
    for (auto &num: nums) cin >> num;

    vector<uint32_t> zeros(32, 0), ones(32, 0), bad_zeros(32, 0), bad_ones(32, 0);
    uint32_t bad_cnt = 0;

    auto sub_add_f = [&bad_cnt](vector<uint32_t> &this_ok, vector<uint32_t> &this_bad,
                                vector<uint32_t> &other_ok, uint32_t pos) {
        if (other_ok[pos]) {
            ++this_bad[pos];
            ++bad_cnt;
        } else ++this_ok[pos];
    };

    auto add_f = [&](uint32_t i) {
        if (!(nums[i] ^ nums[i + 1])) return;
        auto pos = __lg(nums[i] ^ nums[i + 1]), m = 1u << pos;
        if (nums[i] & m) sub_add_f(ones, bad_ones, zeros, pos);
        else sub_add_f(zeros, bad_zeros, ones, pos);
    };

    auto sub_del_f = [&bad_cnt](vector<uint32_t> &this_ok, vector<uint32_t> &this_bad,
                                vector<uint32_t> &other_ok, vector<uint32_t> &other_bad, uint32_t pos) {
        if (this_bad[pos]) {
            --this_bad[pos];
            --bad_cnt;
        } else {
            --this_ok[pos];
            if (!this_ok[pos] && other_bad[pos]) {
                bad_cnt -= other_bad[pos];
                other_ok[pos] = other_bad[pos];
                other_bad[pos] = 0;
            }
        }
    };

    auto del_f = [&](uint32_t i) {
        if (!(nums[i] ^ nums[i + 1])) return;
        auto pos = __lg(nums[i] ^ nums[i + 1]), m = 1u << pos;
        if (nums[i] & m) sub_del_f(ones, bad_ones, zeros, bad_zeros, pos);
        else sub_del_f(zeros, bad_zeros, ones, bad_ones, pos);
    };

    for (uint32_t i = 0; i + 1 < nums.size(); ++i) add_f(i);
    cout << gen_num(ones, bad_cnt) << "\n";

    cin >> q;
    for (uint32_t _ = 0, p, v; _ < q; ++_) {
        cin >> p >> v;
        --p;
        for (uint32_t i = p > 0 ? p - 1 : p; i <= p && i + 1 < nums.size(); ++i) del_f(i);
        nums[p] = v;
        for (uint32_t i = p > 0 ? p - 1 : p; i <= p && i + 1 < nums.size(); ++i) add_f(i);
        cout << gen_num(ones, bad_cnt) << "\n";
    }
    return 0;
}




/*

namespace Stupid {

    int32_t may_sol(const vector<uint32_t> &nums) {
        uint32_t zeros = 0xffffffff, ones = 0;
        for (std::uint32_t i = 0; i + 1 < nums.size(); ++i) {
            auto dif = nums[i] ^ nums[i + 1];
            if (dif == 0) continue;
            auto m = 1u << __lg(dif);
            bool nv = nums[i] & m;
            if (nv) {
                if (!(zeros & m)) return -1;
                ones |= m;
            } else {
                if (ones & m) return -1;
                zeros &= ~m;
            }
        }
        return ones;
    }

    vector<int32_t> full_sol(vector<uint32_t> nums, const vector<pair<uint32_t, uint32_t>> &changes) {
        vector<int32_t> res;
        res.reserve(changes.size() + 1);
        res.push_back(may_sol(nums));
        for (auto [p, v]: changes) {
            nums[p] = v;
            res.push_back(may_sol(nums));
        }
        return res;
    }
}



namespace Test {
    random_device dev;

    mt19937 rng(dev());

    int32_t randint(int32_t a, int32_t b) { return uniform_int_distribution(a, b)(rng); }

    using Ins = pair<vector<uint32_t>, vector<pair<uint32_t, uint32_t>>>;
    using Res = vector<int32_t>;

    void print_ins(const Ins &ins) {
        cout << ins.first.size() << "\n";
        for (const auto num: ins.first) cout << num << " ";
        cout << "\n" << ins.second.size() << "\n";
        for (const auto [p, v]: ins.second) cout << p + 1 << " " << v << "\n";
        cout << "\n";
    }

    void print_res(const Res &res) {
        for (auto r: res) cout << r << "\n";
        cout << "\n";
    }

    Ins gen() {
        uint32_t n = randint(1, 100), q = randint(0, 100);
        vector<uint32_t> nums(n);
        vector<pair<uint32_t, uint32_t>> changes(q);
        for (auto &num: nums) num = randint(0, 100);
        for (auto &[p, v]: changes) {
            p = randint(0, n - 1);
            v = randint(0, 100);
        }
        return {nums, changes};
    }

    void Test() {
        while (true) {
            auto ins = gen();
            auto a = Stupid::full_sol(ins.first, ins.second),
                    b = MySol::full_sol(ins.first, ins.second);
            if (a != b) {
                print_ins(ins);
                print_res(a);
                print_res(b);
                break;
            }
        }
    }
}
*/