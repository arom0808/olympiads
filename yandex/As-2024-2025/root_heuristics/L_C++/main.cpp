#pragma GCC optimize("Ofast")

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int32_t maxn = 1e5, sqrtn = 2155;
int32_t n, q, ch_cnt = 0;

struct Change {
    int32_t pos, old_val, new_val;
};

struct Req {
    int32_t l, r, t, id, ans;

    Req(int32_t l, int32_t r, int32_t t, int32_t id, int32_t ans): l(l), r(r), t(t), id(id), ans(ans) {
    }
};

int32_t nums[maxn];
Change changes[maxn];
vector<Req> reqs;
vector<int32_t> all_nums;

int32_t get_zip_pos(int32_t num) {
    return distance(all_nums.begin(), lower_bound(all_nums.begin(), all_nums.end(), num));
}

namespace SqrtArr {
    int32_t cnts[maxn * 2 + 2];
    int32_t mex_cnts[maxn * 2 + 2];
    int32_t blocks[(maxn * 2 + 2) / sqrtn + 1];

    void add_del_to_mex(int32_t val, bool del = false) {
        if (!mex_cnts[val]) ++blocks[val / sqrtn];
        mex_cnts[val] += -2 * del + 1;
        if (!mex_cnts[val]) --blocks[val / sqrtn];
    }

    void add_del(int32_t val, bool del = false) {
        if (cnts[val]) add_del_to_mex(cnts[val], true);
        cnts[val] += -2 * del + 1;
        if (cnts[val]) add_del_to_mex(cnts[val]);
    }

    int32_t get_mex() {
        int32_t i = 0;
        while (blocks[i] == sqrtn) ++i;
        i *= sqrtn;
        while (mex_cnts[i]) ++i;
        return i;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    SqrtArr::add_del_to_mex(0);
    cin >> n >> q;
    for (int32_t i = 0; i < n; ++i) cin >> nums[i], all_nums.push_back(nums[i]);
    for (int32_t i = 0, t, a, b, r_c = 0; i < q; ++i) {
        cin >> t >> a >> b;
        if (t == 1) reqs.emplace_back(a - 1, b, ch_cnt, r_c++, 0);
        else changes[ch_cnt++] = {a - 1, nums[a - 1], b}, nums[a - 1] = b, all_nums.push_back(b);
    }
    for (int32_t i = ch_cnt - 1; i >= 0; --i) nums[changes[i].pos] = changes[i].old_val;
    sort(all_nums.begin(), all_nums.end());
    for (int32_t i = 0; i < n; ++i) nums[i] = get_zip_pos(nums[i]);
    for (int32_t i = 0; i < ch_cnt; ++i)
        changes[i].old_val = get_zip_pos(changes[i].old_val), changes[i].new_val = get_zip_pos(changes[i].new_val);
    sort(reqs.begin(), reqs.end(), [](const Req &a, const Req &b) {
        int32_t ald = a.l / sqrtn, bld = b.l / sqrtn;
        if (ald != bld) return ald < bld;
        int32_t ard = a.r / sqrtn, brd = b.r / sqrtn;
        int32_t arcv = ard * (-2 * (ald & 1) + 1), brcv = brd * (-2 * (bld & 1) + 1);
        if (arcv != brcv) return arcv < brcv;
        return a.t * (-2 * ((ald + ard) & 1) + 1) < b.t * (-2 * ((bld + brd) & 1) + 1);
    });
    int32_t gl = 0, gr = 0, gt = 0;
    auto change_t = [&gl,&gr,&gt](bool rev = false) {
        if (rev) --gt;
        if (changes[gt].pos >= gl && changes[gt].pos < gr) {
            SqrtArr::add_del(rev ? changes[gt].new_val : changes[gt].old_val, true);
            SqrtArr::add_del(rev ? changes[gt].old_val : changes[gt].new_val);
        }
        nums[changes[gt].pos] = rev ? changes[gt].old_val : changes[gt].new_val;
        if (!rev) ++gt;
    };
    for (auto &[l,r,t,id,ans]: reqs) {
        while (gl > l) SqrtArr::add_del(nums[--gl]);
        while (gr < r) SqrtArr::add_del(nums[gr++]);
        while (gl < l) SqrtArr::add_del(nums[gl++], true);
        while (gr > r) SqrtArr::add_del(nums[--gr], true);
        while (gt < t) change_t();
        while (gt > t) change_t(true);
        ans = SqrtArr::get_mex();
    }
    vector<int32_t> res(reqs.size());
    for (const auto [l,r,t,id,ans]: reqs) res[id] = ans;
    for (auto el: res) cout << el << "\n";
    return 0;
}
