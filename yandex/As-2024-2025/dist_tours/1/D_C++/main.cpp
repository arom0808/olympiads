#include <iostream>
#include <iomanip>

using namespace std;

const int32_t maxn = 5e4, xor_val = (1 << 29) - 1;

const long double eps = 1e-20;
const long double inf = 1e20;

struct Line {
    long double k, b;

    long double get(int32_t x) {
        return k * x + b;
    }
};

inline int32_t my_sign(long double val) {
    if (std::abs(val) <= eps) return 0;
    if (val < 0) return -1;
    return 1;
}

bool is_intersect(Line a, Line b) {
    return my_sign(b.b - a.b) / my_sign(a.k - b.k) >= 0;
}

long double intersect(Line a, Line b) {
    return static_cast<long double>(b.b - a.b) / static_cast<long double>(a.k - b.k);
}

namespace LiChaoTree {
    const int32_t max_nodes_cnt = 1e6;

    struct Node {
        Line line;
        Node *left = nullptr, *right = nullptr;

        void init() {
            line = Line(0, -inf);
        }
    };

    Node tree[max_nodes_cnt];
    int32_t nodes_used = 0;
    uint32_t size = 2e9 + 2;
    Node *root = nullptr;

    Node *get_new_node() {
        Node *node = &tree[nodes_used++];
        node->init();
        return node;
    }

    void init() {
        root = get_new_node();
    }

    void check_add_children(Node *v) {
        if (v->left == nullptr) v->left = get_new_node();
        if (v->right == nullptr) v->right = get_new_node();
    }

    void _insert(Node *v, uint32_t l, uint32_t r, Line line) {
        if (l >= r) return;
        uint32_t mid = (l + r) / 2;
        bool a = line.get(l) > v->line.get(l), b = line.get(mid) > v->line.get(mid), c =
                line.get(r - 1) > v->line.get(r - 1);
        if (b) swap(v->line, line);
        if (r - l == 1) return;
        check_add_children(v);
        if (a != b) _insert(v->left, l, mid, line);
        else if (b != c) _insert(v->right, mid, r, line);
    }

    long double _max_val(Node *v, uint32_t l, uint32_t r, uint32_t x) {
        if (l >= r || l > x || x >= r) return -inf;
        long double sec_val = -inf;
        if (r - l > 1) {
            uint32_t mid = (l + r) / 2;
            if (x < mid && v->left != nullptr) sec_val = _max_val(v->left, l, mid, x);
            else if (v->right != nullptr) sec_val = _max_val(v->right, mid, r, x);
        }
        return std::max(v->line.get(x), sec_val);
    }

    void insert(Line line) {
        _insert(root, 0, size, line);
    }
}

Line rays[maxn];
int32_t n, q;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    LiChaoTree::init();
    cout << fixed << setprecision(20);
    cin >> n;
    for (int32_t i = 0; i < n; ++i) {
        cin >> rays[i].k >> rays[i].b;
        LiChaoTree::insert(Line(static_cast<long double>(1) / rays[i].k, -(1e9l + rays[i].b) / rays[i].k));
    }
    cin >> q;
    if (n <= 2000) {
        bool pre_intersected = false;
        for (int32_t i = 0, c, d, e, f; i < q; ++i) {
            cin >> e >> f;
            if (i == 0 || pre_intersected) c = e, d = f;
            else c = e ^ xor_val, d = f ^ xor_val;
            Line cur_line(c, d);
            long double ans = 0;
            pre_intersected = false;
            for (int32_t j = 0; j < n; ++j) {
                if (!is_intersect(cur_line, rays[j])) continue;
                pre_intersected = true;
                ans = std::max(ans, intersect(cur_line, rays[j]));
            }
            if (!pre_intersected) cout << "No cross\n";
            else cout << ans << "\n";
        }
    } else {
        bool pre_intersected = false;
        for (int32_t i = 0, c, d, e, f; i < q; ++i) {
            cin >> e >> f;
            if (i == 0 || pre_intersected) c = e, d = f;
            else c = e ^ xor_val, d = f ^ xor_val;
            Line cur_line(c, d);
            pre_intersected = false;
            long double ans = LiChaoTree::_max_val(LiChaoTree::root, 0, LiChaoTree::size,
                                                   static_cast<uint32_t>(d) + 1e9);
            if (ans >= 0)pre_intersected = true;
            if (!pre_intersected) cout << "No cross\n";
            else cout << ans << "\n";
        }
    }
    return 0;
}
