#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

template<typename T>
class FenwickTree {
private:
//    static inline int32_t f(int32_t x) { return x - (x & (-x)) + 1; }

    vector<T> tree;

public:
    T sum(int32_t r) {
        T res = 0;
        for (; r > 0; r -= r & -r) res += tree[r];
        return res;
    }

    T sum(int32_t l, int32_t r) { return sum(r) - sum(l); }

    void add(int32_t pos, T val) { for (++pos; pos < tree.size(); pos += pos & -pos) tree[pos] += val; }

    void set(int32_t pos, T val) { add(pos, val - sum(pos, pos + 1)); }

    explicit FenwickTree(int32_t n) : tree(n + 1, 0) {}

    explicit FenwickTree(const vector<T> &vec) : tree(vec.size() + 1, 0) {
        for (uint32_t i = 0; i < vec.size(); ++i) add(i, vec[i]);
    }
};

struct Act {
    bool type;
    uint32_t a, b, c, i;

    bool operator<(const Act &other) const {
        if (c != other.c) return c < other.c;
        return type && !other.type;
    }
};

const uint32_t c15 = 1.5e6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint32_t n, q;
    cin >> n >> q;
    vector<uint32_t> rz(n);
    for (auto &z: rz) cin >> z;
    vector<uint32_t> from(c15 + 2);
    iota(from.begin(), from.end(), 0);
    vector<Act> acts;
    acts.reserve(q + n);
    uint32_t r2c = 0;
    for (uint32_t i = 0, t, x, l, r, y; i < q; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> x;
            from[x + 1] = from[x];
        } else {
            cin >> l >> r >> y;
            acts.emplace_back(true, l - 1, r - 1, from[y + 1], r2c++);
        }
    }
    for (uint32_t i = 0; i < n; ++i) acts.emplace_back(false, i, 0, rz[i], 0);
    sort(acts.begin(), acts.end());
    FenwickTree<uint32_t> ft(n);
    vector<uint32_t> ans(r2c);
    for (auto [type, a, b, c, i]: acts) {
        if (!type) ft.set(a, 1);
        else ans[i] = ft.sum(a, b + 1);
    }
    for (auto a: ans) cout << a << "\n";
    return 0;
}

