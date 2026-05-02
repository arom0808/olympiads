#include <iostream>
#include <random>


using namespace std;
using ll = long long;

const int maxn = 3e5, mod = 1e9;

namespace DD {
    const uint32_t seed = 18927899;
    mt19937 rng(seed);
    uniform_int_distribution<int> dist_y(0, 1e9);


    struct Node {
        Node *l = nullptr, *r = nullptr;
        int sz = 0, max = 0, val = 0, y = 0;
        ll sum = 0;

        void update_from_child();
    };

    using nodes_pair = pair<Node *, Node *>;

    Node tree[maxn] = {{nullptr, nullptr, 0, 0, 0, 0, 0}};
    int used_nodes = 1;
    Node *zero_node = &tree[0];
    Node *root = zero_node;

    void Node::update_from_child() {
        if (this == zero_node) return;
        this->max = std::max(std::max(l->max, r->max), val);
        sum = l->sum + r->sum + val;
        sz = l->sz + r->sz + 1;
    }

    Node *get_new_v(int val) {
        return &(tree[used_nodes++] = {zero_node, zero_node, 1, val, val, dist_y(rng), val});
    }

    Node *merge(Node *a, Node *b) {
        if (a == zero_node) return b;
        if (b == zero_node) return a;
        if (a->y > b->y) {
            a->r = merge(a->r, b);
            a->update_from_child();
            return a;
        }
        b->l = merge(a, b->l);
        b->update_from_child();
        return b;
    }

    nodes_pair split(Node *a, int x) {
        if (a == zero_node) return {zero_node, zero_node};
        if (a->l->max >= x || a->val >= x) {
            auto p = split(a->l, x);
            a->l = p.second;
            p.first->update_from_child(), a->update_from_child();
            return {p.first, a};
        }
        auto p = split(a->r, x);
        a->r = p.first;
        a->update_from_child(), p.second->update_from_child();
        return {a, p.second};
    }

    void add(int val) {
        auto p1 = split(root, val), p2 = split(p1.second, val + 1);
        if (p2.first == zero_node) p2.first = get_new_v(val);
        root = merge(p1.first, merge(p2.first, p2.second));
    }

    ll sum(int l, int r) {
        auto p1 = split(root, l), p2 = split(p1.second, r + 1);
        auto ans = p2.first->sum;
        root = merge(p1.first, merge(p2.first, p2.second));
        return ans;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, a, b;
    cin >> n;
    char c;
    ll last_sum = -1;
    for (int i = 0; i < n; ++i) {
        cin >> c;
        if (c == '+') {
            cin >> a;
            if (last_sum == -1) DD::add(a);
            else DD::add((last_sum + a) % mod);
            last_sum = -1;
        } else {
            cin >> a >> b;
            last_sum = DD::sum(a, b);
            cout << last_sum << "\n";
        }
    }
    return 0;
}
