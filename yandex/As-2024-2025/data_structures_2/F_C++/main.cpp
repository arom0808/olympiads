#include <iostream>
#include <random>

using namespace std;

const int maxn = 1e5;
const int inf = 1e9 + 1;

namespace DD {
    struct Node {
        Node *l = nullptr, *r = nullptr;
        int val, min_val, y, size;
        bool reverse_need;
    };

    mt19937 rng(71784178);
    uniform_int_distribution<int> y_dist(-inf + 1, inf);
    Node tree[maxn + 2];
    Node *zero_node = &(tree[0] = {nullptr, nullptr, inf, inf, -inf, 0, false});
    Node *root = zero_node;
    int nodes_used = 1;

    Node *get_new_node(int val) {
        return &(tree[nodes_used++] = {zero_node, zero_node, val, val, y_dist(rng), 1, false});
    }

    void upd_from_child(Node *v) {
        if (v == zero_node) return;
        v->min_val = std::min(std::min(v->l->min_val, v->r->min_val), v->val);
        v->size = v->l->size + v->r->size + 1;
    }

    void push(Node *v) {
        if (!v->reverse_need) return;
        if (v != zero_node) {
            v->l->reverse_need ^= 1, v->r->reverse_need ^= 1;
            swap(v->l, v->r);
        }
        v->reverse_need = false;
    }

    Node *merge(Node *a, Node *b) {
        if (a == zero_node) return b;
        if (b == zero_node) return a;
        if (a->y > b->y) {
            push(a);
            a->r = merge(a->r, b);
            upd_from_child(a);
            return a;
        }
        push(b);
        b->l = merge(a, b->l);
        upd_from_child(b);
        return b;
    }

    pair<Node *, Node *> split(Node *v, int sz) {
        if (v == zero_node) return {zero_node, zero_node};
        push(v);
        if (v->l->size >= sz) {
            auto p = split(v->l, sz);
            v->l = p.second;
            upd_from_child(v);
            return {p.first, v};
        }
        auto p = split(v->r, sz - v->l->size - 1);
        v->r = p.first;
        upd_from_child(v);
        return {v, p.second};
    }

    void push_back(int val) {
        root = merge(root, get_new_node(val));
    }

    void reverse(int from, int to) {
        auto [pre_node, cn_n] = split(root, from);
        auto [cur_node, next_node] = split(cn_n, to - from);
        cur_node->reverse_need ^= 1;
        root = merge(pre_node, merge(cur_node, next_node));
    }

    int min_val(int from, int to) {
        auto [pre_node, cn_n] = split(root, from);
        auto [cur_node, next_node] = split(cn_n, to - from);
        auto ans = cur_node->min_val;
        root = merge(pre_node, merge(cur_node, next_node));
        return ans;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0, val; i < n; ++i) cin >> val, DD::push_back(val);
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c, --b;
        if (a == 1) DD::reverse(b, c);
        else cout << DD::min_val(b, c) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
