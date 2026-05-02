#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

namespace st {
    struct Node {
        int32_t max_val = 0;
        Node *l = nullptr, *r = nullptr;
    };

    const int32_t max_st_size = 1e7;

    Node tree[max_st_size];
    int32_t used_cnt = 0;
    int32_t size;

    void init(Node *&v, int32_t l, int32_t r) {
        if (l >= r) return;
        if (!v) v = &tree[used_cnt++];
        if (r - l == 1) return;
        init(v->l, l, (l + r) / 2);
        init(v->r, (l + r) / 2, r);
    }

    Node *assign(int32_t _size) {
        size = _size;
        Node *root = nullptr;
        init(root, 0, size);
        return root;
    }

    inline int32_t node_max_val(Node *v) { return v ? v->max_val : 0; }

    Node *_set(Node *v, int32_t l, int32_t r, int32_t pos, int32_t val) {
        if (l >= r || r <= pos || pos < l) return v;
        Node *nv = &tree[used_cnt++];
        if (r - l == 1) {
            nv->max_val = val;
        } else {
            nv->l = _set(v->l, l, (l + r) / 2, pos, val);
            nv->r = _set(v->r, (l + r) / 2, r, pos, val);
            nv->max_val = std::max(node_max_val(nv->l), node_max_val(nv->r));
        }
        return nv;
    }

    int32_t _max_val(Node *v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || r <= a || b <= l) return 0;
        if (a <= l && r <= b) return v->max_val;
        return std::max(_max_val(v->l, l, (l + r) / 2, a, b), _max_val(v->r, (l + r) / 2, r, a, b));
    }

    Node *set(Node *root, int32_t pos, int32_t val) {
        return _set(root, 0, size, pos, val);
    }

    int32_t max_val(Node *root, int32_t a, int32_t b) {
        return _max_val(root, 0, size, a, b);
    }
}

const int32_t maxn = 2e5;
st::Node *roots[maxn];
vector<int32_t> g[maxn];
vector<int32_t> nums;
int32_t ans[maxn];

void dfs(int32_t u, int32_t p = -1) {
    ans[u] = st::max_val(roots[u], 0, st::size);
    for (auto v: g[u]) {
        if (v == p) continue;
        roots[v] = st::set(roots[u], nums[v], st::max_val(roots[u], 0, nums[v]) + 1);
        dfs(v, u);
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    nums.resize(n);
    for (auto &v: nums) cin >> v;
    vector<int32_t> clz = nums;
    std::sort(clz.begin(), clz.end());
    for (auto &v: nums)
        v = static_cast<int32_t>(distance(clz.begin(), std::lower_bound(clz.begin(), clz.end(), v)));
    roots[0] = st::assign(n);
    roots[0] = st::set(roots[0], nums[0], 1);
    for (int32_t i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1), g[v - 1].push_back(u - 1);
    }
    dfs(0);
    for (int32_t i = 0; i < n; ++i) cout << ans[i] << "\n";
    return 0;
}
