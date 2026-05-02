#include <iostream>
#include <bitset>
#include <random>

using namespace std;
using ll = long long;

namespace DD {
    const uint32_t seed = 784725489;
    mt19937 rng(seed);
    uniform_int_distribution<int> dist_y(0, 1e9);

    struct Node {
        Node *l = nullptr, *r = nullptr;
        bitset<26> chars_contains;
        ll sz = 0;
        char cur_type = 0;
        int cur_size = 0;

        void update_from_child();

        void check_make_child();
    };

    using NP = pair<Node *, Node *>;

    const int max_nodes_cnt = 2e6;

    Node nodes[max_nodes_cnt];
    Node *zn = &nodes[0], *root = zn;
    int used_nodes = 1;

    Node *get_new_node(char type, int cnt) {
        auto ans = &(nodes[used_nodes++] = {zn, zn, {}, cnt, type, cnt});
        ans->chars_contains.set(type, true);
        return ans;
    }

    void Node::update_from_child() {
        if (this == zn) return;
        chars_contains = l->chars_contains | r->chars_contains;
        chars_contains.set(cur_type, true);
        sz = l->sz + r->sz + cur_size;
    }

    void Node::check_make_child() {
        if (cur_size <= 1) return;
        auto nl = get_new_node(cur_type, cur_size / 2);
        nl->l = l, l = nl, l->update_from_child();
        if (int rsz = cur_size - cur_size / 2 - 1; rsz > 0) {
            auto nr = get_new_node(cur_type, rsz);
            nr->r = r, r = nr, r->update_from_child();
        }
        cur_size = 1;
    }

    Node *merge(Node *a, Node *b) {
        if (a == zn) return b;
        if (b == zn) return a;
        if (dist_y(rng) % (a->sz + b->sz) < a->sz) {
            a->r = merge(a->r, b);
            a->update_from_child();
            return a;
        }
        b->l = merge(a, b->l);
        b->update_from_child();
        return b;
    }

    NP split(Node *a, ll sz) {
        if (a == zn) return {zn, zn};
        a->check_make_child();
        if (a->l->sz >= sz) {
            NP p = split(a->l, sz);
            a->l = p.second;
            p.first->update_from_child(), a->update_from_child();
            return {p.first, a};
        }
        NP p = split(a->r, a->sz - sz - 1);
        a->r = p.first;
        a->update_from_child(), p.second->update_from_child();
        return {a, p.second};
    }

    void insert(int pos, int cnt, char type) {
        auto p = split(root, pos);
        auto new_node = get_new_node(type, cnt);
        root = merge(p.first, merge(new_node, p.second));
    }

    void remove(int pos, int cnt) {
        auto p1 = split(root, pos), p2 = split(p1.second, cnt);
        root = merge(p1.first, p2.second);
    }

    int query(int pos1, int pos2) {
        auto p1 = split(root, pos1), p2 = split(p1.second, pos2 - pos1);
        auto ans = p2.first->chars_contains.count();
        root = merge(p1.first, merge(p2.first, p2.second));
        return ans;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n;
    cin >> n;
    char c;
    for (int i = 0, a, b; i < n; ++i) {
        cin >> c;
        if (c == '+') {
            cin >> a >> b >> c;
            DD::insert(a - 1, b, c - 'a');
        } else if (c == '-') {
            cin >> a >> b;
            DD::remove(a - 1, b);
        } else {
            cin >> a >> b;
            cout << DD::query(a - 1, b) << "\n";
        }
    }
    return 0;
}
