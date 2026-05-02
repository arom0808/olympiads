#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <algorithm>

using namespace std;

constexpr int maxn = 6e5;
int n, x;
int vals[maxn], all_vals[maxn];
int vals_cnt = 0;

int zip_val(int val) {
    return lower_bound(all_vals, all_vals + vals_cnt, val) - all_vals;
}

struct ST {
    int tree[maxn * 2];

    void init() {
        for (int i = 0; i < 2 * vals_cnt; ++i) tree[i] = 0;
    }

    int get_max(int l, int r) {
        l += vals_cnt, r += vals_cnt;
        int ans = 0;
        while (l != r) {
            if (l & 1) ans = std::max(ans, tree[l++]);
            if (r & 1) ans = std::max(ans, tree[--r]);
            l >>= 1, r >>= 1;
        }
        return ans;
    }

    void set_val(int pos, int val) {
        pos += vals_cnt;
        tree[pos] = val;
        for (pos >>= 1; pos; pos >>= 1) tree[pos] = std::max(tree[pos << 1], tree[pos << 1 | 1]);
    }
};

ST not_start, started, finished;

int calc_lis_with_shift(int shift) {
    not_start.init(), started.init(), finished.init();
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        int ov = zip_val(vals[i]), cv = zip_val(vals[i] + shift);
        int c1 = not_start.get_max(0, ov) + 1;
        int c2 = std::max(not_start.get_max(0, cv), started.get_max(0, cv)) + 1;
        int c3 = std::max(c1, std::max(started.get_max(0, ov), finished.get_max(0, ov)) + 1);
        not_start.set_val(ov, c1);
        started.set_val(cv, c2);
        finished.set_val(ov, c3);
        ans = std::max(ans, std::max(c1, std::max(c2, c3)));
    }
    return ans;
}

void solve() {
    cin >> n >> x;
    for (int i = 0; i < n; ++i) cin >> vals[i];
    for (int i = 0; i < n; ++i) all_vals[vals_cnt++] = vals[i];
    for (int i = 0; i < n; ++i) all_vals[vals_cnt++] = vals[i] - x;
    sort(all_vals, all_vals + vals_cnt);
    vals_cnt = unique(all_vals, all_vals + vals_cnt) - all_vals;
    // for (int i = 0; i < n; ++i) vals[i] = zip_val(vals[i]);
    int ans = 1;
    ans = std::max(ans, calc_lis_with_shift(-x));
    ans = std::max(ans, calc_lis_with_shift(0));
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
