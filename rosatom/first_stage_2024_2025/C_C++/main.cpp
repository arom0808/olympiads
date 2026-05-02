// #pragma GCC optimize("Ofast")

#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 3e5 + 1, inf = 2e9;
constexpr int N = (1 << 19);


// struct ST {
//     int *tree = new int[N * 2];
//
//     void swap(ST &other) noexcept {
//         std::swap(tree, other.tree);
//     }
//
//     void init(pair<int, int> *arr, int _size) {
//         for (int i = 0; i < _size; ++i) tree[N + i] = arr[i].second;
//         for (int i = _size; i < N; ++i) tree[N + i] = inf;
//         for (int i = N - 1; i > 0; --i) tree[i] = std::min(tree[i << 1], tree[(i << 1) | 1]);
//     }
//
//     int min_val(int l, int r) {
//         l += N, r += N;
//         int ans = inf;
//         while (l < r) {
//             if (l & 1) ans = std::min(ans, tree[l++]);
//             if (r & 1) ans = std::min(ans, tree[--r]);
//             l >>= 1, r >>= 1;
//         }
//         return ans;
//     }
// };

struct SlidingWindow {
    deque<pair<int, int> > d;
    int l, r;

    void clear() {
        d.clear();
        l = r = 0;
    }

    void pb(int x) {
        while (!d.empty() && d.back().first >= x) d.pop_back();
        d.emplace_back(x, r++);
    }

    void pop_front() {
        if (d.front().second == l++) d.pop_front();
    }

    int get_min() const {
        return d.empty() ? inf : d.front().first;
    }
};


int n;
pair<int, int> *asp = new pair<int, int>[maxn], *bsp = new pair<int, int>[maxn], *csp = new pair<int, int>[maxn];
// ST ast, bst, cst;
vector<int> all_colors;
int *a_st_col_pos = new int[maxn * 3 + 1], *b_st_col_pos = new int[maxn * 3 + 1], *c_st_col_pos = new int[maxn * 3 + 1];
SlidingWindow slw1, slw2;

ll min_full_price(int d) {
    slw1.clear(), slw2.clear();
    int s1 = 0, s2 = 0, f1 = 0, f2 = 0;
    ll cans = inf;
    for (int i = 0; i < n; ++i) {
        while (f1 < b_st_col_pos[std::min<int>(asp[i].first + d + 1, all_colors.size())]) slw1.pb(bsp[f1++].second);
        while (f2 < c_st_col_pos[std::min<int>(asp[i].first + d + 1, all_colors.size())]) slw2.pb(csp[f2++].second);
        while (s1 < n && bsp[s1].first < asp[i].first) slw1.pop_front(), ++s1;
        while (s2 < n && csp[s2].first < asp[i].first) slw2.pop_front(), ++s2;
        cans = std::min(cans, 0ll + asp[i].second + slw1.get_min() + slw2.get_min());
    }
    return cans;
}

int get_ans(int x) {
    int l = -1, r = 1e9 + 1;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (min_full_price(mid) <= x) r = mid;
        else l = mid;
    }
    return r;
    // int d = 1e9;
    // int max_col_id = all_colors.size();
    // for (int i = 0; i < n; ++i) {
    //     while (max_col_id < all_colors.size() && all_colors[max_col_id] < all_colors[asp[i].first] + d) ++max_col_id;
    //     do --max_col_id;
    //     while (max_col_id >= 0 && min_full_price(i, max_col_id) <= 0ll + x);
    //     ++max_col_id;
    //     if (max_col_id < all_colors.size()) d = std::min(d, all_colors[max_col_id] - all_colors[asp[i].first]);
    // }
    // return d;
}

int get_zipped(const vector<int> &fzn, int val) {
    return lower_bound(fzn.begin(), fzn.end(), val) - fzn.begin();
}

void init_st_col_pos(pair<int, int> *cur_cs, int *cur_st_col_pos) {
    int next_col = 0;
    for (int i = 0; i < n; ++i)
        if (cur_cs[i].first >= next_col)
            for (; next_col <= cur_cs[i].first; ++next_col)
                cur_st_col_pos[next_col] = i;
    for (; next_col <= all_colors.size(); ++next_col) cur_st_col_pos[next_col] = n;
}

void solve() {
    int x;
    cin >> n >> x;
    int a_min_price = inf, b_min_price = inf, c_min_price = inf;
    all_colors.reserve(n * 3);
    for (int i = 0; i < n; ++i) cin >> asp[i].first, all_colors.push_back(asp[i].first);
    for (int i = 0; i < n; ++i) cin >> asp[i].second, a_min_price = std::min(a_min_price, asp[i].second);
    for (int i = 0; i < n; ++i) cin >> bsp[i].first, all_colors.push_back(bsp[i].first);
    for (int i = 0; i < n; ++i) cin >> bsp[i].second, b_min_price = std::min(b_min_price, bsp[i].second);
    for (int i = 0; i < n; ++i) cin >> csp[i].first, all_colors.push_back(csp[i].first);
    for (int i = 0; i < n; ++i) cin >> csp[i].second, c_min_price = std::min(c_min_price, csp[i].second);
    if (0ll + a_min_price + b_min_price + c_min_price > 0ll + x) {
        cout << "-1\n";
        return;
    }
    sort(all_colors.begin(), all_colors.end());
    all_colors.erase(unique(all_colors.begin(), all_colors.end()), all_colors.end());
    sort(asp, asp + n);
    sort(bsp, bsp + n);
    sort(csp, csp + n);
    for (int i = 0; i < n; ++i) asp[i].first = get_zipped(all_colors, asp[i].first);
    for (int i = 0; i < n; ++i) bsp[i].first = get_zipped(all_colors, bsp[i].first);
    for (int i = 0; i < n; ++i) csp[i].first = get_zipped(all_colors, csp[i].first);
    init_st_col_pos(asp, a_st_col_pos);
    init_st_col_pos(bsp, b_st_col_pos);
    init_st_col_pos(csp, c_st_col_pos);
    // ast.init(asp, n), bst.init(bsp, n), cst.init(csp, n);
    int bans = inf;
    for (int i = 0; i < 3; ++i) {
        bans = std::min(bans, get_ans(x));
        swap(asp, bsp), swap(bsp, csp);
        // swap(acs, bcs), swap(bcs, ccs);
        // swap(aprs, bprs), swap(bprs, cprs);
        swap(a_st_col_pos, b_st_col_pos), swap(b_st_col_pos, c_st_col_pos);
        // ast.swap(bst), bst.swap(cst);
    }
    cout << bans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    solve();
    return 0;
}
