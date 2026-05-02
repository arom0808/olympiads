#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int32_t maxn = 1e5;

namespace MST {
    struct Node {
        vector<int32_t> els;

        void init(int32_t el) { els = {el}; }

        void init(const vector<int32_t> &a, const vector<int32_t> &b) {
            els.clear();
            for (int32_t i1 = 0, i2 = 0; i1 < a.size() || i2 < b.size();) {
                if (i1 != a.size() && (i2 == b.size() || a[i1] < b[i2])) els.push_back(a[i1++]);
                else els.push_back(b[i2++]);
            }
        }

        [[nodiscard]] int32_t cnt_in_diap(int32_t a, int32_t b) const {
            if (a > b) swap(a, b);
            return distance(lower_bound(els.begin(), els.end(), a), upper_bound(els.begin(), els.end(), b));
        }
    };

    Node tree[maxn * 4];
    int32_t size;

    void _init(int32_t v, int32_t l, int32_t r, const vector<int32_t> &arr) {
        if (r - l == 1) {
            tree[v].init(arr[l]);
            return;
        }
        _init(v * 2, l, (l + r) / 2, arr);
        _init(v * 2 + 1, (l + r) / 2, r, arr);
        tree[v].init(tree[v * 2].els, tree[v * 2 + 1].els);
    }

    int32_t _cnt_in_diap(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b, int32_t c, int32_t d) {
        if (l >= b || a >= r) return 0;
        if (a <= l && r <= b) return tree[v].cnt_in_diap(c, d);
        return _cnt_in_diap(v * 2, l, (l + r) / 2, a, b, c, d) + _cnt_in_diap(v * 2 + 1, (l + r) / 2, r, a, b, c, d);
    }

    void init(const vector<int32_t> &arr) {
        size = arr.size();
        _init(1, 0, size, arr);
    }

    int32_t cnt_in_diap(int32_t a, int32_t b, int32_t c, int32_t d) {
        return _cnt_in_diap(1, 0, size, a, b, c, d);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, m;
    cin >> n >> m;
    vector<int32_t> arr(n);
    for (auto &el: arr) cin >> el;
    MST::init(arr);
    for (int i = 0, a, b, c, d; i < m; ++i) {
        cin >> a >> b >> c >> d;
        cout << MST::cnt_in_diap(a - 1, b, c, d) << "\n";
    }
    return 0;
}
