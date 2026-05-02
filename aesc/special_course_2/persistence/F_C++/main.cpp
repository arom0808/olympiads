#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

const int32_t mod = 1e9;

namespace st {
    struct Node {
        int32_t sum = 0;
        Node *l = nullptr, *r = nullptr;
    };

    const int32_t max_st_size = 1e7;

    Node tree[max_st_size];
    int32_t used_cnt = 0;
    int32_t size;

    inline int32_t node_sum(Node *v) { return v ? v->sum : 0; }

    void init(Node *&v, int32_t l, int32_t r) {
        if (l >= r) return;
        if (!v) v = &tree[used_cnt++];
        v->l = v->r = nullptr;
        if (r - l == 1) {
            v->sum = 0;
        } else {
            init(v->l, l, (l + r) / 2);
            init(v->r, (l + r) / 2, r);
            v->sum = node_sum(v->l) + node_sum(v->r);
        }
    }

    Node *assign(int32_t n) {
        size = n;
        Node *root = nullptr;
        init(root, 0, size);
        return root;
    }


    Node *_add(Node *v, int32_t l, int32_t r, int32_t pos, int32_t val) {
        if (l >= r || r <= pos || pos < l) return v;
        Node *nv = &(tree[used_cnt++] = *v);
        if (r - l == 1) {
            nv->sum += val;
        } else {
            nv->l = _add(v->l, l, (l + r) / 2, pos, val);
            nv->r = _add(v->r, (l + r) / 2, r, pos, val);
            nv->sum = node_sum(nv->l) + node_sum(nv->r);
        }
        return nv;
    }
    Node *add(Node *root, int32_t pos, int32_t val) {
        return _add(root, 0, size, pos, val);
    }

    int32_t _find_kth(Node *v1, Node *v2, int32_t l, int32_t r, int32_t k) {
        if (!v1 || !v2 || l >= r) return -1;
        if (r - l == 1 && k < v2->sum - v1->sum) return l;
        int32_t left_size = node_sum(v2->l) - node_sum(v1->l);
        if (left_size > k) return _find_kth(v1->l, v2->l, l, (l + r) / 2, k);
        return _find_kth(v1->r, v2->r, (l + r) / 2, r, k - left_size);
    }

    int32_t find_kth(Node *v1, Node *v2, int32_t k) {
        return _find_kth(v1, v2, 0, size, k);
    }
}
int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    int32_t a1, vl, vm;
    cin >> a1 >> vl >> vm;
    vector<int32_t> nums(n);
    nums[0] = a1;
    for (int32_t i = 1; i < n; ++i) nums[i] = (1ll * nums[i - 1] * vl + vm) % mod;
    vector<int32_t> cls = nums;
    sort(cls.begin(), cls.end());
    for (auto &v: nums) v = distance(cls.begin(), lower_bound(cls.begin(), cls.end(), v));
    vector<st::Node *> vers(n + 1);
    vers[0] = st::assign(n);
    for (int32_t i = 0; i < n; ++i) vers[i + 1] = st::add(vers[i], nums[i], 1);
    int32_t b_cnt;
    cin >> b_cnt;
    uint64_t res = 0;
    for (int32_t _ = 0, G, x, lx, mx, y, ly, my, k, lk, mk; _ < b_cnt; ++_) {
        cin >> G >> x >> lx >> mx >> y >> ly >> my >> k >> lk >> mk;
        --x, --y, --k;
        int32_t i = std::min(x, y), j = std::max(x, y);
        res += cls[st::find_kth(vers[i], vers[j + 1], k)];
        for (int32_t g = 2; g <= G; ++g) {
            x = (1ll * i * lx + mx) % n;
            y = (1ll * j * ly + my) % n;
            if (x < y) i = x, j = y;
            else i = y, j = x;
            k = (1ll * k * lk + mk) % (j - i + 1);
            res += cls[st::find_kth(vers[i], vers[j + 1], k)];
        }
    }
    cout << res << "\n";
    return 0;
}

//
//struct Que {
//    int32_t a, b, k;
//};
//
//using Ques = pair<vector<int32_t>, vector<Que>>;

//
//namespace Clever {
//    vector<int32_t> sol(const Ques &_ques) {
//        auto [nums, ques] = _ques;
//        vector<int32_t> cls = nums;
//        sort(cls.begin(), cls.end());
//        for (auto &v: nums) v = distance(cls.begin(), lower_bound(cls.begin(), cls.end(), v));
//        st::used_cnt = 0;
//        vector<st::Node *> vers(nums.size() + 1);
//        vers[0] = st::assign(nums.size());
//        for (int32_t i = 0; i < nums.size(); ++i) vers[i + 1] = st::add(vers[i], nums[i], 1);
//        vector<int32_t> res;
//        res.reserve(ques.size());
//        for (auto [a, b, k]: ques) {
//            res.push_back(cls[st::find_kth(vers[a], vers[b], k)]);
//        }
//        return res;
//    }
//};
//
//namespace Stupid {
//    vector<int32_t> sol(const Ques &_ques) {
//        auto [nums, ques] = _ques;
//        vector<int32_t> res;
//        for (auto [a, b, k]: ques) {
//            multiset<int32_t> ms;
//            for (int32_t i = a; i < b; ++i) ms.insert(nums[i]);
//            res.push_back(*next(ms.begin(), k));
//        }
//        return res;
//    }
//}
//
//namespace Test {
//    uint32_t seed = 4285893;
//    mt19937 rng(seed);
//
//    int32_t randint(int32_t a, int32_t b) {
//        return uniform_int_distribution(a, b)(rng);
//    }
//
//    Ques gen_input() {
//        int32_t n = randint(1, 10);
//        vector<int32_t> nums(n);
//        for (auto &v: nums) v = randint(1, 10);
//        int32_t q = randint(1, 10);
//        vector<Que> ques(q);
//        for (auto &[a, b, k]: ques) {
//            a = randint(0, n - 1);
//            b = randint(a + 1, n);
//            k = randint(0, b - a - 1);
//        }
//        return {nums, ques};
//    }
//
//    void print_input(const Ques &ques) {
//        cout << ques.first.size() << "\n";
//        for (auto v: ques.first) cout << v << " ";
//        cout << "\n";
//        cout << ques.second.size() << "\n";
//        for (auto [a, b, k]: ques.second) cout << a + 1 << " " << b << " " << k + 1 << "\n";
//        cout << "\n";
//    }
//
//    void print_output(const vector<int32_t> &res) {
//        for (auto v: res) cout << v << "\n";
//        cout << "\n";
//    }
//
//    void Test() {
//        while (true) {
//            auto inp = gen_input();
//            auto r1 = Stupid::sol(inp), r2 = Clever::sol(inp);
//            if (r1 != r2) {
//                cout << "Input:\n";
//                print_input(inp);
//                cout << "Stupid:\n";
//                print_output(r1);
//                cout << "Clever:\n";
//                print_output(r2);
//                break;
//            }
//        }
//    }
//
//    void inp_test() {
//        int32_t n, q;
//        cin >> n;
//        vector<int32_t> nums(n);
//        for (auto &v: nums) cin >> v;
//        cin >> q;
//        vector<Que> ques(q);
//        for (auto &[a, b, k]: ques) cin >> a >> b >> k, --a, --k;
//        auto r = Clever::sol({nums, ques});
//        print_output(r);
//    }
//}
