#pragma GCC optimize("Ofast")

#include <iostream>


using namespace std;

void solve() {
    long long ans = 0;
    long long n = -8903;
    for (long long i = 0; i < 10000000000l; ++i) {
        ans += n;
        if (!n) break;
        if (n & 1) n /= 2;
        else n = n * 3 + 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // #ifdef LOCAL
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif
    solve();
    return 0;
}


// #pragma GCC optimize("Ofast")
//
// #ifdef LOCAL
// #include <iostream>
// #endif
//
// #include <algorithm>
// #include <vector>
// using namespace std;
//
// constexpr int maxval = 2.3e6 + 1;
// vector<int> rer[maxval + 1];
// int rer_cnts[maxval + 1];
// long long cnt_ok[maxval + 1], suf_cnt_ok_add[maxval + 1];
// int n, t;
//
// void rer_init() {
//     for (int i = 1; i <= maxval; ++i) for (int j = i; j <= maxval; j += i) ++rer_cnts[j];
//     for (int i = 1; i <= maxval; ++i) rer[i].reserve(rer_cnts[i]);
//     for (int i = 1; i <= maxval; ++i) for (int j = i; j <= maxval; j += i) rer[j].push_back(i);
// }
//
// int solve(int _n, int _t, vector<int> r, vector<int> c, vector<int> v) {
//     n = _n, t = _t;
//     rer_init();
//     for (int i = 0; i < r.size(); ++i) {
//         int x = r[i], y = c[i], val = v[i];
//         int rk = val - x - y;
//         if (rk > 0) continue;
//         if (rk == 0) {
//             if (val + 1 <= maxval) ++suf_cnt_ok_add[val + 1];
//             continue;
//         }
//         auto &cdels = rer[-rk];
//         auto it = upper_bound(cdels.begin(), cdels.end(), val);
//         for (; it != cdels.end(); ++it) ++cnt_ok[*it];
//     }
//     for (int i = 1; i <= maxval; ++i) suf_cnt_ok_add[i] += suf_cnt_ok_add[i - 1];
//     for (int i = 0; i <= maxval; ++i) cnt_ok[i] += suf_cnt_ok_add[i];
//     int k = 0;
//     for (int i = 0; i <= maxval; ++i) if (cnt_ok[i] >= cnt_ok[k]) k = i;
//     if (k == 0) k = 1;
//     int ans = 0;
//     for (int i = 0; i < r.size(); ++i) {
//         int x = r[i], y = c[i], val = v[i];
//         if ((x + y) % k != val) ++ans;
//     }
//     return ans;
// }
//
// #ifdef LOCAL
// int main() {
//     int n, t;
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
//     cin >> n >> t;
//     vector<int> r(t), c(t), v(t);
//     for (int &x: r) cin >> x;
//     for (int &x: c) cin >> x;
//     for (int &x: v) cin >> x;
//     int result = solve(n, t, r, c, v);
//     cout << result << "\n";
//     return 0;
// }
// #endif
