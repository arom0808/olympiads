#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

const int32_t inf = 1e9 + 1;

template<typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
class SegmentTree {
public:
    struct Node {
        T max_val, change;
    };

    vector<Node> tree;
    int32_t size;

    void _init(int32_t id, int32_t l, int32_t r, const vector<T> &vals) {
        if (l >= r) return;
        if (r - l == 1) tree[id].max_val = vals[l];
        else {
            _init(id * 2, l, (l + r) / 2, vals);
            _init(id * 2 + 1, (l + r) / 2, r, vals);
            tree[id].max_val = max(tree[id * 2].max_val, tree[id * 2 + 1].max_val);
        }
    }

    void transfer_changes(int32_t id) {
        if (tree[id].change == 0) return;
        if (id * 2 + 1 < tree.size()) {
            auto c = tree[id].change;
            auto &l = tree[id * 2], &r = tree[id * 2 + 1];
            l.max_val += c, l.change += c, r.max_val += c, r.change += c;
        }
        tree[id].change = 0;
    }

    T _max_val(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || b <= l || r <= a) return -inf - inf;
        transfer_changes(id);
        if (a <= l && r <= b) return tree[id].max_val;
        return max(_max_val(id * 2, l, (l + r) / 2, a, b), _max_val(id * 2 + 1, (l + r) / 2, r, a, b));
    }

    void _add(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b, T val) {
        if (l >= r || b <= l || r <= a) return;
        transfer_changes(id);
        if (a <= l && r <= b) tree[id].max_val += val, tree[id].change += val;
        else {
            _add(id * 2, l, (l + r) / 2, a, b, val);
            _add(id * 2 + 1, (l + r) / 2, r, a, b, val);
            tree[id].max_val = max(tree[id * 2].max_val, tree[id * 2 + 1].max_val);
        }
    }

    explicit SegmentTree(int32_t size, const vector<T> &vals) : size(size), tree(size * 4) {
        _init(1, 0, size, vals);
    }

    T max_val(int32_t a, int32_t b) {
        return _max_val(1, 0, size, a, b);
    }

    void add(int32_t a, int32_t b, T val) {
        _add(1, 0, size, a, b, val);
    }
};

struct CoordElem {
    uint32_t val, pos;

    bool operator==(const CoordElem &other) const {
        return val == other.val && pos == other.pos;
    }

    bool operator<(const CoordElem &other) const {
        if (val != other.val) return val < other.val;
        return pos < other.pos;
    }
};

struct Change {
    uint32_t x, v;
};

int main() {
//    freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    uint32_t n, q;
    cin >> n >> q;
//    ordered_multiset<pair<int32_t, int32_t>> om;
    ordered_multiset<uint64_t> om;
    vector<uint32_t> nums(n);
    for (auto &num: nums) cin >> num;
    vector<CoordElem> els;
    for (int32_t i = 0; i < nums.size(); ++i)
        om.insert((static_cast<uint64_t>(nums[i]) << 32) | i), els.emplace_back(nums[i], i);
    vector<Change> changes(q);
    for (auto &[x, v]: changes) cin >> x >> v, --x, els.emplace_back(v, x);
    sort(els.begin(), els.end());
    els.erase(unique(els.begin(), els.end()), els.end());
    vector<int32_t> rr_raw_vals(nums.size());
    int32_t lower_cnt = -1;
    vector<int32_t> st_init_vec(els.size());
    for (uint32_t i = 0; i < els.size(); ++i) {
        auto [val, pos] = els[i];
        if (nums[pos] != val) {
            st_init_vec[i] = -inf;
        } else {
            ++lower_cnt;
            rr_raw_vals[pos] = st_init_vec[i] = pos - lower_cnt;
        }
    }
    SegmentTree<int32_t> st(st_init_vec.size(), st_init_vec);
    for (auto [x, v]: changes) {
        int32_t pos1 = distance(els.begin(),
                                lower_bound(els.begin(), els.end(), CoordElem(nums[x], x)));
        st.add(pos1, pos1 + 1, -inf - rr_raw_vals[x]);
        st.add(pos1 + 1, st.size, 1);
        om.erase(om.find_by_order(om.order_of_key((static_cast<uint64_t>(nums[x]) << 32) | x)));
        nums[x] = v;
        om.insert((static_cast<uint64_t>(nums[x]) << 32) | x);
        pos1 = distance(els.begin(), lower_bound(els.begin(), els.end(), CoordElem(nums[x], x)));
        int32_t nrw = x - om.order_of_key((static_cast<uint64_t>(nums[x]) << 32) | x);
        st.add(pos1, pos1 + 1, nrw - st.max_val(pos1, pos1 + 1));
        rr_raw_vals[x] = nrw;
        st.add(pos1 + 1, st.size, -1);
        cout << max(st.max_val(0, st.size), static_cast<int32_t>(0)) << "\n";
    }
    return 0;
}
