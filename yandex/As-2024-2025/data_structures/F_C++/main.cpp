#include <iostream>
#include <vector>

using namespace std;

const int32_t maxn = 1e5;

namespace Hash {
    template<uint64_t M>
    struct HV {
        uint64_t val;

        HV<M> operator+(const HV<M> &other) const {
            if (val + other.val > M) return {val + other.val - M};
            return {val + other.val};
        }

        HV<M> operator-(const HV<M> &other) const {
            if (val < other.val) return val + M - other.val;
            return val - other.val;
        }

        HV<M> operator*(const HV<M> &other) const {
            if (M) return {val * other.val % M};
            return {val * other.val};
        }

        HV<M> operator*(uint64_t other) const {
            if (M) return HV<M>(val * other % M);
            return HV<M>(val * other);
        }

        bool operator==(const HV<M> &other) const {
            return val == other.val;
        }
    };

    constexpr uint64_t P = 100019, M1 = 1e9 + 7, M2 = 0;
    HV<M1> ps1[maxn + 1], ps1_ps[maxn + 2];
    HV<M2> ps2[maxn + 1], ps2_ps[maxn + 2];

    void init() {
        ps1_ps[0].val = ps2_ps[0].val = 0;
        ps1[0].val = ps2[0].val = ps1_ps[1].val = ps2_ps[1].val = 1;
        for (int i = 1; i <= maxn; ++i) {
            ps1[i] = ps1[i - 1] * P;
            ps2[i] = ps2[i - 1] * P;
            ps1_ps[i + 1] = ps1_ps[i] + ps1[i];
            ps2_ps[i + 1] = ps2_ps[i] + ps2[i];
        }
    }

    struct DHV {
        HV<M1> v1;
        HV<M2> v2;

        DHV mul_ps_pow(int32_t y) {
            return {v1 * ps1[y], v2 * ps2[y]};
        }

        DHV operator+(const DHV &other) const {
            return {v1 + other.v1, v2 + other.v2};
        }

        DHV operator*(uint64_t other) const {
            return {v1 * other, v2 * other};
        }

        bool operator==(const DHV &other) const {
            return v1 == other.v1 && v2 == other.v2;
        }

        static DHV ps_pref_sum(int32_t cnt) {
            return {ps1_ps[cnt], ps2_ps[cnt]};
        }

        static DHV from_val(int32_t val) {
            return {HV<M1>(val), HV<M2>(val)};
        }

        static DHV concat(DHV a, int32_t a_len, DHV b) {
            return a + b.mul_ps_pow(a_len);
        }
    };
}

namespace SegTree {
    struct Node {
        Hash::DHV hash;
        int32_t set_change;

        void init() {
            set_change = -1;
        }
    };

    Node tree[maxn * 4];
    int32_t size;

    void _init(int32_t v, int32_t l, int32_t r, const vector<int32_t> &vals) {
        if (l >= r) return;
        tree[v].init();
        if (r - l == 1) {
            tree[v].hash = Hash::DHV::from_val(vals[l]);
            return;
        }
        _init(v * 2, l, (l + r) / 2, vals);
        _init(v * 2 + 1, (l + r) / 2, r, vals);
        tree[v].hash = Hash::DHV::concat(tree[v * 2].hash, (l + r) / 2 - l, tree[v * 2 + 1].hash);
    }

    void transfer_changes(int32_t v, int32_t l, int32_t r) {
        if (tree[v].set_change == -1) return;
        if (r - l > 1) {
            tree[v * 2].hash = Hash::DHV::ps_pref_sum((l + r) / 2 - l) * tree[v].set_change;
            tree[v * 2 + 1].hash = Hash::DHV::ps_pref_sum(r - (l + r) / 2) * tree[v].set_change;
            tree[v * 2].set_change = tree[v * 2 + 1].set_change = tree[v].set_change;
        }
        tree[v].set_change = -1;
    }

    void _set_val(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b, int32_t val) {
        if (l >= r || l >= b || a >= r) return;
        transfer_changes(v, l, r);
        if (a <= l && r <= b) {
            tree[v].hash = Hash::DHV::ps_pref_sum(r - l) * val;
            tree[v].set_change = val;
            return;
        }
        _set_val(v * 2, l, (l + r) / 2, a, b, val);
        _set_val(v * 2 + 1, (l + r) / 2, r, a, b, val);
        tree[v].hash = Hash::DHV::concat(tree[v * 2].hash, (l + r) / 2 - l, tree[v * 2 + 1].hash);
    }

    Hash::DHV _get_hash(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || l >= b || a >= r) return {0, 0};
        transfer_changes(v, l, r);
        if (a <= l && r <= b) return tree[v].hash;
        if (b <= (l + r) / 2) return _get_hash(v * 2, l, (l + r) / 2, a, b);
        if (a >= (l + r) / 2) return _get_hash(v * 2 + 1, (l + r) / 2, r, a, b);
        return Hash::DHV::concat(_get_hash(v * 2, l, (l + r) / 2, a, b), (l + r) / 2 - std::max(a, l),
                                 _get_hash(v * 2 + 1, (l + r) / 2, r, a, b));
    }

    void init(int32_t _size, const vector<int32_t> &vals) {
        size = _size;
        _init(1, 0, size, vals);
    }

    void set_val(int32_t a, int32_t b, int32_t val) {
        _set_val(1, 0, size, a, b, val);
    }

    Hash::DHV get_hash(int32_t a, int32_t b) {
        return _get_hash(1, 0, size, a, b);
    }
}

int main() {
    Hash::init();
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, m;
    cin >> n;
    vector<int32_t> vals(n);
    for (auto &el: vals) cin >> el, --el;
    SegTree::init(n, vals);
    cin >> m;
    for (int32_t i = 0, q, l, r, k; i < m; ++i) {
        cin >> q >> l >> r >> k;
        if (!q) SegTree::set_val(l - 1, r, k - 1);
        else {
            if (SegTree::get_hash(l - 1, l - 1 + k) == SegTree::get_hash(r - 1, r - 1 + k)) cout << "+";
            else cout << "-";
        }
    }
    return 0;
}
