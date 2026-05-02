#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, q;
    cin >> n;
    string temp;
    vector<bool> s(n), t(n);
    cin >> temp;
    for (int32_t i = 0; i < n; ++i) s[i] = temp[i] == '1';
    cin >> temp;
    for (int32_t i = 0; i < n; ++i) t[i] = temp[i] == '1';
    vector<int32_t> need_lb(n, -1), need_rb(n, -1);
    for (int32_t i = 0; i < n; ++i) {
        if (s[i]) continue;
        if (i > 0) {
            if (t[i - 1]) need_lb[i] = i - 1;
            else if (i > 1 && !s[i - 2]) need_lb[i] = i - 2;
        }
        if (i + 1 < n) {
            if (t[i + 1]) need_rb[i] = i + 1;
            else if (i + 2 < n && !s[i + 2]) need_rb[i] = i + 2;
        }
    }
    vector<int32_t> pref_sum(n + 1), may_pref_sum(n + 1);
    for (int32_t i = 1; i <= n; ++i)
        pref_sum[i] = pref_sum[i - 1] + s[i - 1],
                may_pref_sum[i] = may_pref_sum[i - 1] + (need_lb[i - 1] >= 0 && need_rb[i - 1] >= 0);
    cin >> q;
    set<int32_t> to_check;
    for (int32_t i = 0, l, r; i < q; ++i) {
        cin >> l >> r, --l;  // [l, r)
        int32_t res = pref_sum[r] - pref_sum[l];
        to_check.clear();
        to_check.insert(l + 1), to_check.insert(l + 2), to_check.insert(r - 2), to_check.insert(r - 3);
        if (r - l >= 6) res += may_pref_sum[r - 3] - may_pref_sum[l + 3];
        for (auto tc: to_check) {
            if (s[tc] || tc < l + 1 || tc > r - 2) continue;
            if (need_rb[tc] != -1 && need_lb[tc] != -1 && need_lb[tc] >= l && need_rb[tc] < r) ++res;
        }
        cout << res << "\n";
    }
    return 0;
}
