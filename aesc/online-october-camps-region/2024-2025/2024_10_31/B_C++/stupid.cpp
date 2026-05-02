#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 2e6;
using ll = int64_t;
constexpr ll inf = 1e18;

namespace ST {
    struct Node {
        int enabled_cnt, change;
        ll min_val_m_pre;

        void init() {
            enabled_cnt = 0;
            min_val_m_pre = inf;
            change = 0;
        }
    };

    Node tree[maxn * 4];
    int size;

    void push(int v, int l, int r) {
        if (!tree[v].change) return;
        if (r - l > 1) {
            tree[v * 2].min_val_m_pre += tree[v].change;
            tree[v * 2 + 1].min_val_m_pre += tree[v].change;
            tree[v * 2].change += tree[v].change;
            tree[v * 2 + 1].change += tree[v].change;
        }
        tree[v].change = 0;
    }

    void upd_from_children(int v, int l, int r) {
        if (r - l <= 1) return;
        tree[v].enabled_cnt = tree[v * 2].enabled_cnt + tree[v * 2 + 1].enabled_cnt;
        tree[v].min_val_m_pre = std::min(tree[v * 2].min_val_m_pre, tree[v * 2 + 1].min_val_m_pre);
    }

    void _init(int v, int l, int r) {
        if (r - l == 1) {
            tree[v].init();
            return;
        }
        _init(v * 2, l, (l + r) / 2);
        _init(v * 2 + 1, (l + r) / 2, r);
        upd_from_children(v, l, r);
    }

    int _enabled_cnt(int v, int l, int r, int a, int b) {
        if (l >= b || a >= r) return 0;
        if (a <= l && r <= b) return tree[v].enabled_cnt;
        push(v, l, r);
        return _enabled_cnt(v * 2, l, (l + r) / 2, a, b) + _enabled_cnt(v * 2 + 1, (l + r) / 2, r, a, b);
    }

    ll _min_val_m_pre(int v, int l, int r, int a, int b) {
        if (l >= b || a >= r) return inf;
        if (a <= l && r <= b) return tree[v].min_val_m_pre;
        push(v, l, r);
        return std::min(_min_val_m_pre(v * 2, l, (l + r) / 2, a, b), _min_val_m_pre(v * 2 + 1, (l + r) / 2, r, a, b));
    }

    void _enable_set(int v, int l, int r, int pos, ll val) {
        if (l >= pos + 1 || pos >= r) return;
        if (l == pos && r == pos + 1) {
            tree[v].enabled_cnt = 1;
            tree[v].min_val_m_pre = val;
            return;
        }
        push(v, l, r);
        _enable_set(v * 2, l, (l + r) / 2, pos, val);
        _enable_set(v * 2 + 1, (l + r) / 2, r, pos, val);
        upd_from_children(v, l, r);
    }

    void _add(int v, int l, int r, int a, int b, int val) {
        if (l >= b || a >= r) return;
        if (a <= l && r <= b) {
            tree[v].min_val_m_pre += val;
            tree[v].change += val;
            return;
        }
        push(v, l, r);
        _add(v * 2, l, (l + r) / 2, a, b, val);
        _add(v * 2 + 1, (l + r) / 2, r, a, b, val);
        upd_from_children(v, l, r);
    }

    void _add_all_enabled(int v, int l, int r, vector<int> &res) {
        if (r - l == 1) {
            if (tree[v].enabled_cnt) res.push_back(l);
            return;
        }
        _add_all_enabled(v * 2, l, (l + r) / 2, res);
        _add_all_enabled(v * 2 + 1, (l + r) / 2, r, res);
    }

    void init(int _size) {
        size = _size;
        _init(1, 0, size);
    }

    // int enabled_cnt(int a, int b) {
    //     return _enabled_cnt(1, 0, size, a, b);
    // }

    ll min_val_m_pre(int a, int b) {
        return _min_val_m_pre(1, 0, size, a, b);
    }

    void enable_set(int pos, ll val) {
        _enable_set(1, 0, size, pos, val);
    }

    void add(int a, int b, int val) {
        _add(1, 0, size, a, b, val);
    }

    void add_all_enabled(vector<int> &res) {
        _add_all_enabled(1, 0, size, res);
    }
}

int n, m, k;
vector<pair<ll, int> > exp_date_id;
bool enabled[maxn];
int enabled_pf[maxn];

bool try_add(int edid) {
    ll exp_date = exp_date_id[edid].first;
    ll mvmp = (exp_date + 1) * k - 1 - enabled_pf[edid];
    if (mvmp >= 0 && ST::min_val_m_pre(edid + 1, n + m) > 0) {
        ST::add(edid + 1, n + m, -1);
        enabled[edid] = true;
        ST::enable_set(edid, mvmp);
        return true;
    }
    return false;
}

int main() {
    freopen("input.txt", "r",stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m >> k;
    exp_date_id.resize(n + m);
    for (int i = 0; i < n + m; ++i) cin >> exp_date_id[i].first, exp_date_id[i].second = i;
    sort(exp_date_id.begin(), exp_date_id.end());
    ST::init(n + m);
    for (int i = 0; i < n + m; ++i) enabled_pf[i] = 0, enabled[i] = false;
    enabled_pf[n + m] = 0;
    for (int i = n + m - 1; i >= 0; --i) {
        if (exp_date_id[i].second >= n) continue;
        if (!try_add(i)) {
            cout << "-1\n";
            return 0;
        }
    }
    for (int i = 0; i < n + m; ++i) enabled_pf[i + 1] = enabled_pf[i] + enabled[i];
    for (int i = n + m - 1; i >= 0; --i) if (exp_date_id[i].second >= n) try_add(i);
    vector<int> ans;
    ans.reserve(n + m);
    ST::add_all_enabled(ans);
    cout << ans.size() - n << "\n";
    for (auto el: ans) if (exp_date_id[el].second >= n) cout << exp_date_id[el].second - n + 1 << " ";
    cout << "\n";
    return 0;
}