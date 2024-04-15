#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

const uint32_t inf = 2e9;

class SparseTable2d {
    vector<vector<vector<vector<uint32_t>>>> st;

public:
    explicit SparseTable2d(const vector<vector<uint32_t>> &nums) : st(nums.size(), vector<vector<vector<uint32_t>>>(
            nums.front().size(),
            vector<vector<uint32_t>>(__lg(nums.size()) + 1, vector<uint32_t>(__lg(nums.front().size()) + 1)))) {
        for (uint32_t i = 0; i < nums.size(); ++i)
            for (uint32_t j = 0; j < nums[i].size(); ++j)
                st[i][j][0][0] = nums[i][j];
        for (uint32_t k1 = 1; k1 < st.front().front().size(); ++k1)
            for (uint32_t i = 0; i + (1 << (k1 - 1)) < nums.size(); ++i)
                for (uint32_t k2 = 0; k2 < st.front().front().front().size(); ++k2)
                    for (uint32_t j = 0; j < st.front().size(); ++j)
                        st[i][j][k1][k2] = std::max(st[i][j][k1 - 1][k2], st[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
    }

    uint32_t max(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2) {
        uint32_t k1 = __lg(x2 - x1), k2 = __lg(y2 - y1);
        uint32_t ans = st[x1][y1][k1][k2];
        ans = std::max(ans, st[x2 - (1 << k1)][y1][k1][k2]);
        ans = std::max(ans, st[x1][y2 - (1 << k2)][k1][k2]);
        ans = std::max(ans, st[x2 - (1 << k1)][y2 - (1 << k2)][k1][k2]);
        return ans;
    }
};

class SparseTable {
    vector<vector<pair<uint32_t, uint32_t>>> st_min, st_max;

    void init_rows() {
        for (uint32_t k = 1; k < st_min.size(); ++k) {
            for (uint32_t i = 0; i + (1 << (k - 1)) < st_min[k].size(); ++i) {
                auto [v1, p1] = st_min[k - 1][i];
                auto [v2, p2] = st_min[k - 1][i + (1 << (k - 1))];
                if (v1 < v2 || (v1 == v2 && p1 < p2)) st_min[k][i] = st_min[k - 1][i];
                else st_min[k][i] = st_min[k - 1][i + (1 << (k - 1))];
            }
        }
        for (uint32_t k = 1; k < st_max.size(); ++k) {
            for (uint32_t i = 0; i + (1 << (k - 1)) < st_max[k].size(); ++i) {
                auto [v1, p1] = st_max[k - 1][i];
                auto [v2, p2] = st_max[k - 1][i + (1 << (k - 1))];
                if (v1 > v2 || (v1 == v2 && p1 > p2)) st_max[k][i] = st_max[k - 1][i];
                else st_max[k][i] = st_max[k - 1][i + (1 << (k - 1))];
            }
        }
    }

public:
    [[nodiscard]] uint32_t left_min_pos(uint32_t l, uint32_t r) const {
        uint32_t k = __lg(r - l);
        auto [v1, p1] = st_min[k][l];
        auto [v2, p2] = st_min[k][r - (1 << k)];
        if (v1 < v2 || (v1 == v2 && p1 < p2)) return p1;
        return p2;
    }

    [[nodiscard]] uint32_t min(uint32_t l, uint32_t r) const {
        uint32_t k = __lg(r - l);
        auto [v1, p1] = st_min[k][l];
        auto [v2, p2] = st_min[k][r - (1 << k)];
        if (v1 < v2) return v1;
        return v2;
    }

    [[nodiscard]] uint32_t right_max_pos(uint32_t l, uint32_t r) const {
        uint32_t k = __lg(r - l);
        auto [v1, p1] = st_max[k][l];
        auto [v2, p2] = st_max[k][r - (1 << k)];
        if (v1 > v2 || (v1 == v2 && p1 > p2)) return p1;
        return p2;
    }

    explicit SparseTable(const vector<uint32_t> &nums)
            : st_min(__lg(nums.size()) + 1, vector<pair<uint32_t, uint32_t>>(nums.size())),
              st_max(__lg(nums.size()) + 1, vector<pair<uint32_t, uint32_t>>(nums.size())) {
        for (uint32_t i = 0; i < nums.size(); ++i) {
            st_min[0][i].first = st_max[0][i].first = nums[i];
            st_min[0][i].second = st_max[0][i].second = i;
        }
        init_rows();
    }
};

//class MST {
//    struct Node {
//        set<uint32_t> els;
//        uint32_t max_val = 0, max_pos = inf;
//    };
//
//    uint32_t size = 0;
//    vector<Node> nodes;
//
//    void init_node(uint32_t id, uint32_t node_left, uint32_t node_right, const vector<uint32_t> &vec) {
//        if (node_left >= node_right) return;
//        if (node_left + 1 == node_right) {
//            nodes[id].els.insert(vec[node_left]);
//            nodes[id].max_val = vec[node_left], nodes[id].max_pos = node_left;
//            return;
//        }
//        init_node(id * 2, node_left, (node_left + node_right) / 2, vec);
//    }
//
//    MST(const vector<uint32_t> &vec) : size(vec.size()), nodes(vec.size() * 4) {
//        init_node(1, 0, size, vec)
//    }
//};

struct Req {
    uint32_t l, r;
};

void sol1(const vector<uint32_t> &nums, const vector<Req> &reqs, vector<uint32_t> &ans) {
    SparseTable st(nums);
    for (uint32_t i = 0; i < reqs.size(); ++i) {
        auto [l, r] = reqs[i];
        uint32_t best_ans = 0;
        for (--l; l < r; ++l) {
            uint32_t bsl = l, bsr = r;
            while (bsl + 1 < bsr) {
                uint32_t mid = (bsl + bsr) / 2;
                auto m1 = (mid > bsl ? st.min(bsl, mid) : inf);
                auto m2 = (bsr > mid ? st.min(mid, bsr) : inf);
                if (m1 < nums[l]) bsr = mid;
                else if (m2 < nums[l]) bsl = mid;
                else bsl = bsr;
            }
            uint32_t new_r = r;
            if (bsl != bsr) new_r = bsr;
            uint32_t rmp = st.right_max_pos(l, new_r);
            if (rmp - l + 1 > best_ans) best_ans = rmp - l + 1;
        }
        ans[i] = best_ans;
    }
}

void sol2(const vector<uint32_t> &nums, const vector<Req> &reqs, vector<uint32_t> &ans) {
    SparseTable st(nums);
    vector<vector<uint32_t>> prep(nums.size() + 1, vector<uint32_t>(nums.size() + 1, 0));
    for (uint32_t l = 0; l < nums.size(); ++l) {
        for (uint32_t r = l + 1; r <= nums.size(); ++r) {
            uint32_t bsl = l, bsr = r;
            while (bsl + 1 < bsr) {
                uint32_t mid = (bsl + bsr) / 2;
                auto m1 = (mid > bsl ? st.min(bsl, mid) : inf);
                auto m2 = (bsr > mid ? st.min(mid, bsr) : inf);
                if (m1 < nums[l]) bsr = mid;
                else if (m2 < nums[l]) bsl = mid;
                else bsl = bsr;
            }
            uint32_t new_r = r;
            if (bsl != bsr) new_r = bsr;
            uint32_t rmp = st.right_max_pos(l, new_r);
            prep[l][r] = rmp - l + 1;
        }
    }
    SparseTable2d st2(prep);
    for (uint32_t i = 0; i < reqs.size(); ++i) {
        ans[i] = st2.max(reqs[i].l - 1, reqs[i].r, reqs[i].l - 1, reqs[i].r);
    }
}

int main() {
    uint32_t n;
    cin >> n;
    vector<uint32_t> nums(n);
    for (auto &num: nums) cin >> num;
    uint32_t q;
    cin >> q;
    vector<Req> reqs(q);
    for (auto &[l, r]: reqs) cin >> l >> r;
    vector<uint32_t> ans1(reqs.size()), ans2(reqs.size());
    if (q <= 100) sol2(nums, reqs, ans1);
    else sol2(nums, reqs, ans1);
    reverse(nums.begin(), nums.end());
    for (auto &req: reqs) req = {n + 1 - req.r, n + 1 - req.l};
    if (q <= 100) sol2(nums, reqs, ans2);
    else sol2(nums, reqs, ans2);
    for (uint32_t i = 0; i < q; ++i) cout << max(ans1[i], ans2[i]) << "\n";
//    uint32_t k = static_cast<uint32_t>(sqrt(static_cast<long double>(q))) + 2;
//    auto cmp = [k](const Req &a, const Req &b) {
//        if (a.l / k != b.l / k) return a.l < b.l;
//        return a.r < b.r;
//    };
//    sort(reqs.begin(), reqs.end(), cmp);
//    uint32_t nl = 0, nr = 0;
//    for (auto [rl, rr, ri]: reqs) {
//    }
    return 0;
}
