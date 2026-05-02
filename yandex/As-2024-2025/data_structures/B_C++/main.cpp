#include <iostream>

using namespace std;

const int32_t maxn = 5e5;

int32_t nums[maxn];

namespace SegTree {
    struct Node {
        int32_t pref_len, suf_len, center_len;
    };

    Node tree[maxn * 4];
    int32_t size;

    Node merge(Node a, Node b, int32_t a_start, int32_t a_len, int32_t b_len) {
        Node res;
        if (a.pref_len == a_len && nums[a_start + a_len - 1] == nums[a_start + a_len] && nums[a_start + a_len - 1] == 0)
            res.pref_len = a_len + b.pref_len;
        else res.pref_len = a.pref_len;
        res.center_len = res.pref_len;
        if (nums[a_start + a_len - 1] == nums[a_start + a_len] && a.suf_len + b.pref_len > res.center_len)
            res.center_len = a.suf_len + b.pref_len;
        if (b.suf_len == b_len && nums[a_start + a_len - 1] == nums[a_start + a_len] && nums[a_start + a_len - 1] == 0)
            res.suf_len = a.suf_len + b_len;
        else res.suf_len = b.suf_len;
        res.center_len = std::max(res.suf_len, res.center_len);
        res.center_len = std::max(res.center_len, a.center_len);
        res.center_len = std::max(res.center_len, b.center_len);
        return res;
    }

    void _init(int32_t v, int32_t l, int32_t r) {
        if (l >= r) return;
        if (r - l == 1) {
            if (nums[l] == 0) tree[v].pref_len = tree[v].suf_len = tree[v].center_len = 1;
            else tree[v].pref_len = tree[v].suf_len = tree[v].center_len = 0;
            return;
        }
        _init(v * 2, l, (l + r) / 2);
        _init(v * 2 + 1, (l + r) / 2, r);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1], l, (l + r) / 2 - l, r - (l + r) / 2);
    }

    void _update(int32_t v, int32_t l, int32_t r, int32_t x) {
        if (l >= r || l > x || r <= x) return;
        if (r - l == 1) {
            if (nums[l] == 0) tree[v].pref_len = tree[v].suf_len = tree[v].center_len = 1;
            else tree[v].pref_len = tree[v].suf_len = tree[v].center_len = 0;
            return;
        }
        _update(v * 2, l, (l + r) / 2, x);
        _update(v * 2 + 1, (l + r) / 2, r, x);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1], l, (l + r) / 2 - l, r - (l + r) / 2);
    }

    Node _get_ans(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || l >= b || r <= a) return {0, 0, 0};
        if (a <= l && r <= b) return tree[v];
        if (b <= (l + r) / 2) return _get_ans(v * 2, l, (l + r) / 2, a, b);
        if (a >= (l + r) / 2) return _get_ans(v * 2 + 1, (l + r) / 2, r, a, b);
        return merge(_get_ans(v * 2, l, (l + r) / 2, a, b), _get_ans(v * 2 + 1, (l + r) / 2, r, a, b),
                     std::max(l, a), (l + r) / 2 - std::max(l, a), std::min(r, b) - (l + r) / 2);
    }

    void init(int32_t _size) {
        size = _size;
        _init(1, 0, size);
    }

    void update(int32_t x) {
        _update(1, 0, size, x);
    }

    int32_t get_ans(int32_t a, int32_t b) {
        return _get_ans(1, 0, size, a, b).center_len;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, m;
    cin >> n;
    for (int32_t i = 0; i < n; ++i) cin >> nums[i];
    SegTree::init(n);
    cin >> m;
    string temp_s;
    for (int32_t _ = 0, l, r, i, x; _ < m; ++_) {
        cin >> temp_s;
        if (temp_s == "QUERY") {
            cin >> l >> r;
            cout << SegTree::get_ans(l - 1, r) << "\n";
        } else {
            cin >> i >> x;
            nums[i - 1] = x;
            SegTree::update(i - 1);
        }
    }
    return 0;
}
