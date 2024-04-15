#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int32_t pow_mod(int32_t x, int32_t n) {
    int32_t res = 1;
    for (int32_t t_p = x; n; n >>= 1, t_p = t_p * t_p) if (n & 1ull) res *= t_p;
    return res;
}

bool is_pow_ok(int32_t num, int32_t p) {
    int32_t l = 2, r = num;
    if (p == 2) r = min(r, 320);
    if (p == 3) r = min(r, 50);
    if (p == 4) r = min(r, 20);
    else r = min(r, 11);
    while (l < r) {
        int32_t m = (l + r) / 2;
        if (pow_mod(m, p) < num) l = m + 1;
        else if (pow_mod(m, p) > num) r = m - 1;
        else l = r = m;
    }
    return pow_mod(l, p) == num;
}

//class SegmentTree {
//private:
//    struct Node {
//        map<int32_t, int32_t> prime_dels;
//    };
//
//    vector<Node> nodes;
//    int32_t size;
//
//    void
//    init_node(int32_t node_id, int32_t left, int32_t right, const vector<int32_t> &arr, const vector<int32_t> &lp) {
//        if (left >= right) return;
//        auto &cn = nodes[node_id];
//        if (left + 1 == right) {
//            for (int32_t num = arr[left]; num > 1; num /= lp[num]) {
//                auto it = cn.prime_dels.find(lp[num]);
//                if (it != cn.prime_dels.end()) ++it->second;
//                else cn.prime_dels.emplace(lp[num], 1);
//            }
//        } else {
//            init_node(node_id * 2, left, (left + right) / 2, arr, lp);
//            init_node(node_id * 2 + 1, (left + right) / 2, right, arr, lp);
//            cn.prime_dels = nodes[node_id * 2].prime_dels;
//            for (auto d: nodes[node_id * 2 + 1].prime_dels) {
//                auto it = cn.prime_dels.find(d.first);
//                if (it != cn.prime_dels.end()) it->second += d.second;
//                else cn.prime_dels.emplace(d.first, d.second);
//            }
//        }
//    }
//
//    int32_t _max(int32_t node_id, int32_t node_left, int32_t node_right, int32_t req_left,
//                 int32_t req_right) {
//        if (node_left >= node_right) return 0;
//        modify_transfer(node_id, node_left, node_right);
//        if (req_right <= node_left || req_left >= node_right) return 0;
//        if (req_left <= node_left && req_right >= node_right) return nodes[node_id].max;
//        return max(_max(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right),
//                   _max(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right));
//    }
//
//
//public:
//    explicit SegmentTree(const vector<int32_t> &arr) : nodes(arr.size() * 4), size(arr.size()) {
//        init_node(1, 0, arr.size(), arr);
//    }
//
//    void add(int32_t left, int32_t right, int32_t val) {
//        _add(1, 0, size, left, right + 1, val);
//    }
//
//    int32_t max(int32_t left, int32_t right) {
//        return _max(1, 0, size, left, right + 1);
//    }
//};

int main() {
    int32_t max_num = 1e5 + 1;
    vector<int32_t> lp(max_num + 1, 0), primes;
    primes.reserve(10000);
    for (int32_t i = 2; i <= max_num; ++i) {
        if (!lp[i]) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int32_t j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= max_num; ++j)
            lp[i * primes[j]] = primes[j];
    }

    int32_t n;
    cin >> n;
    vector<map<int32_t, int32_t>> pref_dels(n);
    set<int32_t> allowed_pows{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    bool is_all_ones = true;
    for (int32_t i = 0, num; i < n; ++i) {
        cin >> num;
        if (num != 1) is_all_ones = false;
        auto &cn = pref_dels[i];
        if (i > 0) cn = pref_dels[i - 1];
        for (; num > 1; num /= lp[num]) {
            auto it = cn.find(lp[num]);
            if (it != cn.end()) ++it->second;
            else cn.emplace(lp[num], 1);
        }
        if (num != 1) for (int32_t p = 2; p < 20; ++p) if (!is_pow_ok(num, p)) allowed_pows.erase(p);
    }
    return 0;
}