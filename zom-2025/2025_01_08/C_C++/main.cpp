#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

constexpr int maxn = 1e5 + 1, maxval = 1e6 + 1, block_size = 320, inf = 1e9;
using ld = double;

ld p2s[maxn + 1];
int n;
int nums[maxn];
int sorted_nums[maxn];
int minpos_by_val[maxval];


template<typename T>
T ceil(T a, T b) {
    return (a + b - 1) / b;
}

struct MinStack {
    vector<pair<int, int> > st;

    int min_val() const {
        if (st.empty()) return inf;
        return st.back().second;
    }

    void push(int val) {
        st.emplace_back(val, std::min(min_val(), val));
    }

    void pop() {
        st.pop_back();
    }

    void erase_n_bottom(int n) {
        if (n >= st.size()) {
            st.clear();
            return;
        }
        for (int i = 0; i < st.size() - n; ++i) {
            st[i] = st[i + n];
            st[i].second = std::min(st[i].first, i ? st[i - 1].second : inf);
        }
        st.resize(st.size() - n);
    }

    int operator[](int pos) const {
        return st[pos].first;
    }

    bool empty() const { return st.empty(); }

    size_t size() const { return st.size(); }
};

namespace MinDeque {
    MinStack st1, st2;

    size_t size() {
        return st1.size() + st2.size();
    }

    void push_back(int val) {
        st2.push(val);
    }

    void push_front(int val) {
        st1.push(val);
    }

    void pop_back() {
        if (st2.empty()) {
            for (int i = ceil<int>(st1.size(), 2) - 1; i >= 0; --i) st2.push(st1[i]);
            st1.erase_n_bottom(ceil<int>(st1.size(), 2));
        }
        st2.pop();
    }

    void pop_front() {
        if (st1.empty()) {
            for (int i = ceil<int>(st2.size(), 2) - 1; i >= 0; --i) st1.push(st2[i]);
            st2.erase_n_bottom(ceil<int>(st2.size(), 2));
        }
        st1.pop();
    }

    int min_val() {
        return std::min(st1.min_val(), st2.min_val());
    }
}

namespace ST {
    struct Node {
        int cnt = 0;
        ld psum = 0;
    };

    Node tree[maxn * 2];

    void insert(int val) {
        int pos = (minpos_by_val[val]++) + n;
        tree[pos].cnt = 1, tree[pos].psum = val;
        pos >>= 1;
        while (pos) {
            tree[pos].cnt = tree[pos << 1].cnt + tree[pos << 1 | 1].cnt;
            tree[pos].psum = tree[pos << 1].psum + tree[pos << 1 | 1].psum * p2s[tree[pos << 1].cnt];
            pos >>= 1;
        }
    }

    void erase(int val) {
        int pos = (--minpos_by_val[val]) + n;
        tree[pos].cnt = 0, tree[pos].psum = 0;
        pos >>= 1;
        while (pos) {
            tree[pos].cnt = tree[pos << 1].cnt + tree[pos << 1 | 1].cnt;
            tree[pos].psum = tree[pos << 1].psum + tree[pos << 1 | 1].psum * p2s[tree[pos << 1].cnt];
            pos >>= 1;
        }
    }

    pair<ld, int> get_sum_cnt() {
        Node left_res, right_res;
        int l = n, r = n * 2;
        while (l < r) {
            if (l & 1) {
                left_res.psum = left_res.psum + tree[l].psum * p2s[left_res.cnt];
                left_res.cnt += tree[l].cnt;
                ++l;
            }
            if (r & 1) {
                --r;
                right_res.psum = tree[r].psum + right_res.psum * p2s[tree[r].cnt];
                right_res.cnt += tree[r].cnt;
            }
            l >>= 1, r >>= 1;
        }
        left_res.psum = left_res.psum + right_res.psum * p2s[left_res.cnt];
        left_res.cnt += right_res.cnt;
        return {left_res.psum, left_res.cnt};
    }
}

struct Req {
    int id, l, r;

    bool operator<(const Req &rhs) const {
        int lb = l / block_size, rlb = rhs.l / block_size;
        if (lb != rlb) return lb < rlb;
        if (r != rhs.r) {
            if (lb & 1) return r > rhs.r;
            return r < rhs.r;
        }
        return id < rhs.id;
    }
};

Req reqs[maxn];
ld ans[maxn];

void solve() {
    p2s[0] = 1;
    for (int i = 1; i <= maxn; ++i) p2s[i] = p2s[i - 1] / 2;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    copy(nums, nums + n, sorted_nums);
    sort(sorted_nums, sorted_nums + n);
    reverse(sorted_nums, sorted_nums + n);
    for (int i = n - 1; i >= 0; --i) minpos_by_val[sorted_nums[i]] = i;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> reqs[i].l >> reqs[i].r, --reqs[i].l;
        reqs[i].id = i;
    }
    sort(reqs, reqs + q);
    int l = 0, r = 0;
    for (int i = 0; i < q; ++i) {
        int rl = reqs[i].l, rr = reqs[i].r;
        while (r < rr) MinDeque::push_back(nums[r]), ST::insert(nums[r++]);
        while (l > rl) ST::insert(nums[--l]), MinDeque::push_front(nums[l]);
        while (r > rr) ST::erase(nums[--r]), MinDeque::pop_back();
        while (l < rl) MinDeque::pop_front(), ST::erase(nums[l++]);
        auto [csum, ccnt] = ST::get_sum_cnt();
        ans[reqs[i].id] = csum / 2 + p2s[ccnt] * MinDeque::min_val();
    }
    for (int i = 0; i < q; ++i) cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << fixed << setprecision(10);
    solve();
    return 0;
}
