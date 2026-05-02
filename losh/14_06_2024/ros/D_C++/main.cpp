//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2")
//#pragma GCC optimize("unroll-loops")


#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <set>
#include <ctime>
#include <cassert>

using namespace std;

namespace FullSol {
    const int64_t inf = 1e9;

//    template<typename T>
//    class SegmentTree {
//    public:
    namespace orig_st {
        using T = int64_t;

        struct Node {
            T max_val = 0, min_val = 0, best_x_y_dif = -inf, best_y_x_dif = -inf;
            int64_t min_pos, max_pos;
        };

        struct XYAns {
            T dif, min_val, max_val;
        };

        int64_t size;
        vector<Node> tree;

        void update_by_child(int64_t id) {
            auto &tt = tree[id], &tl = tree[id * 2], &tr = tree[id * 2 + 1];
            if (tl.max_val > tr.max_val) tt.max_val = tl.max_val, tt.max_pos = tl.max_pos;
            else tt.max_val = tr.max_val, tt.max_pos = tr.max_pos;
            if (tl.min_val < tr.min_val) tt.min_val = tl.min_val, tt.min_pos = tl.min_pos;
            else tt.min_val = tr.min_val, tt.min_pos = tr.min_pos;
            int64_t bd_x_y = tl.best_x_y_dif;
            if (tr.best_x_y_dif > bd_x_y) bd_x_y = tr.best_x_y_dif;
            if (tr.max_val - tl.min_val > bd_x_y) bd_x_y = tr.max_val - tl.min_val;
            tt.best_x_y_dif = bd_x_y;
            int64_t bd_y_x = tl.best_y_x_dif;
            if (tr.best_y_x_dif > bd_y_x) bd_y_x = tr.best_y_x_dif;
            if (tl.max_val - tr.min_val > bd_y_x) bd_y_x = tl.max_val - tr.min_val;
            tt.best_y_x_dif = bd_y_x;
        }

        void _init(int64_t id, int64_t l, int64_t r, const int64_t nums[]) {
            if (l >= r) return;
            if (r - l == 1)
                tree[id].max_val = tree[id].min_val = nums[l], tree[id].min_pos = tree[id].max_pos = l;
            else {
                _init(id * 2, l, (l + r) / 2, nums);
                _init(id * 2 + 1, (l + r) / 2, r, nums);
                update_by_child(id);
            }
        }

        T _max_val(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
            if (l >= r || b <= l || r <= a) return -inf;
            if (a <= l && b >= r) return tree[id].max_val;
            return max(_max_val(id * 2, l, (l + r) / 2, a, b), _max_val(id * 2 + 1, (l + r) / 2, r, a, b));
        }

        T _min_val(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
            if (l >= r || b <= l || r <= a) return inf;
            if (a <= l && b >= r) return tree[id].min_val;
            return min(_min_val(id * 2, l, (l + r) / 2, a, b), _min_val(id * 2 + 1, (l + r) / 2, r, a, b));
        }

        pair<int64_t, T> _min_pos(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
            if (l >= r || b <= l || r <= a) return {-1, inf};
            if (a <= l && b >= r) return {tree[id].min_pos, tree[id].min_val};
            auto r1 = _min_pos(id * 2, l, (l + r) / 2, a, b),
                    r2 = _min_pos(id * 2 + 1, (l + r) / 2, r, a, b);
            return r1.second < r2.second ? r1 : r2;
        }

        XYAns _best_xy_dif(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
            if (l >= r || b <= l || r <= a) return {-inf, inf, -inf};
            if (l + 1 >= r) return {-inf, tree[id].min_val, tree[id].max_val};
            if (a <= l && b >= r) return {tree[id].best_x_y_dif, tree[id].min_val, tree[id].max_val};
            XYAns bd1 = _best_xy_dif(id * 2, l, (l + r) / 2, a, b),
                    bd2 = _best_xy_dif(id * 2 + 1, (l + r) / 2, r, a, b), bd3 = {-inf, inf, -inf};
            if (a < (l + r) / 2 && b >= (l + r) / 2) {
//                int64_t dif = (bd2.max_val <= -inf || bd1.min_val >= inf) ? -inf : bd2.max_val - bd1.min_val;
                bd3 = {bd2.max_val - bd1.min_val, 0, 0};
//                bd3 = {bd2.max_val - bd1.min_val, min(bd1.min_val, bd2.min_val), max(bd1.max_val, bd2.max_val)};
            }
            return {max(max(bd1.dif, bd2.dif), bd3.dif), min(bd1.min_val, bd2.min_val), max(bd1.max_val, bd2.max_val)};
        }

