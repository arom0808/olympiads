#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int maxn = 1e5;

namespace MST {
    struct Node {
        ordered_multiset<int32_t> els;

        void init(int32_t el) { els.clear(), els.insert(el); }

        void init(const ordered_multiset<int32_t> &a, const ordered_multiset<int32_t> &b) {
            els.clear();
            els.copy_from_range(a.begin(), a.end());
            els.copy_from_range(b.begin(), b.end());
        }

        [[nodiscard]] int32_t cnt_higher(int x) const {
            return els.size() - els.order_of_key(x + 1);
        }
    };

    Node tree[maxn * 4];
    int32_t size;

    void _init(int32_t v, int32_t l, int32_t r) {
        if (r - l == 1) {
            tree[v].init(0);
            return;
        }
        _init(v * 2, l, (l + r) / 2);
        _init(v * 2 + 1, (l + r) / 2, r);
        tree[v].init(tree[v * 2].els, tree[v * 2 + 1].els);
    }

    int _change(int v, int l, int r, int pos, int x) {
        if (l > pos || pos >= r) return -1;
        if (l == pos && r == pos + 1) {
            int ans = *tree[v].els.begin();
            tree[v].els.clear();
            tree[v].els.insert(x);
            return ans;
        }
        int m = (l + r) / 2, tcv;
        if (pos < m) tcv = _change(v * 2, l, m, pos, x);
        else tcv = _change(v * 2 + 1, m, r, pos, x);
        tree[v].els.erase(tree[v].els.find_by_order(tree[v].els.order_of_key(tcv)));
        tree[v].els.insert(x);
        return tcv;
    }

    int32_t _cnt_higher_in_diap(int32_t v, int32_t l, int32_t r, int32_t a, int32_t b, int32_t x) {
        if (l >= b || a >= r) return 0;
        if (a <= l && r <= b) return tree[v].cnt_higher(x);
        return _cnt_higher_in_diap(v * 2, l, (l + r) / 2, a, b, x) +
               _cnt_higher_in_diap(v * 2 + 1, (l + r) / 2, r, a, b, x);
    }

    void init(int n) {
        size = n;
        _init(1, 0, size);
    }

    int32_t cnt_higher_in_diap(int32_t a, int32_t b, int32_t x) {
        return _cnt_higher_in_diap(1, 0, size, a, b, x);
    }

    void change(int pos, int x) {
        _change(1, 0, size, pos, x);
    }
}


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n;
    while (true) {
        cin >> n;
        if(cin.eof()) break;
        MST::init(n);
        for (int i = 0, a, b; i < n; ++i) {
            cin >> a >> b, --a;
            cout << MST::cnt_higher_in_diap(0, a, b) << " ";
            MST::change(a, b);
        }
        cout << "\n";
    }
    return 0;
}
