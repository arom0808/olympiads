#include <iostream>
#include <random>

using namespace std;
using ll = long long;

constexpr int maxn = 1e5;

mt19937 rng(2234897);

namespace DD {
    struct Node {
        ll val = 0, sum = 0;
        ll push_start = 0;
        unsigned int prior = 0;
        int sz = 0, push_delta = 0, push_set = 0;
        Node *l = nullptr, *r = nullptr;

        Node() = default;

        void init(ll _val);

        void set_val(ll _val) {
            val = _val;
            sum = val * sz;
            push_set = val;
            push_start = push_delta = 0;
        }

        void add_progr(ll start, int delta) {
            sum += 1ll * sz * start + 1ll * sz * (sz - 1) / 2 * delta;
            val += start + 1ll * l->sz * delta;
            push_start += start, push_delta += delta;
        }
    };

    Node tree[maxn * 2 + 2];
    int nodes_used = 0;
    Node *zero_node = &tree[nodes_used++];
    Node *root = zero_node;

    void Node::init(ll _val) {
        val = sum = _val;
        prior = rng();
        sz = 1;
        push_delta = push_set = 0;
        l = r = zero_node;
    }

    Node *get_new_node(ll val) {
        tree[nodes_used].init(val);
        return &tree[nodes_used++];
    }

    void push(Node *v) {
        if (v == zero_node) return;
        if (v->push_set) {
            if (v->l != zero_node) v->l->set_val(v->push_set);
            if (v->r != zero_node) v->r->set_val(v->push_set);
            v->push_set = 0;
        }
        if (v->push_start) {
            if (v->l != zero_node) v->l->add_progr(v->push_start, v->push_delta);
            if (v->r != zero_node)
                v->r->add_progr(v->push_start + 1ll * (v->l->sz + 1) * v->push_delta, v->push_delta);
            v->push_start = v->push_delta = 0;
        }
    }

    void upd_from_children(Node *v) {
        v->sum = v->l->sum + v->r->sum + v->val;
        v->sz = v->l->sz + v->r->sz + 1;
    }

    pair<Node *, Node *> split(Node *v, int lsz) {
        if (!lsz) return {zero_node, v};
        if (v == zero_node) return {zero_node, zero_node};
        push(v);
        if (v->l->sz >= lsz) {
            auto p1 = split(v->l, lsz);
            v->l = p1.second;
            upd_from_children(v);
            return {p1.first, v};
        }
        auto p1 = split(v->r, lsz - v->l->sz - 1);
        v->r = p1.first;
        upd_from_children(v);
        return {v, p1.second};
    }

    Node *merge(Node *a, Node *b) {
        if (a == zero_node) return b;
        if (b == zero_node) return a;
        push(a), push(b);
        if (a->prior > b->prior) {
            a->r = merge(a->r, b);
            upd_from_children(a);
            return a;
        }
        b->l = merge(a, b->l);
        upd_from_children(b);
        return b;
    }

    void set_val(int from, int to, int val) {
        auto p1 = split(root, from);
        auto p2 = split(p1.second, to - from);
        if (p2.first != zero_node) p2.first->set_val(val);
        root = merge(p1.first, merge(p2.first, p2.second));
    }

    void add_progr(int from, int to, int x) {
        auto p1 = split(root, from);
        auto p2 = split(p1.second, to - from);
        if (p2.first != zero_node) p2.first->add_progr(x, x);
        root = merge(p1.first, merge(p2.first, p2.second));
    }

    void insert(int before, int val) {
        auto p1 = split(root, before);
        auto m = get_new_node(val);
        root = merge(p1.first, merge(m, p1.second));
    }

    ll sum(int from, int to) {
        auto p1 = split(root, from);
        auto p2 = split(p1.second, to - from);
        ll res = p2.first->sum;
        root = merge(p1.first, merge(p2.first, p2.second));
        return res;
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0, val; i < n; ++i) {
        cin >> val;
        DD::insert(i, val);
    }
    int t, a, b, c, x;
    for (int i = 0; i < q; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> a >> b >> x;
            DD::set_val(a - 1, b, x);
        } else if (t == 2) {
            cin >> a >> b >> x;
            DD::add_progr(a - 1, b, x);
        } else if (t == 3) {
            cin >> c >> x;
            DD::insert(c - 1, x);
        } else {
            cin >> a >> b;
            cout << DD::sum(a - 1, b) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
