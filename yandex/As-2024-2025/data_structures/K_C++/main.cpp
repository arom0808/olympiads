#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int32_t maxn = 1e5 + 1;

namespace SegTree {
    struct Node {
        int32_t val, change;

        void make_change(int32_t ch) {
            val += ch, change += ch;
        }

        void init() {
            val = 0, change = 0;
        }

        Node operator+(const Node &rhs) const {
            return {val + rhs.val, 0};
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
        if (l >= r || !tree[v].change) return;
        if (r - l > 1) {
            tree[v * 2].make_change(tree[v].change);
            tree[v * 2 + 1].make_change(tree[v].change);
        }
        tree[v].change = 0;
    }

    void _add(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b, int32_t val) {
        if (l >= r || l >= b || a >= r) return;
        if (a <= l && r <= b) {
            tree[v].make_change(val);
            return;
        }
        transfer_changes(v, l, r);
        _add(v * 2, l, (l + r) / 2, a, b, val);
        _add(v * 2 + 1, (l + r) / 2, r, a, b, val);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    int32_t _get_val(int32_t v, int32_t l, int32_t r, int32_t pos) {
        if (l == pos && r == pos + 1) return tree[v].val;
        transfer_changes(v, l, r);
        if (pos < (l + r) / 2) return _get_val(v * 2, l, (l + r) / 2, pos);
        return _get_val(v * 2 + 1, (l + r) / 2, r, pos);
    }

    void init(int32_t _size) {
        size = _size;
        _init(1, 0, size);
    }

    void add(int32_t a, int32_t b, int32_t val) {
        _add(1, 0, size, a, b, val);
    }

    int32_t get_val(int32_t pos) {
        return _get_val(1, 0, size, pos);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, m;
    cin >> n >> m;
    SegTree::init(m + 1);
    vector<pair<int32_t, int32_t> > segs(n);
    for (auto &[l,r]: segs) cin >> l >> r;
    sort(segs.begin(), segs.end(), [](const pair<int32_t, int32_t> &a, const pair<int32_t, int32_t> &b) {
        return a.second - a.first < b.second - b.first;
    });
    int32_t cnt_geq = n;
    auto s_it = segs.begin();
    for (int32_t d = 1; d <= m; ++d) {
        for (; s_it != segs.end() && s_it->second - s_it->first + 1 < d; --cnt_geq, ++s_it)
            SegTree::add(s_it->first, s_it->second + 1, 1);
        int32_t add_num = 0;
        for (int32_t i = 0; i <= m; i += d) add_num += SegTree::get_val(i);
        cout << cnt_geq + add_num << "\n";
    }
    return 0;
}