        XYAns _best_yx_dif(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
            if (l >= r || b <= l || r <= a) return {-inf, inf, -inf};
            if (l + 1 >= r) return {-inf, tree[id].min_val, tree[id].max_val};
            if (a <= l && b >= r) return {tree[id].best_y_x_dif, tree[id].min_val, tree[id].max_val};
            XYAns bd1 = _best_yx_dif(id * 2, l, (l + r) / 2, a, b),
                    bd2 = _best_yx_dif(id * 2 + 1, (l + r) / 2, r, a, b), bd3 = {-inf, inf, -inf};
            if (a < (l + r) / 2 && b >= (l + r) / 2) {
                bd3 = {bd1.max_val - bd2.min_val, 0, 0};
            }
            return {max(max(bd1.dif, bd2.dif), bd3.dif), min(bd1.min_val, bd2.min_val), max(bd1.max_val, bd2.max_val)};
        }

        int32_t _rightest_higher_equal_cnt = 0;

        int64_t _rightest_higher_equal(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b, T val) {
//            if (l >= r || b <= l || r <= a || _max_val(id, l, r, a, b) < val) return -1;
            ++_rightest_higher_equal_cnt;
            if (l >= r || b <= l || r <= a || tree[id].max_val < val) return -1;
            if (r - l == 1) return tree[id].max_val >= val ? l : -1;
            else {
                int64_t res = _rightest_higher_equal(id * 2 + 1, (l + r) / 2, r, a, b, val);
                if (res == -1) res = _rightest_higher_equal(id * 2, l, (l + r) / 2, a, b, val);
                return res;
            }
        }

        int32_t _rightest_lower_cnt = 0;

        int64_t _rightest_lower(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b, T val) {
//            if (l >= r || b <= l || r <= a || _min_val(id, l, r, a, b) >= val) return -1;
            ++_rightest_lower_cnt;
            if (l >= r || b <= l || r <= a || tree[id].min_val >= val) return -1;
            if (r - l == 1) return tree[id].min_val < val ? l : -1;
            else {
                int64_t res = _rightest_lower(id * 2 + 1, (l + r) / 2, r, a, b, val);
                if (res == -1) res = _rightest_lower(id * 2, l, (l + r) / 2, a, b, val);
                return res;
            }
        }

        int32_t _leftest_higher_equal_cnt = 0;

        int64_t _leftest_higher_equal(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b, T val) {
//            if (l >= r || b <= l || r <= a || _max_val(id, l, r, a, b) < val) return -1;
            ++_leftest_higher_equal_cnt;
            if (l >= r || b <= l || r <= a || tree[id].max_val < val) return -1;
            if (r - l == 1) return tree[id].max_val >= val ? l : -1;
            else {
                int64_t res = _leftest_higher_equal(id * 2, l, (l + r) / 2, a, b, val);
                if (res == -1) res = _leftest_higher_equal(id * 2 + 1, (l + r) / 2, r, a, b, val);
                return res;
            }
        }

        int32_t _leftest_lower_cnt = 0;

        int64_t _leftest_lower(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b, T val) {
//            if (l >= r || b <= l || r <= a || _min_val(id, l, r, a, b) >= val) return -1;
            ++_leftest_lower_cnt;
//            cout << "Node: " << id << " " << l << " " << r << " " << a << " " << b << " " << val << " " << "\n";
//            cout.flush();
            if (l >= r || b <= l || r <= a || tree[id].min_val >= val) return -1;
            if (r - l == 1) return tree[id].min_val < val ? l : -1;
            else {
                int64_t res = _leftest_lower(id * 2, l, (l + r) / 2, a, b, val);
                if (res == -1) res = _leftest_lower(id * 2 + 1, (l + r) / 2, r, a, b, val);
                return res;
            }
        }

//        explicit SegmentTree(int64_t size, const int64_t nums[]) : size(size), tree(size * 4) {
//            _init(1, 0, size, nums);
//        }
//
//        explicit SegmentTree() = default;

        void assign(int64_t nums_size, const int64_t nums[]) {
            size = nums_size;
            tree.clear();
            tree.resize(size * 4);
            _init(1, 0, size, nums);
        }

        const int32_t test_spusk_max = 12;

