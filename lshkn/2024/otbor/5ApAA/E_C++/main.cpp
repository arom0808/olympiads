#include <iostream>
#include <vector>
#include <cstdint>
#include <bitset>

using namespace std;

bitset<1000> primes;

void primes_init() {
    for (int32_t i = 2; i < 1000; ++i) {
        primes.set(i);
        for (int32_t j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                primes.reset(i);
                break;
            }
        }
    }
}

class SegmentTree {
    struct Elem {
        bitset<1000> vals;
        int32_t change = 0;

        explicit Elem() = default;
    };

    int32_t size, m;
    vector<Elem> tree;
    bitset<1000> req_temp, first_m;

    void init_val(int32_t id, int32_t l, int32_t r, const vector<int32_t> &values) {
        if (l >= r) return;
        if (r - l == 1) {
            tree[id].vals.set(values[l] % m);
            return;
        }
        init_val(id * 2, l, (l + r) / 2, values);
        init_val(id * 2 + 1, (l + r) / 2, r, values);
        tree[id].vals = tree[id * 2].vals | tree[id * 2 + 1].vals;
    }

    void transfer_changes(int32_t id) {
        if (!tree[id].change) return;
        if (id * 2 + 1 < tree.size()) {
//            tree[id].change %= m;
//            for (int32_t i = 0; i < m; ++i) temp[(i + tree[id].change) % m] = tree[id * 2].vals[i];
//            tree[id * 2].vals = temp, tree[id * 2].change += tree[id].change;
//            for (int32_t i = 0; i < m; ++i) temp[(i + tree[id].change) % m] = tree[id * 2 + 1].vals[i];
//            tree[id * 2 + 1].vals = temp, tree[id * 2 + 1].change += tree[id].change;
            auto ch = tree[id].change %= m;
            auto &l = tree[id * 2], &r = tree[id * 2 + 1];
            l.vals = ((l.vals >> (m - ch)) | (l.vals << ch)) & first_m;
            l.change += ch;
            r.vals = ((r.vals >> (m - ch)) | (r.vals << ch)) & first_m;
            r.change += ch;
        }
        tree[id].change = 0;
    }

    void _add(int32_t id, int32_t l, int32_t r, int32_t req_l, int32_t req_r, int32_t val) {
        if (l >= r || r <= req_l || req_r <= l) return;
        if (req_l <= l && r <= req_r) {
            val %= m;
            auto &th = tree[id];
//            cout << th.vals << "\n";
//            cout << val << " " << m << "\n";
//            temp2 = (th.vals >> (m - val)) | (th.vals << val) & first_m;
            th.vals = (th.vals >> (m - val)) | (th.vals << val) & first_m;
            th.change += val;
//            for (int32_t i = 0; i < m; ++i) temp[(i + val) % m] = tree[id].vals[i];
//            tree[id].vals = temp, tree[id].change += val;
//            cout << temp.to_string() << "\n";
//            cout << temp2.to_string() << "\n\n";
//            cout.flush();
//            if (temp != temp2) throw std::runtime_error("Some fucking shit");
            return;
        }
        transfer_changes(id);
        _add(id * 2, l, (l + r) / 2, req_l, req_r, val);
        _add(id * 2 + 1, (l + r) / 2, r, req_l, req_r, val);
        tree[id].vals = tree[id * 2].vals | tree[id * 2 + 1].vals;
    }

    void _count_primes(int32_t id, int32_t l, int32_t r, int32_t req_l, int32_t req_r) {
        if (l >= r || r <= req_l || req_r <= l) return;
        transfer_changes(id);
        if (req_l <= l && r <= req_r) { req_temp |= tree[id].vals; }
        else {
            _count_primes(id * 2, l, (l + r) / 2, req_l, req_r);
            _count_primes(id * 2 + 1, (l + r) / 2, r, req_l, req_r);
        }
    }


public:
    SegmentTree(const vector<int32_t> &values, int32_t _m)
            : size(values.size()), m(_m), tree(values.size() * 4) {
        for (int32_t i = 0; i < m; ++i) first_m.set(i);
        primes &= first_m;
        init_val(1, 0, size, values);
    }

    void add(int32_t l, int32_t r, int32_t val) {
        _add(1, 0, size, l, r, val % m);
    }

    int32_t count_primes(int32_t l, int32_t r) {
        req_temp.reset();
        _count_primes(1, 0, size, l, r);
        req_temp &= primes;
        return req_temp.count();
    }
};

void dfs(int32_t v, const vector<vector<int32_t>> &g, vector<int32_t> &tin, vector<int32_t> &tout,
         int32_t &t, int32_t p = -1) {
    tin[v] = t++;
    for (auto u: g[v]) if (u != p) dfs(u, g, tin, tout, t, v);
    tout[v] = t;
}

void input_to_vector(int32_t &n, int32_t &m, vector<int32_t> &tin, vector<int32_t> &tout,
                     vector<int32_t> &start_seg_tree) {
    cin >> n >> m;
    vector<int32_t> start_values(n);
    for (auto &val: start_values) cin >> val;
    vector<vector<int32_t>> g(n);
    for (int32_t i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    tin.resize(n), tout.resize(n), start_seg_tree.resize(n);
    int32_t t = 0;
    dfs(0, g, tin, tout, t);
    for (int32_t i = 0; i < n; ++i) start_seg_tree[tin[i]] = start_values[i] % m;
}

namespace Test {
    void Test() {
        bitset<100> first_m;
        for (int32_t i = 0; i < 64; ++i) first_m.set(i);
        bitset<100> a(17058913289283582ull);
        cout << a.to_string() << "\n";
        bitset<100> b = ((a >> 3) | (a << (64 - 3)));
        cout << b.to_string() << "\n";
        cout << first_m.to_string() << "\n";
    }
}

int main() {
//    Test::Test();
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    primes_init();
    int32_t n, m;
    vector<int32_t> tin, tout, start_seg_tree;
    input_to_vector(n, m, tin, tout, start_seg_tree);
    SegmentTree st(start_seg_tree, m);
    int32_t q, t, u, a;
    cin >> q;
    for (int32_t i = 0; i < q; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> u >> a;
            st.add(tin[u - 1], tout[u - 1], a);
        } else {
            cin >> u;
            cout << st.count_primes(tin[u - 1], tout[u - 1]) << "\n";
        }
    }
    return 0;
}
