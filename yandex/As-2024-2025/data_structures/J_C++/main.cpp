#include <iostream>
#include <vector>

using namespace std;

const int32_t maxn = 2e5;
const int64_t inf = 2e18;

namespace SegTree {
    struct Node {
        int32_t norm_cnt;
        int64_t change, min_val, min_vmi, min_vpi;

        void init() {
            norm_cnt = 0, change = 0, min_val = inf, min_vmi = inf, min_vpi = inf;
        }

        Node operator+(const Node &rhs) const {
            return {
                norm_cnt + rhs.norm_cnt, 0, std::min(min_val, rhs.min_val), std::min(min_vmi, rhs.min_vmi),
                std::min(min_vpi, rhs.min_vpi)
            };
        }

        void operator+=(int64_t ch_v) {
            change += ch_v, min_val += ch_v, min_vmi += ch_v, min_vpi += ch_v;
        }
    };

    Node tree[maxn * 4];
    int32_t size;

    void _init(int32_t v, int32_t l, int32_t r) {
        if (l >= r) return;
        tree[v].init();
        if (r - l == 1) return;
        _init(v * 2, l, (l + r) / 2);
        _init(v * 2 + 1, (l + r) / 2, r);
    }

    void transfer_changes(int32_t v, int32_t l, int32_t r) {
        if (!tree[v].change) return;
        if (r - l > 1) {
            if (tree[v * 2].norm_cnt) tree[v * 2] += tree[v].change;
            if (tree[v * 2 + 1].norm_cnt) tree[v * 2 + 1] += tree[v].change;
        }
        tree[v].change = 0;
    }

    void _add(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b, int64_t val) {
        if (l >= r || l >= b || a >= r || !tree[v].norm_cnt) return;
        if (a <= l && r <= b) {
            tree[v] += val;
            return;
        }
        transfer_changes(v, l, r);
        _add(v * 2, l, (l + r) / 2, a, b, val);
        _add(v * 2 + 1, (l + r) / 2, r, a, b, val);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    void _min_assign(int32_t v, int32_t l, int32_t r, int32_t pos, int64_t val) {
        if (l >= r || l >= pos + 1 || pos >= r) return;
        if (pos <= l && r <= pos + 1) {
            if (!tree[v].norm_cnt || tree[v].min_val > val) tree[v].min_val = val;
            tree[v].norm_cnt = 1, tree[v].change = 0, tree[v].min_vmi = tree[v].min_val - l,
                    tree[v].min_vpi = tree[v].min_val + l;
            return;
        }
        transfer_changes(v, l, r);
        _min_assign(v * 2, l, (l + r) / 2, pos, val);
        _min_assign(v * 2 + 1, (l + r) / 2, r, pos, val);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    int64_t _min_val(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || l >= b || a >= r || !tree[v].norm_cnt) return inf;
        if (a <= l && r <= b) return tree[v].min_val;
        transfer_changes(v, l, r);
        return std::min(_min_val(v * 2, l, (l + r) / 2, a, b), _min_val(v * 2 + 1, (l + r) / 2, r, a, b));
    }

    int64_t _min_vmi(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || l >= b || a >= r || !tree[v].norm_cnt) return inf;
        if (a <= l && r <= b) return tree[v].min_vmi;
        transfer_changes(v, l, r);
        return std::min(_min_vmi(v * 2, l, (l + r) / 2, a, b), _min_vmi(v * 2 + 1, (l + r) / 2, r, a, b));
    }

    int64_t _min_vpi(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || l >= b || a >= r || !tree[v].norm_cnt) return inf;
        if (a <= l && r <= b) return tree[v].min_vpi;
        transfer_changes(v, l, r);
        return std::min(_min_vpi(v * 2, l, (l + r) / 2, a, b), _min_vpi(v * 2 + 1, (l + r) / 2, r, a, b));
    }

    void init(int32_t _size) {
        size = _size;
        _init(1, 0, size);
    }

    void add(int32_t a, int32_t b, int64_t val) {
        _add(1, 0, size, a, b, val);
    }

    void min_assign(int32_t pos, int64_t val) {
        _min_assign(1, 0, size, pos, val);
    }

    int64_t min_val(int32_t a, int32_t b) {
        return _min_val(1, 0, size, a, b);
    }

    int64_t min_vmi(int32_t a, int32_t b) {
        return _min_vmi(1, 0, size, a, b);
    }

    int64_t min_vpi(int32_t a, int32_t b) {
        return _min_vpi(1, 0, size, a, b);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, q, a, b;
    cin >> n >> q >> a >> b, --a, --b;
    SegTree::init(n);
    for (int32_t i = 0, x, pre_x; i < q; ++i, pre_x = x) {
        cin >> x, --x;
        if (i == 0) {
            SegTree::min_assign(a, std::abs(b - x));
            SegTree::min_assign(b, std::abs(a - x));
            continue;
        }
        int64_t lk = SegTree::min_vmi(0, x), rk = SegTree::min_vpi(x, n);
        int64_t riv = inf;
        if (lk != inf) riv = std::min<int64_t>(riv, lk + x);
        if (rk != inf) riv = std::min<int64_t>(riv, rk - x);
        SegTree::add(0, n, std::abs(x - pre_x));
        if (riv != inf) SegTree::min_assign(pre_x, riv);
    }
    cout << SegTree::min_val(0, n) << "\n";
    return 0;
}