        int64_t rightest_lower(int64_t a, int64_t b, T val) {
            _rightest_lower_cnt = 0;
            int64_t res = _rightest_lower(1, 0, size, a, b, val);
            if (_rightest_lower_cnt > test_spusk_max) {
//                assert(false);
            }
            return res;
        }

        int64_t leftest_lower(int64_t a, int64_t b, T val) {
            _leftest_lower_cnt = 0;
            int64_t res = _leftest_lower(1, 0, size, a, b, val);
//            cout << "\n\n";
            if (_leftest_lower_cnt > test_spusk_max) {
//                assert(false);
            }
            return res;
        }

        int64_t rightest_higher_equal(int64_t a, int64_t b, T val) {
            _rightest_higher_equal_cnt = 0;
            int64_t res = _rightest_higher_equal(1, 0, size, a, b, val);
            if (_rightest_higher_equal_cnt > test_spusk_max) {
//                assert(false);
            }
            return res;
        }

        int64_t leftest_higher_equal(int64_t a, int64_t b, T val) {
            _leftest_higher_equal_cnt = 0;
            int64_t res = _leftest_higher_equal(1, 0, size, a, b, val);
            if (_leftest_higher_equal_cnt > test_spusk_max) {
//                assert(false);
            }
            return res;
        }

        T max_val(int64_t a, int64_t b) {
            return _max_val(1, 0, size, a, b);
        }

        T min_val(int64_t a, int64_t b) {
            return _min_val(1, 0, size, a, b);
        }

        int64_t min_pos(int64_t a, int64_t b) {
            return _min_pos(1, 0, size, a, b).first;
        }

        T best_xy_dif(int64_t a, int64_t b) {
            return _best_xy_dif(1, 0, size, a, b).dif;
        }

        T best_yx_dif(int64_t a, int64_t b) {
            return _best_yx_dif(1, 0, size, a, b).dif;
        }
//    };
    }
//    class PersistentSegmentTree {
//    public:
    namespace pers_st {
        static const int64_t maxpstn = 5e6;
        struct Node {
            int64_t sum, max_val, l_id, r_id;
        };
        Node tree[maxpstn];
        int64_t used = 0, size;

        map<int64_t, int64_t> versions;

        void _init(int64_t id, int64_t l, int64_t r, const vector<int64_t> &vals) {
            if (l >= r) tree[id].sum = 0, tree[id].max_val = -inf;
            if (r - l == 1) tree[id].sum = tree[id].max_val = vals[l];
            else {
                tree[id].l_id = used++, tree[id].r_id = used++;
                _init(tree[id].l_id, l, (l + r) / 2, vals);
                _init(tree[id].r_id, (l + r) / 2, r, vals);
                tree[id].sum = tree[tree[id].l_id].sum + tree[tree[id].r_id].sum;
                tree[id].max_val = max(tree[tree[id].l_id].max_val, tree[tree[id].r_id].max_val);
            }
        }

        void init(int64_t n, int64_t start_d, const vector<int64_t> &vals) {
            for (int64_t i = 0; i < pers_st::maxpstn; ++i) {
                tree[i].l_id = -1;
                tree[i].r_id = -1;
                tree[i].sum = 0;
                tree[i].max_val = 0;
            }
            used = 1, size = n;
            versions.clear();
            _init(0, 0, n, vals);
            versions.emplace(start_d, 0);
        }

        void _add(int64_t id, int64_t l, int64_t r, int64_t pos, int64_t val) {
            if (l >= r || pos < l || r <= pos) return;
            if (r - l == 1) tree[id].sum += val, tree[id].max_val += val;
            else {
                int64_t nl_id = used++, nr_id = used++;
                tree[nl_id] = tree[tree[id].l_id], tree[nr_id] = tree[tree[id].r_id];
                tree[id].l_id = nl_id, tree[id].r_id = nr_id;
                _add(tree[id].l_id, l, (l + r) / 2, pos, val);
                _add(tree[id].r_id, (l + r) / 2, r, pos, val);
                tree[id].sum = tree[tree[id].l_id].sum + tree[tree[id].r_id].sum;
                tree[id].max_val = max(tree[tree[id].l_id].max_val, tree[tree[id].r_id].max_val);
            }
        }

        int64_t _sum(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
            if (l >= r || b <= l || r <= a) return 0;
            if (a <= l && r <= b) return tree[id].sum;
            return _sum(tree[id].l_id, l, (l + r) / 2, a, b) + _sum(tree[id].r_id, (l + r) / 2, r, a, b);
        }

