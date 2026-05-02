#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int32_t maxn = 5e5 + 2;
constexpr int32_t inf = 1e9;

namespace SegTree {
    struct Node {
        int32_t cnt_norm, change, max_val;

        void init() {
            cnt_norm = 0, change = 0, max_val = -inf;
        }

        Node operator+(const Node &rhs) const {
            return {cnt_norm + rhs.cnt_norm, 0, std::max(max_val, rhs.max_val)};
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
        if (r - l > 1 && tree[v].cnt_norm) {
            if (tree[v * 2].cnt_norm) tree[v * 2].change += tree[v].change, tree[v * 2].max_val += tree[v].change;
            if (tree[v * 2 + 1].cnt_norm)
                tree[v * 2 + 1].change += tree[v].change, tree[v * 2 + 1].max_val += tree[v].change;
        }
        tree[v].change = 0;
    }

    int32_t _cnt_norm_val(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || l >= b || a >= r) return 0;
        if (a <= l && r <= b) return tree[v].cnt_norm;
        transfer_changes(v, l, r);
        return _cnt_norm_val(v * 2, l, (l + r) / 2, a, b) + _cnt_norm_val(v * 2 + 1, (l + r) / 2, r, a, b);
    }

    int32_t _first_greater_zero(int32_t v, int32_t l, int32_t r) {
        if (tree[v].max_val <= 0) return r;
        if (r - l == 1) return l;
        transfer_changes(v, l, r);
        if (tree[v * 2].max_val > 0) return _first_greater_zero(v * 2, l, (l + r) / 2);
        return _first_greater_zero(v * 2 + 1, (l + r) / 2, r);
    }

    void _add(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b, int32_t val) {
        if (l >= r || l >= b || a >= r || !tree[v].cnt_norm) return;
        if (a <= l && r <= b) {
            tree[v].max_val += val, tree[v].change += val;
            return;
        }
        transfer_changes(v, l, r);
        _add(v * 2, l, (l + r) / 2, a, b, val);
        _add(v * 2 + 1, (l + r) / 2, r, a, b, val);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    void _set_val(int32_t v, int32_t l, int32_t r, int32_t pos, bool norm, int32_t val) {
        if (l >= r || l >= pos + 1 || pos >= r) return;
        if (l == pos && r == pos + 1) {
            if (norm) tree[v].cnt_norm = 1, tree[v].max_val = val;
            else tree[v].cnt_norm = 0, tree[v].max_val = -inf;
            return;
        }
        transfer_changes(v, l, r);
        _set_val(v * 2, l, (l + r) / 2, pos, norm, val);
        _set_val(v * 2 + 1, (l + r) / 2, r, pos, norm, val);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    void init(int32_t _size) {
        size = _size;
        _init(1, 0, size);
    }

    int32_t cnt_norm_val(int32_t a, int32_t b) {
        return _cnt_norm_val(1, 0, size, a, b);
    }

    int32_t first_greater_zero() {
        return _first_greater_zero(1, 0, size);
    }

    void add(int32_t a, int32_t b, int32_t val) {
        _add(1, 0, size, a, b, val);
    }

    void set_val(int32_t pos, bool norm, int32_t val) {
        _set_val(1, 0, size, pos, norm, val);
    }
}

pair<int32_t, int32_t> a_pos_cnt[maxn];
int32_t raw_a_cnt[maxn], raw_acts[maxn];
int32_t n;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n, ++n;
    vector<int32_t> raw_as;
    char c;
    raw_acts[0] = 0, ++raw_a_cnt[0], raw_as.push_back(0);
    for (int32_t i = 1, a; i < n; ++i) {
        cin >> c >> a;
        if (c == '+') raw_acts[i] = a, ++raw_a_cnt[a], raw_as.push_back(a);
        else raw_acts[i] = -a;
    }
    sort(raw_as.begin(), raw_as.end());;
    raw_as.erase(unique(raw_as.begin(), raw_as.end()), raw_as.end());
    int32_t full_cnt = 0;
    for (int32_t i = 0; i < raw_as.size(); ++i) {
        a_pos_cnt[raw_as[i]] = {full_cnt, 0};
        full_cnt += raw_a_cnt[raw_as[i]];
    }
    SegTree::init(full_cnt);
    for (int32_t i = 0; i < n; ++i) {
        int32_t act = raw_acts[i];
        if (act >= 0) {
            int32_t pos = a_pos_cnt[act].first + a_pos_cnt[act].second;
            SegTree::set_val(pos, true, act - SegTree::cnt_norm_val(0, pos));
            SegTree::add(pos + 1, full_cnt, -1);
            ++a_pos_cnt[act].second;
        } else {
            act = -act;
            int32_t pos = a_pos_cnt[act].first + a_pos_cnt[act].second - 1;
            SegTree::set_val(pos, false, -inf);
            SegTree::add(pos + 1, full_cnt, 1);
            --a_pos_cnt[act].second;
        }
        if (i) cout << SegTree::cnt_norm_val(0, SegTree::first_greater_zero()) << "\n";
    }
    return 0;
}
