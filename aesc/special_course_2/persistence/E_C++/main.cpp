#include <iostream>
#include <map>
#include <functional>
#include <cstdint>

using namespace std;

namespace st {
    struct Node {
        int32_t val = 0;
        Node *l = nullptr, *r = nullptr;
    };

    const int32_t max_st_size = 1e7;

    Node tree[max_st_size];
    int32_t used_cnt = 0;
    int32_t size;

    void init(Node *&v, int32_t l, int32_t r, const function<int32_t(int32_t)> &f) {
        if (l >= r) return;
        if (!v) v = &tree[used_cnt++];
        if (r - l == 1) {
            v->val = f(l);
        } else {
            init(v->l, l, (l + r) / 2, f);
            init(v->r, (l + r) / 2, r, f);
        }
    }

    Node *assign(int32_t n, const function<int32_t(int32_t)> &f) {
        size = n;
        Node *root = nullptr;
        init(root, 0, size, f);
        return root;
    }

    Node *_set(Node *v, int32_t l, int32_t r, int32_t pos, int32_t val) {
        if (l >= r || r <= pos || pos < l) return v;
        Node *nv = &tree[used_cnt++];
        if (r - l == 1) {
            nv->val = val;
        } else {
            nv->l = _set(v->l, l, (l + r) / 2, pos, val);
            nv->r = _set(v->r, (l + r) / 2, r, pos, val);
        }
        return nv;
    }

    int32_t _val(Node *v, int32_t l, int32_t r, int32_t pos) {
        if (l == pos && r == pos + 1) return v->val;
        if (pos < (l + r) / 2) return _val(v->l, l, (l + r) / 2, pos);
        return _val(v->r, (l + r) / 2, r, pos);
    }

    Node *set(Node *root, int32_t pos, int32_t val) {
        return _set(root, 0, size, pos, val);
    }

    int32_t val(Node *root, int32_t pos) {
        return _val(root, 0, size, pos);
    }
};

namespace DSU {
    map<int32_t, st::Node *> p_rs, h_rs;

    void assign(int32_t n) {
        p_rs.emplace(0, st::assign(n, [](int32_t i) { return i; }));
        h_rs.emplace(0, st::assign(n, [](int32_t i) { return 1; }));
    }

    int32_t gp(st::Node *par_root, int32_t a) {
        int32_t pa = a;
        while (st::val(par_root, pa) != pa) pa = st::val(par_root, pa);
        return pa;
    }

    void join(int32_t pre_id, int32_t now_id, int32_t a, int32_t b) {
        st::Node *p_r = p_rs[pre_id], *h_r = h_rs[pre_id];
        a = gp(p_r, a), b = gp(p_r, b);
        if (a != b) {
            if (st::val(h_r, a) < st::val(h_r, b)) swap(a, b);
            p_r = st::set(p_r, b, a);
            h_r = st::set(h_r, a, std::max(st::val(h_r, a), st::val(h_r, b) + 1));
        }
        p_rs.emplace(now_id, p_r);
        h_rs.emplace(now_id, h_r);
    }

    bool is_equal_set(int32_t id, int32_t a, int32_t b) {
        st::Node *p_r = p_rs[id];
        return gp(p_r, a) == gp(p_r, b);
    }
}


int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, k;
    cin >> n >> k;
    DSU::assign(n);
    char tc;
    for (int32_t i = 1, a, b, c; i <= k; ++i) {
        cin >> tc >> a >> b >> c, --b, --c;
        if (tc == '+') DSU::join(a, i, b, c);
        else cout << (DSU::is_equal_set(a, b, c) ? "YES" : "NO") << endl;
    }
    return 0;
}


//namespace Test {
//    uint32_t seed = 1242525;
//    mt19937 rng(seed);
//
//    int32_t randint(int32_t a, int32_t b) {
//        return uniform_int_distribution(a, b)(rng);
//    }
//
//    pair<int32_t, vector<tuple<bool, int32_t, int32_t, int32_t>>> gen_inp() {
//        int32_t n = randint(1, 10);
//        int32_t q = randint(1, 10);
//        vector<tuple<bool, int32_t, int32_t, int32_t>> ques(q);
//        vector<int32_t> vers{0};
//        int32_t i = 1;
//        for (auto &[t, id, l, r]: ques) {
//            id = vers[randint(0, vers.size() - 1)];
//            t = randint(0, 1);
//            l = randint(0, n - 1), r = randint(0, n - 1);
//            if (t) vers.push_back(i);
//            ++i;
//        }
//        return {n, ques};
//    }
//
//    void print_inp(const pair<int32_t, vector<tuple<bool, int32_t, int32_t, int32_t>>> &inp) {
//        cout << inp.first << " " << inp.second.size() << "\n";
//        for (auto [t, id, l, r]: inp.second) {
//            cout << (t ? "+" : "?") << " " << id << " " << l + 1 << " " << r + 1 << "\n";
//        }
//        cout << endl;
//    }
//
//    void Test() {
//        while (true) {
//            auto [n, ques] = gen_inp();
//            st::used_cnt = 0;
//            DSU::p_rs.clear(), DSU::h_rs.clear();
//            DSU::assign(n);
//            print_inp({n, ques});
//            int32_t i = 1;
//            for (auto [t, id, l, r]: ques) {
//                if (t) DSU::join(id, i, l, r);
//                else cout << (DSU::is_equal_set(id, l, r) ? "YES" : "NO") << endl;
//                ++i;
//            }
//        }
//    }
//}