        int64_t _max_val(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
            if (l >= r || b <= l || r <= a) return -inf;
            if (a <= l && r <= b) return tree[id].max_val;
            return max(_max_val(tree[id].l_id, l, (l + r) / 2, a, b), _max_val(tree[id].r_id, (l + r) / 2, r, a, b));
        }

        int32_t _leftest_non_zero_cnt = 0;

        int64_t _leftest_non_zero(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
//            if (l >= r || b <= l || r <= a || _max_val(id, l, r, a, b) < 1) return -1;
            ++_leftest_non_zero_cnt;
            if (l >= r || b <= l || r <= a || tree[id].max_val < 1) return -1;
            if (r - l == 1) return tree[id].max_val >= 1 ? l : -1;
            else {
                int64_t res = _leftest_non_zero(tree[id].l_id, l, (l + r) / 2, a, b);
                if (res == -1) res = _leftest_non_zero(tree[id].r_id, (l + r) / 2, r, a, b);
                return res;
            }
        }

        int32_t _rightest_non_zero_cnt = 0;

        int64_t _rightest_non_zero(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
//            if (l >= r || b <= l || r <= a || _max_val(id, l, r, a, b) < 1) return -1;
            ++_rightest_non_zero_cnt;
            if (l >= r || b <= l || r <= a || tree[id].max_val < 1) return -1;
            if (r - l == 1) return tree[id].max_val >= 1 ? l : -1;
            else {
                int64_t res = _rightest_non_zero(tree[id].r_id, (l + r) / 2, r, a, b);
                if (res == -1) res = _rightest_non_zero(tree[id].l_id, l, (l + r) / 2, a, b);
                return res;
            }
        }

        int64_t best_version(int64_t req_d) {
            return prev(versions.upper_bound(req_d))->first;
        }

        void add_version(int64_t d, const vector<int64_t> &removes_after_last) {
            int64_t pre_version = best_version(d);
            if (pre_version == d) return;
            int64_t now_root = versions[pre_version];
            for (int pos: removes_after_last) {
                int64_t new_root = used++;
                tree[new_root] = tree[now_root];
                now_root = new_root;
                _add(now_root, 0, size, pos, -1);
            }
            versions.emplace(d, now_root);
        }

        int64_t sum(int64_t d, int64_t a, int64_t b) {
            return _sum(versions.find(d)->second, 0, size, a, b);
        }

        int64_t leftest_non_zero(int64_t d, int64_t a, int64_t b) {
            _leftest_non_zero_cnt = 0;
            auto res = _leftest_non_zero(versions.find(d)->second, 0, size, a, b);
            if (_leftest_non_zero_cnt > 80) {
                assert(false);
            }
            return res;
        }

        int64_t rightest_non_zero(int64_t d, int64_t a, int64_t b) {
            int32_t _rightest_non_zero_cnt = 0;
            auto res = _rightest_non_zero(versions.find(d)->second, 0, size, a, b);
            if (_rightest_non_zero_cnt > 80) {
                assert(false);
            }
            return res;
        }
    };

    const int64_t maxn = 1e5;
    int64_t n;
    int64_t heights[maxn], first_bad_d[maxn];
//    SegmentTree<int64_t> orig_st;
//    PersistentSegmentTree pers_st;
    vector<int64_t> temp_to_del_vec;
    map<int64_t, vector<int64_t>> remove_with_d;

    void init_sol(int64_t _n, const vector<int64_t> &v_heights) {
        n = _n;
        for (int64_t i = 0; i < n; ++i) heights[i] = v_heights[i];
        orig_st::assign(n, heights);
        for (int64_t i = 0; i < n; ++i) {
            int64_t lb = orig_st::rightest_lower(0, i, heights[i]);
            int64_t ls = orig_st::max_val(lb == -1 ? 0 : lb + 1, i);
            int64_t rb = orig_st::leftest_lower(i + 1, n, heights[i]);
            int64_t rs = orig_st::max_val(i + 1, rb == -1 ? n : rb);
            if ((lb != -1 && ls == -inf) || (rb != -1 && rs == -inf)) first_bad_d[i] = 1;
            else if (lb == -1 && rb == -1) first_bad_d[i] = inf;
            else {
                int64_t md = min((lb != -1 ? ls : rs), (rb != -1 ? rs : ls)) - heights[i];
                if (md <= 0) first_bad_d[i] = 1;
                else first_bad_d[i] = md + 1;
            }
        }
        remove_with_d.clear();
        for (int64_t i = 0; i < n; ++i) {
            auto it = remove_with_d.find(first_bad_d[i]);
            if (it != remove_with_d.end()) it->second.push_back(i);
            else remove_with_d.emplace(first_bad_d[i], vector<int64_t>{i});
        }
        vector<int64_t> start_st_vals(n, 1);
        for (int64_t i = 0; i < n; ++i) if (first_bad_d[i] <= 1) start_st_vals[i] = 0;
        pers_st::init(n, 1, start_st_vals);
    }

