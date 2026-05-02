#include <iostream>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

using namespace std;

template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
class SegmentTree {
public:
    struct Node {
        T sum = 0;

    };

    int32_t size = 0;
    vector<Node> tree;

    void _init(int32_t id, int32_t l, int32_t r, const vector<T> &vals) {
        if (l >= r) return;
        if (r - l == 1) tree[id].sum = vals[l];
        else {
            _init(id * 2, l, (l + r) / 2, vals);
            _init(id * 2 + 1, (l + r) / 2, r, vals);
            tree[id].sum = tree[id * 2].sum + tree[id * 2 + 1].sum;
        }
    }

    void _set(int32_t id, int32_t l, int32_t r, int32_t pos, T val) {
        if (l >= r || pos < l || r <= pos) return;
        if (r - l == 1) tree[id].sum = val;
        else {
            _set(id * 2, l, (l + r) / 2, pos, val);
            _set(id * 2 + 1, (l + r) / 2, r, pos, val);
            tree[id].sum = tree[id * 2].sum + tree[id * 2 + 1].sum;
        }
    }

    T _sum(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || b <= l || r <= a) return 0;
        if (a <= l && r <= b) return tree[id].sum;
        return _sum(id * 2, l, (l + r) / 2, a, b) + _sum(id * 2 + 1, (l + r) / 2, r, a, b);
    }

    void assign(const vector<T> &vals) {
        size = vals.size();
        tree.clear(), tree.resize(size * 4);
        _init(1, 0, size, vals);
    }

    void set(int32_t pos, T val) {
        _set(1, 0, size, pos, val);
    }

    T sum(int32_t a, int32_t b) {
        return _sum(1, 0, size, a, b);
    }
};

int64_t n;
vector<int64_t> raw_counts;
vector<int32_t> sorted_positions;
vector<pair<int64_t, int64_t>> comp1;
SegmentTree<int64_t> st1;
vector<int64_t> results;

void first_sol() {
    ordered_multiset<int64_t> oms;
    for (int32_t i = 0; i < n; ++i) oms.insert(raw_counts[i]);
    int64_t pre_sum = 0;
    for (int64_t i = 0; i < n; ++i) {
        st1.set(sorted_positions[i], 0);
        int64_t l = 0, r = n - 1 - i;
        pre_sum += raw_counts[i];
    }
}

int main() {
    int64_t c;
    cin >> n >> c;
    raw_counts.resize(n);
    for (auto val: raw_counts) cin >> val;
    raw_counts[0] += c;
    comp1.resize(n);
    for (int32_t i = 0; i < n; ++i) comp1[i] = {raw_counts[i], i};
    sort(comp1.begin(), comp1.end(), [](const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });
    for (int32_t i = 0; i < n; ++i) sorted_positions[comp1[i].second] = i;
    vector<int64_t> st_init_vec(n);
    for (int32_t i = 0; i < n; ++i) st_init_vec[i] = comp1[i].first;
    st1.assign(st_init_vec);
    results.resize(n, 1e9);
    first_sol();
    return 0;
}
