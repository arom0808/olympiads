#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int32_t maxn = 2e5 + 2;

namespace SegTree {
    struct Node {
        int32_t min_val = 0, min_cnt_sum = 0, change = 0;

        Node operator+(const Node &other) const {
            return {
                std::min(min_val, other.min_val),
                (min_val <= other.min_val ? min_cnt_sum : 0) + (other.min_val <= min_val ? other.min_cnt_sum : 0), 0
            };
        }
    };

    Node tree[maxn * 4];
    int32_t size;

    void _init(int32_t v, int32_t l, int32_t r, const vector<int32_t> &fsums) {
        if (l >= r) return;
        if (r - l == 1) {
            tree[v].min_cnt_sum = fsums[l];
            return;
        }
        _init(v * 2, l, (l + r) / 2, fsums);
        _init(v * 2 + 1, (l + r) / 2, r, fsums);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    void transfer_changes(int32_t v, int32_t l, int32_t r) {
        if (!tree[v].change) return;
        if (r - l > 1) {
            tree[v * 2].change += tree[v].change;
            tree[v * 2 + 1].change += tree[v].change;
            tree[v * 2].min_val += tree[v].change;
            tree[v * 2 + 1].min_val += tree[v].change;
        }
        tree[v].change = 0;
    }

    void _add(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b, int32_t val) {
        if (l >= r || l >= b || a >= r) return;
        transfer_changes(v, l, r);
        if (a <= l && r <= b) {
            tree[v].change += val;
            tree[v].min_val += val;
            return;
        }
        _add(v * 2, l, (l + r) / 2, a, b, val);
        _add(v * 2 + 1, (l + r) / 2, r, a, b, val);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    pair<int32_t, int32_t> _min_sum_val(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || l >= b || a >= r) return {2e9, 0};
        transfer_changes(v, l, r);
        if (a <= l && r <= b) return {tree[v].min_val, tree[v].min_cnt_sum};
        auto [v1,s1] = _min_sum_val(v * 2, l, (l + r) / 2, a, b);
        auto [v2,s2] = _min_sum_val(v * 2 + 1, (l + r) / 2, r, a, b);
        return {std::min(v1, v2), (v1 <= v2 ? s1 : 0) + (v2 <= v1 ? s2 : 0)};
    }

    void init(int32_t _size, const vector<int32_t> &fsums) {
        size = _size;
        _init(1, 0, size, fsums);
    }

    void add(int32_t a, int32_t b, int32_t val) {
        _add(1, 0, size, a, b, val);
    }

    pair<int32_t, int32_t> min_sum_val(int32_t a, int32_t b) {
        return _min_sum_val(1, 0, size, a, b);
    }
}

struct Action {
    int32_t x, y1, y2;
    bool mode;
};

int32_t zip_pos(int32_t val, const vector<int32_t> &zip_vec) {
    return distance(zip_vec.begin(), lower_bound(zip_vec.begin(), zip_vec.end(), val));
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n;
    cin >> n;
    vector<int32_t> xs(n * 2), ys(n * 2);
    vector<Action> actions(n * 2);
    for (int32_t i = 0, x1, y1, x2, y2; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        xs[i * 2] = x1, xs[i * 2 + 1] = x2;
        ys[i * 2] = y1, ys[i * 2 + 1] = y2;
        actions[i * 2] = {x1, y1, y2, true};
        actions[i * 2 + 1] = {x2, y1, y2, false};
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (auto &[x,y1,y2,mode]: actions) x = zip_pos(x, xs), y1 = zip_pos(y1, ys), y2 = zip_pos(y2, ys);
    sort(actions.begin(), actions.end(), [](const Action &a, const Action &b) {
        if (a.x != b.x) return a.x < b.x;
        return !a.mode && b.mode;
    });
    vector<int32_t> st_cnts(ys.size());
    for (int32_t i = 0; i + 1 < ys.size(); ++i) st_cnts[i] = ys[i + 1] - ys[i];
    st_cnts[ys.size() - 1] = 0;
    SegTree::init(ys.size(), st_cnts);
    SegTree::add(ys.size() - 1, ys.size(), 2e9);
    int64_t res = 0;
    for (int32_t a_id = 0; a_id + 1 < actions.size(); ++a_id) {
        SegTree::add(actions[a_id].y1, actions[a_id].y2, actions[a_id].mode ? 1 : -1);
        auto [v,s] = SegTree::min_sum_val(0, ys.size());
        res += 1ll * (ys.back() - ys.front() - (v ? 0 : s)) * (xs[actions[a_id + 1].x] - xs[actions[a_id].x]);
    }
    cout << res << "\n";
    return 0;
}