    int64_t process_req(int64_t l, int64_t r, int64_t d) { // [l, r], d
        ++r;
        int64_t ex_d = pers_st::best_version(d);
        if (ex_d != d) {
            for (auto it = remove_with_d.upper_bound(ex_d); it != remove_with_d.end() && it->first <= d;
                 ++it) {
                temp_to_del_vec.clear();
                for (auto td: it->second)
                    temp_to_del_vec.push_back(td);
                pers_st::add_version(it->first, temp_to_del_vec);
            }
            temp_to_del_vec.clear();
            pers_st::add_version(d, temp_to_del_vec);
        }
        int64_t res = pers_st::sum(d, l, r);
        int64_t ls = pers_st::leftest_non_zero(d, l, r);
        int64_t rs = pers_st::rightest_non_zero(d, l, r);
        if (ls == -1 || rs == -1) {
            res = 1;
            ls = rs = orig_st::min_pos(l, r);
        }
        if (ls - l >= 2) {
            int64_t ald = orig_st::rightest_higher_equal(l + 1, ls, heights[ls] + d);
            if (ald != -1) {
                int64_t bxy = orig_st::best_xy_dif(l, ald + 1);
                if (bxy >= d) ++res;
            }
        }
        if (r - rs >= 3) {
            int64_t ard = orig_st::leftest_higher_equal(rs + 1, r, heights[rs] + d);
            if (ard != -1) {
                int64_t byx = orig_st::best_yx_dif(ard, r);
                if (byx >= d) ++res;
            }
        }
        return res;
    }
}
//
//namespace StupidSol {
//    vector<int64_t> heights;
//    vector<bool> used;
//    int64_t best_sol, l, r, d;
//
//    void init_sol(int64_t _n, const vector<int64_t> &vec_heights) {
//        heights = vec_heights;
//        used.assign(heights.size(), false);
//    }
//
//    void rec_sol(int64_t layer) {
//        if (layer == r) {
//            bool ok = true;
//            for (int64_t i = l; i < r && ok; ++i) {
//                if (!used[i]) continue;
//                for (int64_t j = i + 1; j < r && ok; ++j) {
//                    if (!used[j]) continue;
//                    bool ex = false;
//                    for (int64_t k = i + 1; k < j; ++k) {
//                        if (heights[k] >= heights[i] + d && heights[k] >= heights[j] + d) {
//                            ex = true;
//                            break;
//                        }
//                    }
//                    if (!ex) ok = false;
//                }
//            }
//            if (ok) {
//                int64_t cr = 0;
//                for (int64_t i = l; i < r; ++i) if (used[i]) ++cr;
//                if (cr > best_sol) best_sol = cr;
//            }
//            return;
//        }
//        used[layer] = false;
//        rec_sol(layer + 1);
//        used[layer] = true;
//        rec_sol(layer + 1);
//    }
//
//    int64_t process_req(int64_t _l, int64_t _r, int64_t _d) {
//        best_sol = 0, l = _l, r = _r + 1, d = _d;
//        rec_sol(_l);
//        return best_sol;
//    }
//}

namespace AboutStupidSol {
    vector<int64_t> heights;

    void init_sol(int64_t _n, const vector<int64_t> &vec_heights) {
        heights = vec_heights;
    }

    int64_t process_req(int64_t l, int64_t r, int64_t d) {
        ++r;
        int64_t res = 0;
        vector<pair<int64_t, int64_t>> sort_vals;
        for (int64_t i = l; i < r; ++i) sort_vals.emplace_back(heights[i], i);
        sort(sort_vals.begin(), sort_vals.end(), [](const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) {
            return a.first < b.first;
        });
        for (auto [val, pos]: sort_vals) {
            int64_t lb = l;
            for (int64_t i = lb; i < pos; ++i) if (heights[i] >= val + d) lb = i + 1;
            int64_t rb = r;
            for (int64_t i = rb - 1; i > pos; --i) if (heights[i] >= val + d) rb = i;
            bool ok = true;
            for (int64_t i = lb; i < rb; ++i) if (heights[i] < val) ok = false;
            if (ok) ++res;
        }
        return res;
    }
}

