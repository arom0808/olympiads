#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 1e6, inf = 1e9;

int heroes[maxn];
int near_eq_right[maxn];
int near_dupl_right[maxn];
int near_greater_right[maxn];
int last_pos_by_hero[maxn];
vector<int> temp_vec;

namespace ST {
    struct Node {
        int min_val, min_cnt;
        int change;
        int change_progr;

        void init() {
            min_val = 0, min_cnt = 1;
            change = 0;
            change_progr = -1;
        }

        void set_progr(int l, int r, int start_val) {
            min_val = start_val - (r - l) + 1;
            min_cnt = 1;
            change = 0;
            change_progr = start_val;
        }

        void add(int val) {
            min_val += val;
            change += val;
        }
    };

    int size;
    Node tree[maxn * 4];

    void push(int v, int l, int r) {
        if (tree[v].change_progr >= 0) {
            if (r - l > 1) {
                tree[v * 2].set_progr(l, (l + r) / 2, tree[v].change_progr);
                tree[v * 2 + 1].set_progr((l + r) / 2, r, tree[v].change_progr - ((l + r) / 2 - l));
            }
            tree[v].change_progr = -1;
        }
        if (tree[v].change) {
            if (r - l > 1) {
                tree[v * 2].add(tree[v].change);
                tree[v * 2 + 1].add(tree[v].change);
            }
            tree[v].change = 0;
        }
    }

    void upd_from_children(int v, int l, int r) {
        if (r - l <= 1) return;
        if (tree[v * 2].min_val < tree[v * 2 + 1].min_val)
            tree[v].min_val = tree[v * 2].min_val, tree[v].min_cnt = tree[v * 2].min_cnt;
        else if (tree[v * 2].min_val > tree[v * 2 + 1].min_val)
            tree[v].min_val = tree[v * 2 + 1].min_val, tree[v].min_cnt = tree[v * 2 + 1].min_cnt;
        else
            tree[v].min_val = tree[v * 2].min_val, tree[v].min_cnt = tree[v * 2].min_cnt + tree[v * 2 + 1].min_cnt;
    }

    void _init(int v, int l, int r) {
        tree[v].init();
        if (r - l == 1) return;
        _init(v * 2, l, (l + r) / 2);
        _init(v * 2 + 1, (l + r) / 2, r);
        upd_from_children(v, l, r);
    }

    void init(int _size) {
        size = _size;
        _init(1, 0, size);
    }

    void _set_progr(int v, int l, int r, int a, int b, int start_val) {
        if (l >= b || a >= r) return;
        if (a <= l && r <= b) {
            tree[v].set_progr(l, r, start_val - (l - a));
            return;
        }
        push(v, l, r);
        _set_progr(v * 2, l, (l + r) / 2, a, b, start_val);
        _set_progr(v * 2 + 1, (l + r) / 2, r, a, b, start_val);
        upd_from_children(v, l, r);
    }

    void set_progr(int a, int b, int start_val) {
        _set_progr(1, 0, size, a, b, start_val);
    }

    void _add(int v, int l, int r, int a, int b, int val) {
        if (l >= b || a >= r) return;
        if (a <= l && r <= b) {
            tree[v].add(val);
            return;
        }
        push(v, l, r);
        _add(v * 2, l, (l + r) / 2, a, b, val);
        _add(v * 2 + 1, (l + r) / 2, r, a, b, val);
        upd_from_children(v, l, r);
    }

    void add(int a, int b, int val) {
        _add(1, 0, size, a, b, val);
    }

    int _first_zero(int v, int l, int r, int a, int b) {
        if (l >= b || a >= r) return b;
        if (a <= l && r <= b && tree[v].min_val) return b;
        if (r - l == 1 && !tree[v].min_val) return l;
        push(v, l, r);
        int first_res = _first_zero(v * 2, l, (l + r) / 2, a, b);
        if (first_res < b) return first_res;
        return _first_zero(v * 2 + 1, (l + r) / 2, r, a, b);
    }

    int first_zero(int a, int b) {
        return _first_zero(1, 0, size, a, b);
    }

    pair<int, int> _get_min(int v, int l, int r, int a, int b) {
        if (l >= b || a >= r) return {inf, 0};
        if (a <= l && r <= b) return {tree[v].min_val, tree[v].min_cnt};
        push(v, l, r);
        pair<int, int> fv = _get_min(v * 2, l, (l + r) / 2, a, b), sv = _get_min(v * 2 + 1, (l + r) / 2, r, a, b);
        if (fv.first < sv.first) return fv;
        if (fv.first > sv.first) return sv;
        return {fv.first, fv.second + sv.second};
    }

    pair<int, int> get_min(int a, int b) {
        return _get_min(1, 0, size, a, b);
    }
}

int n, q;

struct Req {
    int id, l, x;

    bool operator<(const Req &other) const {
        return l > other.l;
    }
};

Req reqs[maxn];
pair<int, int> ans[maxn];

void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> heroes[i], --heroes[i];
    for (int i = 0; i < n; ++i) last_pos_by_hero[i] = n;
    for (int i = n - 1; i >= 0; --i) near_eq_right[i] = last_pos_by_hero[heroes[i]], last_pos_by_hero[heroes[i]] = i;
    near_dupl_right[n - 1] = near_eq_right[n - 1];
    for (int i = n - 2; i >= 0; --i) near_dupl_right[i] = std::min(near_dupl_right[i + 1], near_eq_right[i]);
    for (int i = n - 1; i >= 0; --i) {
        while (!temp_vec.empty() && heroes[temp_vec.back()] <= heroes[i]) temp_vec.pop_back();
        near_greater_right[i] = temp_vec.empty() ? n : temp_vec.back();
        temp_vec.push_back(i);
    }
    for (int i = 0; i < q; ++i) {
        cin >> reqs[i].l >> reqs[i].x, --reqs[i].l;
        reqs[i].id = i;
    }
    sort(reqs, reqs + q);
    int next_req = 0;
    ST::init(n);
    ST::set_progr(0, n, n - 1);
    for (int l = n - 1; l >= 0 && next_req < q; --l) {
        int r = near_dupl_right[l];
        ST::add(l + 1, r, -1);
        ST::set_progr(l, std::min(r, near_greater_right[l]), heroes[l]);
        while (next_req < q && reqs[next_req].l == l) {
            int nl = l + reqs[next_req].x - 1;
            if (nl < r) {
                auto [min_val, min_cnt] = ST::get_min(nl, r);
                if (min_val == 0) {
                    int min_len = ST::first_zero(nl, r) - l + 1;
                    ans[reqs[next_req].id] = {min_len, min_cnt};
                } else ans[reqs[next_req].id] = {-1, 0};
            } else ans[reqs[next_req].id] = {-1, 0};
            ++next_req;
        }
    }
    for (int i = 0; i < q; ++i) cout << ans[i].first << " " << ans[i].second << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int g;
    cin >> g;
    solve();
    return 0;
}
