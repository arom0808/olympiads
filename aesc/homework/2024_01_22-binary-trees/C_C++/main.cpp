#include <iostream>
#include <algorithm>

using namespace std;

constexpr int maxn = 4e5;

struct Req {
    int a, b, c;
};

Req reqs[maxn];
int zpv[maxn * 2 + 1];
int zpv_cnt = 0;

int get_zip_pos(int val) {
    return lower_bound(zpv, zpv + zpv_cnt, val) - zpv;
}

namespace ST {
    struct Data {
        int max_pref_len = 0, max_suf_len = 0, max_center_len = 0;

        void set_len(int len) {
            max_pref_len = max_suf_len = max_center_len = len;
        }

        explicit Data(int len = 0) {
            max_pref_len = max_suf_len = max_center_len = len;
        }
    };

    Data tree[maxn * 8];

    void upd_data(const Data &l, int l_len, const Data &r, int r_len, Data &res) {
        if (l.max_pref_len == l_len) res.max_pref_len = l_len + r.max_pref_len;
        else res.max_pref_len = l.max_pref_len;
        if (r.max_suf_len == r_len) res.max_suf_len = r_len + l.max_suf_len;
        else res.max_suf_len = r.max_suf_len;
        res.max_center_len = res.max_pref_len;
        res.max_center_len = std::max(res.max_center_len, res.max_pref_len);
        res.max_center_len = std::max(res.max_center_len, l.max_center_len);
        res.max_center_len = std::max(res.max_center_len, r.max_center_len);
        res.max_center_len = std::max(res.max_center_len, l.max_suf_len + r.max_pref_len);
    }

    void upd_from_children(int v, int l, int r) {
        if (r - l <= 1) return;
        int m = (l + r) >> 1;
        upd_data(tree[v << 1], zpv[m] - zpv[l], tree[v << 1 | 1], zpv[r] - zpv[m], tree[v]);
    }

    void _init(int v, int l, int r) {
        if (r - l == 1) {
            tree[v].set_len(zpv[r] - zpv[l]);
            return;
        }
        int m = (l + r) >> 1;
        _init(v << 1, l, m);
        _init(v << 1 | 1, m, r);
        upd_from_children(v, l, r);
    }

    void init() {
        _init(1, 0, zpv_cnt);
    }

    void _invert_val(int v, int l, int r, int z_pos) {
        if (l > z_pos || z_pos >= r) return;
        if (r - l == 1) {
            if (tree[v].max_pref_len) {
                tree[v].max_pref_len = 0;
                tree[v].max_suf_len = tree[v].max_center_len = zpv[r] - zpv[l] - 1;
            } else {
                tree[v].set_len(zpv[r] - zpv[l]);
            }
            return;
        }
        int m = (l + r) >> 1;
        _invert_val(v << 1, l, m, z_pos);
        _invert_val(v << 1 | 1, m, r, z_pos);
        upd_from_children(v, l, r);
    }

    void invert_val(int pos) {
        _invert_val(1, 0, zpv_cnt, get_zip_pos(pos));
    }

    Data _get_ans(int v, int l, int r, int a, int b) {
        if (l >= b || a >= r) return Data(0);
        if (a <= l && r <= b) return tree[v];
        int m = (l + r) >> 1;
        Data res;
        upd_data(_get_ans(v << 1, l, m, a, b), max(min(zpv[m], zpv[b]) - max(zpv[l], zpv[a]), 0),
                 _get_ans(v << 1 | 1, m, r, a, b), max(min(zpv[r], zpv[b]) - max(zpv[a], zpv[m]), 0), res);
        return res;
    }

    int get_ans(int a, int b) {
        return _get_ans(1, 0, zpv_cnt, get_zip_pos(a), get_zip_pos(b)).max_center_len;
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        if (c == 'A') {
            reqs[i].a = 0;
            cin >> reqs[i].b;
            zpv[zpv_cnt++] = reqs[i].b;
        } else {
            reqs[i].a = 1;
            cin >> reqs[i].b >> reqs[i].c, ++reqs[i].c;
            zpv[zpv_cnt++] = reqs[i].b, zpv[zpv_cnt++] = reqs[i].c;
        }
    }
    sort(zpv, zpv + zpv_cnt);
    zpv_cnt = unique(zpv, zpv + zpv_cnt) - zpv;
    zpv[zpv_cnt] = 1e9 + 1;
    ST::init();
    for (int i = 0; i < n; ++i) {
        if (reqs[i].a == 0) {
            ST::invert_val(reqs[i].b);
        } else {
            cout << ST::get_ans(reqs[i].b, reqs[i].c) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
