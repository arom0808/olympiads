#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdint>
#include <set>
//#include <random>

using namespace std;

template<typename T>
class SegmentTree {
public:
    struct Elem {
        T max_val = 0, change = 0;
    };

    int64_t size;
    vector<Elem> tree;

    void _init(int64_t id, int64_t l, int64_t r, const vector<T> &values) {
        if (l >= r) return;
        if (r - l == 1) tree[id].max_val = values[l];
        else {
            _init(id * 2, l, (l + r) / 2, values);
            _init(id * 2 + 1, (l + r) / 2, r, values);
        }
    }

    inline void transfer_change(int64_t id) {
        if (!tree[id].change) return;
        if (id * 2 + 1 < tree.size()) {
            tree[id * 2].max_val += tree[id].change, tree[id * 2].change += tree[id].change;
            tree[id * 2 + 1].max_val += tree[id].change, tree[id * 2 + 1].change += tree[id].change;
        }
        tree[id].change = 0;
    }

    void _add(int64_t id, int64_t l, int64_t r, int64_t req_l, int64_t req_r, T val) {
        if (l >= r || req_r <= l || r <= req_l) return;
        transfer_change(id);
        if (req_l <= l && r <= req_r) {
            tree[id].max_val += val, tree[id].change += val;
            return;
        } else if (r - l == 1) return;
        _add(id * 2, l, (l + r) / 2, req_l, req_r, val);
        _add(id * 2 + 1, (l + r) / 2, r, req_l, req_r, val);
        tree[id].max_val = max(tree[id * 2].max_val, tree[id * 2 + 1].max_val);
    }

    T _get_max(int64_t id, int64_t l, int64_t r, int64_t req_l, int64_t req_r) {
        if (l >= r || req_r <= l || r <= req_l) return 0;
        transfer_change(id);
        if (req_l <= l && r <= req_r) return tree[id].max_val;
        else if (r - l == 1) return 0;
        return max(_get_max(id * 2, l, (l + r) / 2, req_l, req_r), _get_max(id * 2 + 1, (l + r) / 2, r, req_l, req_r));
    }

    explicit SegmentTree(int64_t n) : size(n), tree(n * 4) {}

    explicit SegmentTree(const vector<T> &values) : size(values.size()), tree(values.size() * 4) {
        _init(1, 0, size, values);
    }

    inline void add(int64_t l, int64_t r, T val) {
        _add(1, 0, size, l, r, val);
    }

    inline T get_max(int64_t l, int64_t r) {
        return _get_max(1, 0, size, l, r);
    }
};

inline int64_t get_nearest_to_right(const set<int64_t> &s, int64_t from, int64_t to) {
    auto it = s.lower_bound(to);
    if (it != s.begin() && *prev(it) >= from) return *prev(it);
    else return -1;
}

inline int64_t get_nearest_to_left(const set<int64_t> &s, int64_t from, int64_t to) {
    auto it = s.lower_bound(from);
    if (it != s.end() && *it < to) return *it;
    else return -1;
}

inline int64_t
get_value_for_max(int64_t id, int64_t n, const set<int64_t> &maximums, const set<int64_t> &minimums) {
    int64_t left_max = get_nearest_to_right(maximums, 0, id);
    int64_t right_max = get_nearest_to_left(maximums, id + 1, n);
    int64_t left_border = left_max == -1 ? 0 : left_max + 1;
    int64_t right_border = right_max == -1 ? n : right_max;
    int64_t left_min = get_nearest_to_right(minimums, left_border, id);
    int64_t right_min = get_nearest_to_left(minimums, id + 1, right_border);
    if (left_min == -1 && right_min == -1) return 1;
    if (left_min == -1) return right_min - id + 1;
    if (right_min == -1) return id - left_min + 1;
    return right_min - left_min + 1;
}

