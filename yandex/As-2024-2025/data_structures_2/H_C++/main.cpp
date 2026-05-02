#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <ranges>
using namespace std;

constexpr int maxn = 2e6, inf = 1e9;

namespace DD {
    const uint32_t seed = 2632643236;
    mt19937 rng(seed);
    uniform_int_distribution<int> dist_y(0, 1e9);

    struct Node {
        Node *l = nullptr, *r = nullptr;
        int sz = 0, val = 0, min_val = 0, y = 0;

        void update_from_children();
    };

    using pn = std::pair<Node *, Node *>;

    Node tree[maxn + 1];
    Node *zn = &(tree[0] = {nullptr, nullptr, 0, inf, inf, 0}), *root = zn;
    int nodes_used = 1;

    void Node::update_from_children() {
        if (this == zn) return;
        sz = l->sz + r->sz + 1;
        min_val = std::min(val, std::min(l->min_val, r->min_val));
    }

    Node *get_new_node(int val) {
        return &(tree[nodes_used++] = {zn, zn, 1, val, val, dist_y(rng)});
    }

    Node *merge(Node *a, Node *b) {
        if (a == zn) return b;
        if (b == zn) return a;
        if (a->y > b->y) {
            a->r = merge(a->r, b);
            a->update_from_children();
            return a;
        }
        b->l = merge(a, b->l);
        b->update_from_children();
        return b;
    }

    pn split_sz(Node *a, int sz) {
        if (a == zn) return {zn, zn};
        if (a->l->sz >= sz) {
            auto p = split_sz(a->l, sz);
            a->l = p.second;
            p.first->update_from_children(), a->update_from_children();
            return {p.first, a};
        }
        auto p = split_sz(a->r, sz - a->l->sz - 1);
        a->r = p.first;
        a->update_from_children(), p.second->update_from_children();
        return {a, p.second};
    }

    pn split_second_min_greater(Node *a, int t) {
        if (a == zn) return {zn, zn};
        if (a->r->min_val <= t || a->val <= t) {
            auto p = split_second_min_greater(a->r, t);
            a->r = p.first;
            a->update_from_children(), p.second->update_from_children();
            return {a, p.second};
        }
        auto p = split_second_min_greater(a->l, t);
        a->l = p.second;
        p.first->update_from_children(), a->update_from_children();
        return {p.first, a};
    }

    void insert(int pos, int val) {
        auto p = split_sz(root, pos);
        root = merge(p.first, merge(get_new_node(val), p.second));
    }

    int insert(int val) {
        auto p = split_second_min_greater(root, val);
        int ans = p.first->sz;
        root = merge(p.first, merge(get_new_node(val), p.second));
        return ans;
    }

    int erase(int pos) {
        auto p1 = split_sz(root, pos), p2 = split_sz(p1.second, 1);
        root = merge(p1.first, p2.second);
        return p2.first->val;
    }
}

vector<int> poss_on_type[maxn];
int type_on_pos[maxn], raw_cards[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> type_on_pos[i], --type_on_pos[i];
        poss_on_type[type_on_pos[i]].push_back(i);
    }
    for (int i = 0; i < n; ++i) reverse(poss_on_type[i].begin(), poss_on_type[i].end());
    for (int i = 0; i < n; ++i) cin >> raw_cards[i], --raw_cards[i];
    for (int i = 0; i < n; ++i)
        DD::insert(i,
                   poss_on_type[raw_cards[i]].empty() ? inf : poss_on_type[raw_cards[i]].back());
    vector<int> ans;
    for (int i = 0; i < m;) {
        auto start_pos = DD::erase(0);
        auto type = start_pos == inf ? inf : type_on_pos[start_pos];
        if (type_on_pos[i] == type && type != inf && !poss_on_type[type].empty()) poss_on_type[type].pop_back();
        auto next_pos = (type == inf || poss_on_type[type].empty()) ? inf : poss_on_type[type].back();
        auto card_pos = DD::insert(next_pos);
        ans.push_back(card_pos);
        if (type_on_pos[i] == type) ++i;
    }
    cout << ans.size() << "\n";
    for (auto el: ans) cout << el + 1 << " ";
    return 0;
}
