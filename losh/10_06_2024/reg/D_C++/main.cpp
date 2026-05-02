#include <iostream>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<typename T> using OrderedMultiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Bus {
    uint64_t x, y, a, b, c;
};

struct Visit {
    uint64_t l, r;
};

struct Action {
    uint64_t time, type, id; // type - 0) end of visit, 1) end of bus, 2) start of bus

    Action(uint64_t time, uint64_t type, uint64_t id) : time(time), type(type), id(id) {}

    bool operator<(const Action &other) const {
        if (time != other.time) return time < other.time;
        if (type != other.type) return type < other.type;
        return id < other.id;
    }
};


const uint64_t maxn = 1e5 + 1;
uint64_t n, m, w;
uint64_t punishments[maxn];
Bus buses[maxn];
Visit visits[maxn];
int64_t dp[maxn];
vector<Action> actions;
OrderedMultiset<uint64_t> visits_oms;

struct Function {
    uint64_t c = 0;
    uint64_t start_time = 0, punish = 0;

    Function() = default;

    Function(uint64_t c, uint64_t start_time, uint64_t punish) : c(c), start_time(start_time), punish(punish) {}

    uint64_t operator()(uint64_t t) const {
        if (t <= start_time) return c;
        return c + (visits_oms.order_of_key(t) - visits_oms.order_of_key(start_time)) * punish;
    }
};

struct LiNode {
    LiNode *_left = nullptr, *_right = nullptr;
    Function f;

    LiNode *left();

    LiNode *right();

    LiNode() = default;

    explicit LiNode(Function _f) : f(_f) {}
};

const uint64_t max_li_tree_size = 1e7;

LiNode li_tree[max_li_tree_size];
uint64_t used_li_nodes_cnt = 0;

LiNode *LiNode::left() {
    if (_left) return _left;
    _left = &li_tree[used_li_nodes_cnt++];
    _left->f = f;
    return _left;
}

LiNode *LiNode::right() {
    if (_right) return _right;
    _right = &li_tree[used_li_nodes_cnt++];
    _right->f = f;
    return _right;
}

class LiChaoTree {
public:
    LiNode *root = nullptr;
    uint64_t size = 0;

    void assign(uint64_t _size, Function f) {
        size = _size;
        root = &li_tree[used_li_nodes_cnt++];
        root->f = f;
    }

    void _add_f(LiNode *node, uint64_t l, uint64_t r, Function f) {
        if (l >= r) return;
        auto mp = (l + r) / 2;
        auto lv = node->f(l) < f(l), mv = node->f(mp) < f(mp), rv = node->f(r - 1) < f(r - 1);
        if (!mv) swap(node->f, f);
        if (lv == mv && mv == rv || r - l == 1) return;
        if (lv != mv) _add_f(node->left(), l, (l + r) / 2, f);
        else _add_f(node->right(), (l + r) / 2, r, f);
    }

    uint64_t _min_val(LiNode *node, uint64_t l, uint64_t r, uint64_t pos) {
        uint64_t mid = (l + r) / 2;
        if (pos == mid) return node->f(pos);
        if (pos < mid) {
            if (node->_left) return min(node->f(pos), _min_val(node->left(), l, mid, pos));
            else return node->f(pos);
        }
        if (node->_right) return min(node->f(pos), _min_val(node->right(), mid, r, pos));
        else return node->f(pos);
    }

    void add_f(Function f) {
        _add_f(root, 0, size, f);
    }

    uint64_t min_val(uint64_t pos) {
        return _min_val(root, 0, size, pos);
    }
};

LiChaoTree li_chaos[maxn];

int main() {
//    freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> w;
    for (uint64_t i = 0; i < n; ++i) cin >> punishments[i];
    for (uint64_t i = 0; i < m; ++i) {
        auto &[x, y, a, b, c] = buses[i];
        cin >> x >> y >> a >> b >> c;
        actions.emplace_back(a, 2, i);
        actions.emplace_back(b, 1, i);
    }
    for (uint64_t i = 0; i < w; ++i) cin >> visits[i].l >> visits[i].r, actions.emplace_back(visits[i].r, 0, i);
    for (uint64_t i = 0; i < m; ++i) dp[i] = -1;
    if (actions.empty()) {
        cout << "-1\n";
        return 0;
    }
    sort(actions.begin(), actions.end());
    const uint64_t max_time = 2e9;
    li_chaos[0].assign(max_time, Function(0, 0, punishments[0]));
    for (auto [time, type, id]: actions) {
        if (type == 0) {
            visits_oms.insert(visits[id].l);
        } else if (type == 1 && dp[id] >= 0) {
            auto f = Function(dp[id], buses[id].b + 1, punishments[buses[id].y]);
            if (li_chaos[buses[id].y].size == 0) li_chaos[buses[id].y].assign(max_time, f);
            else li_chaos[buses[id].y].add_f(f);
        } else if (type == 2 && li_chaos[buses[id].x].size != 0) {
            dp[id] = li_chaos[buses[id].x].min_val(buses[id].a) + buses[id].c;
        }
    }
    if (li_chaos[n - 1].size == 0) cout << "-1\n";
    else cout << li_chaos[n - 1].min_val(max_time - 1) << "\n";
    return 0;
}