int main() {
//    Test::Test();
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int64_t n, m;
    cin >> n;
    vector<int64_t> start_spice(n);
    vector<int64_t> upd(n, 0);
    for (auto &val: start_spice) cin >> val;
    SegmentTree<int64_t> values(start_spice);
//    SegmentTree<int64_t> maximums(n), minimums(n);
    vector<int64_t> vec_maximums(n), vec_minimums(n);
    set<int64_t> maximums, minimums;
    multiset<int64_t> maximums_ms;
    cin >> m;
    if (n == 1) {
        for (int64_t i = 0; i < m; ++i) cout << 1 << "\n";
        return 0;
    }
    if (start_spice[0] < start_spice[1]) minimums.insert(0), vec_minimums[0] = 1;
    else if (start_spice[0] > start_spice[1]) maximums.insert(0), vec_maximums[0] = 1, maximums_ms.insert(1);
    if (start_spice[n - 2] < start_spice[n - 1]) maximums.insert(n - 1), vec_maximums[n - 1] = 1, maximums_ms.insert(1);
    else if (start_spice[n - 2] > start_spice[n - 1]) minimums.insert(n - 1), vec_minimums[n - 1] = 1;
    for (int64_t i = 1; i + 1 < n; ++i) {
        auto v1 = start_spice[i - 1], v2 = start_spice[i], v3 = start_spice[i + 1];
        if (v1 < v2 && v2 >= v3 || v1 == v2 && v2 > v3) maximums.insert(i), vec_maximums[i] = 1, maximums_ms.insert(1);
        else if (v1 > v2 && v2 <= v3 || v1 == v2 && v2 < v3) minimums.insert(i), vec_minimums[i] = 1;
    }
    for (int64_t i = 0; i < n; ++i) {
        if (vec_maximums[i] == 0) continue;
        maximums_ms.erase(vec_maximums[i]);
        vec_maximums[i] = get_value_for_max(i, n, maximums, minimums);
        maximums.insert(i);
        maximums_ms.insert(vec_maximums[i]);
    }
    set<int64_t> to_check;
    int64_t l, r;
    int64_t a;
    int64_t timer = 0;
    for (int64_t i = 0; i < m; ++i) {
        cin >> l >> r >> a, --l;
        to_check.clear();
        values.add(l, r, a);
        ++timer;
        if (l > 0) to_check.insert(l - 1);
        to_check.insert(l);
        if (l + 1 < n) to_check.insert(l + 1);
        if (r > 1) to_check.insert(r - 2);
        to_check.insert(r - 1);
        if (r < n) to_check.insert(r);
        to_check.insert(get_nearest_to_right(maximums, 0, l));
        to_check.insert(get_nearest_to_left(maximums, l + 1, n));
        to_check.insert(get_nearest_to_right(maximums, 0, r - 1));
        to_check.insert(get_nearest_to_left(maximums, r, n));
        to_check.erase(-1);
        for (auto pos: to_check) {
            for (int64_t j = (pos > 0 ? pos - 1 : 0); j <= (pos + 1 < n ? pos + 1 : pos); ++j) {
                if (upd[j] == timer) continue;
                upd[j] = timer;
                start_spice[j] = values.get_max(j, j + 1);
            }
        }
        for (auto pos: to_check) {
            if (pos < 0 || pos >= n) continue;
            int64_t v2 = start_spice[pos];
            int64_t v1 = pos == 0 ? v2 : start_spice[pos - 1];
            int64_t v3 = pos + 1 == n ? v2 : start_spice[pos + 1];
            if (v1 < v2 && v2 >= v3 || v1 == v2 && v2 > v3) {
                if (vec_maximums[pos] == 0) {
                    maximums.insert(pos);
                    vec_maximums[pos] = 1;
                    maximums_ms.insert(1);
                }
                if (vec_minimums[pos] != 0) {
                    minimums.erase(pos);
                    vec_minimums[pos] = 0;
                }
            } else if (v1 > v2 && v2 <= v3 || v1 == v2 && v2 < v3) {
                if (vec_minimums[pos] == 0) {
                    minimums.insert(pos);
                    vec_minimums[pos] = 1;
                }
                if (vec_maximums[pos] != 0) {
                    maximums_ms.erase(vec_maximums[pos]);
                    maximums.erase(pos);
                    vec_maximums[pos] = 0;
                }
            } else {
                if (vec_minimums[pos] != 0) {
                    minimums.erase(pos);
                    vec_minimums[pos] = 0;
                }
                if (vec_maximums[pos] != 0) {
                    maximums_ms.erase(vec_maximums[pos]);
                    maximums.erase(pos);
                    vec_maximums[pos] = 0;
                }
            }
        }
        for (auto pos: to_check) {
            if (vec_maximums[pos] == 0) continue;
            maximums_ms.erase(vec_maximums[pos]);
            vec_maximums[pos] = get_value_for_max(pos, n, maximums, minimums);
            maximums_ms.insert(vec_maximums[pos]);
            maximums.insert(pos);
        }
        if (!maximums_ms.empty()) cout << max(1ll, *maximums_ms.rbegin()) << "\n";
        else cout << 1 << "\n";
    }
    return 0;
}
