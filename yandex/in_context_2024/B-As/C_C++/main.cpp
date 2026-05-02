#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class SegmentTree {
public:
    struct Node {
    public:
        int32_t gcd_val = 0;

        Node() = default;

        explicit Node(int32_t gcd_val) : gcd_val(gcd_val) {}

        Node operator+(Node other) const {
            return Node(std::gcd(gcd_val, other.gcd_val));
        }
    };

    vector<Node> tree;
    int32_t size = 0;

    SegmentTree() = default;

    SegmentTree(int32_t *arr, int32_t _size) : tree(_size * 4), size(_size) {
        init(arr, 1, 0, size);
    }

    void assign(int32_t *arr, int32_t _size) {
        tree.clear();
        tree.resize(_size * 4);
        size = _size;
        init(arr, 1, 0, size);
    }

    void init(int32_t *arr, int32_t id, int32_t l, int32_t r) {
        if (l >= r) return;
        if (r - l == 1) {
            tree[id].gcd_val = arr[l];
            return;
        }
        init(arr, id * 2, l, (l + r) / 2);
        init(arr, id * 2 + 1, (l + r) / 2, r);
        tree[id] = tree[id * 2] + tree[id * 2 + 1];
    }

    int32_t _get_gcd(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b) const {
        if (l >= r || r <= a || b <= l) return 0;
        if (a <= l && r <= b) return tree[id].gcd_val;
        return std::gcd(_get_gcd(id * 2, l, (l + r) / 2, a, b), _get_gcd(id * 2 + 1, (l + r) / 2, r, a, b));
    }

    int32_t get_gcd(int32_t a, int32_t b) const {
        if (a >= b) return 0;
        return _get_gcd(1, 0, size, a, b);
    }
};

const int32_t maxn = 2e5;
int32_t n, q;
int32_t a[maxn], b[maxn];
int32_t da[maxn], db[maxn];
SegmentTree ast, bst;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int32_t i = 0; i < n; ++i) cin >> a[i];
    for (int32_t i = 0; i < n; ++i) cin >> b[i];
    for (int32_t i = 1; i < n; ++i) da[i - 1] = std::abs(a[i] - a[i - 1]);
    for (int32_t i = 1; i < n; ++i) db[i - 1] = std::abs(b[i] - b[i - 1]);
    ast.assign(da, n - 1), bst.assign(db, n - 1);
    int32_t x1, x2, y1, y2;
    for (int32_t i = 0; i < q; ++i) {
        cin >> x1 >> x2 >> y1 >> y2, --x1, --x2, --y1, --y2;
        cout << std::gcd(a[x1] + b[y1], std::gcd(ast.get_gcd(x1, x2), bst.get_gcd(y1, y2))) << "\n";
    }
    return 0;
}