namespace Test {
    random_device dev;
    uint64_t seed = dev();
//    uint64_t seed = 1065656568;
    mt19937 rng(seed);

    struct Que {
        int64_t l, r, d;
    };

    template<typename T>
    T randint(T a, T b) {
        return uniform_int_distribution(a, b)(rng);
    }

    pair<vector<int64_t>, vector<Que>> gen(int64_t maxlen, int64_t maxcmd, int64_t _n = -1, int64_t _q = -1) {
        int64_t n = _n == -1 ? randint<int64_t>(1, maxlen) : _n, q = _q == -1 ? randint<int64_t>(1, maxcmd) : _q;
        set<int64_t> s_h;
        while (s_h.size() < n) s_h.insert(randint<int64_t>(1, n * 10));
        vector<int64_t> heights(s_h.begin(), s_h.end());
        shuffle(heights.begin(), heights.end(), rng);
        vector<Que> ques(q);
        for (auto &[l, r, d]: ques) {
            l = randint<int64_t>(0, n - 1);
            r = randint<int64_t>(l, n - 1);
            d = randint<int64_t>(1, 50);
        }
        return {heights, ques};
    }

    void print_input_output(const vector<int64_t> &heights, const vector<Que> &ques, const vector<int64_t> &f_ans,
                            const vector<int64_t> &s_ans) {
        cout << heights.size() << " " << ques.size() << "\n";
        for (auto h: heights) cout << h << " ";
        cout << "\n";
        for (auto [l, r, d]: ques) cout << l << " " << r << " " << d << "\n";
        cout << "\nFull sol:\n";
        for (auto v: f_ans) cout << v << " ";
        cout << "\nStupid sol:\n";
        for (auto v: s_ans) cout << v << " ";
        cout << "\n\n";
    }

    void Test() {
        cout << "seed: " << seed << "\n\n";
        cout.flush();
        while (true) {
            auto [heights, ques] = gen(16, 1, 16, 1);
            vector<int64_t> f_ans, s_ans;
            print_input_output(heights, ques, f_ans, s_ans);
            cout.flush();
            FullSol::init_sol(heights.size(), heights);
            AboutStupidSol::init_sol(heights.size(), heights);
            for (auto [l, r, d]: ques) {
                f_ans.push_back(FullSol::process_req(l, r, d));
                s_ans.push_back(AboutStupidSol::process_req(l, r, d));
            }
//            print_input_output(heights, ques, f_ans, s_ans);
            if (f_ans != s_ans) {
                print_input_output(heights, ques, f_ans, s_ans);
                break;
            }
        }
    }

    void input_test() {
        int64_t n, q;
        cin >> n >> q;
        vector<int64_t> heights(n);
        vector<Que> ques(q);
        for (auto &h: heights) cin >> h;
        for (auto &[l, r, d]: ques) cin >> l >> r >> d;
        FullSol::init_sol(heights.size(), heights);
        AboutStupidSol::init_sol(heights.size(), heights);
        vector<int64_t> f_ans, s_ans;
        for (auto [l, r, d]: ques) {
            f_ans.push_back(FullSol::process_req(l, r, d));
            s_ans.push_back(AboutStupidSol::process_req(l, r, d));
        }
        print_input_output(heights, ques, f_ans, s_ans);
    }

    void big_test() {
        auto [heights, ques] = gen(1e5, 1e5, 1e5, 1e5);
        cout << "gend\n";
        cout.flush();
        auto time = clock();
        FullSol::init_sol(heights.size(), heights);
        vector<int64_t> f_ans, s_ans;
        cerr << (clock() - time) * 1. / CLOCKS_PER_SEC;
        for (auto [l, r, d]: ques) {
            f_ans.push_back(FullSol::process_req(l, r, d));
        }
        print_input_output(heights, ques, f_ans, s_ans);
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
//    Test::Test();
//    Test::input_test();
//    Test::big_test();
    int64_t n, q;
    cin >> n >> q;
    vector<int64_t> heights(n);
    for (auto &num: heights) cin >> num;
    FullSol::init_sol(n, heights);
    for (int64_t i = 0, l, r, d; i < q; ++i) {
        cin >> l >> r >> d;
        cout << FullSol::process_req(l, r, d) << "\n";
        cout.flush();
    }
    return 0;
}
