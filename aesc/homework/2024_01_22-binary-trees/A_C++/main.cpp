#include <iostream>

using namespace std;

namespace ST {
    struct Node {
        int sum = 0, set_val = 0;
        Node *l = nullptr, *r = nullptr;
    };

    Node *get_new_node() {
        return new Node();
    }

    Node *root = get_new_node();
    constexpr int sz = 1e9 + 2;

    void init_children(Node *v) {
        if (!v) return;
        if (!v->l) v->l = get_new_node();
        if (!v->r) v->r = get_new_node();
    }

    void push(Node *v, int l, int r) {
        if (r - l <= 1 || !v->set_val) return;
        int m = (l + r) >> 1;
        v->l->sum = (m - l) * v->set_val;
        v->l->set_val = v->set_val;
        v->r->sum = (r - m) * v->set_val;
        v->r->set_val = v->set_val;
    }

    void upd_from_children(Node *v) {
        if (v->l && v->r) v->sum = v->l->sum + v->r->sum;
    }

    void _set_val(Node *v, int l, int r, int a, int b, int val) {
        if (l >= b || a >= r) return;
        if (a <= l && r <= b) {
            v->set_val = val;
            v->sum = val * (r - l);
            return;
        }
        init_children(v);
        push(v, l, r);
        int m = (l + r) >> 1;
        _set_val(v->l, l, m, a, b, val);
        _set_val(v->r, m, r, a, b, val);
        upd_from_children(v);
    }

    void set_val(int a, int b, int val) {
        _set_val(root, 0, sz, a, b, val);
    }

    int _sum(Node *v, int l, int r, int a, int b) {
        if (l >= b || a >= r) return 0;
        if (a <= l && r <= b) return v->sum;
        init_children(v);
        push(v, l, r);
        int m = (l + r) >> 1;
        return _sum(v->l, l, m, a, b) + _sum(v->r, m, r, a, b);
    }

    int sum(int a, int b) {
        return _sum(root, 0, sz, a, b);
    }
}

void solve() {
    int m;
    cin >> m;
    int c = 0;
    for (int i = 0; i < m; ++i) {
        int d, x, y;
        cin >> d >> x >> y, --x, x += c, y += c;
        if (d == 1) {
            c = ST::sum(x, y);
            cout << c << "\n";
        } else ST::set_val(x, y, 1);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#else
    freopen("f.in", "r",stdin);
    freopen("f.out", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
