#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_miltiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int32_t maxn = 1e5;

namespace SegTree2D {
    ordered_miltiset<int32_t> tree[maxn * 4];
    int32_t size;

    void _add(int32_t v, int32_t l, int32_t r, int32_t x, int32_t y) {
        if (l >= r || l >= x + 1 || r <= x) return;
        if (x <= l && r <= x + 1) {
            tree[v].insert(y);
        } else {
            _add(v * 2, l, (l + r) / 2, x, y);
            _add(v * 2 + 1, (l + r) / 2, r, x, y);
            tree[v].insert(y);
        }
    }

    int32_t _sum(int32_t v, int32_t l, int32_t r, int32_t a1, int32_t b1, int32_t a2, int32_t b2) {
        if (l >= r || l >= b1 || r <= a1) return 0;
        if (a1 <= l && r <= b1) return tree[v].order_of_key(b2) - tree[v].order_of_key(a2);
        return _sum(v * 2, l, (l + r) / 2, a1, b1, a2, b2) + _sum(v * 2 + 1, (l + r) / 2, r, a1, b1, a2, b2);
    }

    void init(int32_t n, int32_t m) {
        size = n;
    }

    void add(int32_t x, int32_t y) {
        _add(1, 0, size, x, y);
    }

    int32_t sum(int32_t a1, int32_t b1, int32_t a2, int32_t b2) {
        return _sum(1, 0, size, a1, b1, a2, b2);
    }
}

int32_t zipped_val(int32_t val, const vector<int32_t> &zip_arr) {
    return distance(zip_arr.begin(), lower_bound(zip_arr.begin(), zip_arr.end(), val));
}

int32_t zipped_val_up(int32_t val, const vector<int32_t> &zip_arr) {
    return distance(zip_arr.begin(), upper_bound(zip_arr.begin(), zip_arr.end(), val));
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, m;
    cin >> n;
    vector<int32_t> xs(n), ys(n);
    vector<pair<int32_t, int32_t> > ps(n);
    for (int32_t i = 0; i < n; ++i) cin >> ps[i].first >> ps[i].second, xs[i] = ps[i].first, ys[i] = ps[i].second;
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    for (int32_t i = 0; i < n; ++i) {
        ps[i].first = zipped_val(ps[i].first, xs);
        ps[i].second = zipped_val(ps[i].second, ys);
    }
    SegTree2D::init(n, n);
    for (int32_t i = 0; i < n; ++i) SegTree2D::add(ps[i].first, ps[i].second);
    cin >> m;
    for (int32_t i = 0, x1, y1, x2, y2; i < m; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        x1 = zipped_val(x1, xs), y1 = zipped_val(y1, ys);
        x2 = zipped_val_up(x2, xs), y2 = zipped_val_up(y2, ys);
        cout << SegTree2D::sum(x1, x2, y1, y2) << "\n";
    }
    return 0;
}
