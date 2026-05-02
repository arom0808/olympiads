#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>

using namespace std;

constexpr int maxn = 3e5;
int right_one[maxn], left_zero[maxn];
string s;
int n;

pair<int, int> proc_seg(int l, int r, int sz) {
    int minval = left_zero[r - 1] < l ? 0 : left_zero[r - 1] - l + 1;
    int maxval = right_one[l] >= r ? sz : right_one[l] - l;
    return {minval, maxval};
}

void solve() {
    cin >> s;
    n = s.size();
    for (int i = 0; i < n; ++i) {
        if (i) left_zero[i] = left_zero[i - 1];
        else left_zero[i] = -1;
        if (s[i] == '0') left_zero[i] = i;
    }
    for (int i = n - 1; i >= 0; --i) {
        if (i + 1 < n) right_one[i] = right_one[i + 1];
        else right_one[i] = n;
        if (s[i] == '1') right_one[i] = i;
    }
    int best_black_cnt = -1, best_sz = 0, best_a = 0;
    for (int sz = 1; sz <= n; ++sz) {
        int a_min = 0, a_max = n;
        for (int i = 0; i < n; i += sz) {
            auto [nmin, nmax] = proc_seg(i, std::min(i + sz, n), sz);
            if (nmin > a_min) a_min = nmin;
            if (nmax < a_max) a_max = nmax;
            if (a_min > a_max || a_max < 1) break;
        }
        if (a_min > a_max || a_max < 1) continue;
        int ca = std::max(a_min, 1);
        int cbc = (n / sz) * (sz - ca) + std::max(0, n % sz - ca);
        if (cbc > best_black_cnt) best_black_cnt = cbc, best_sz = sz, best_a = ca;
    }
    if (best_black_cnt == -1) {
        cout << "-1\n";
        return;
    }
    for (int i = 0; i < n; ++i) s[i] = (i % best_sz < best_a) ? '0' : '1';
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
