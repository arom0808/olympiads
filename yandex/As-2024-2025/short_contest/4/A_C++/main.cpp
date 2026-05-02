#pragma GCC optimize("Ofast")

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int arr[20];
int n;
int csb = 0, need_cv_sum;
vector<int> cv;
int ans = 0;

bool can_cv(int level, int cs) {
    if (level == cv.size()) return cs == need_cv_sum;
    if (cs + cv[level] <= need_cv_sum && can_cv(level + 1, cs + cv[level])) return true;
    return can_cv(level + 1, cs);
}

void rec_sol(int level, int cs) {
    if (level == n) {
        if ((cs & 1) || !cs) return;
        cv.clear();
        for (int cl = 0; cl < n; ++cl) if ((csb >> cl) & 1) cv.push_back(arr[cl]);
        need_cv_sum = cs >> 1;
        ans += can_cv(0, 0);
        return;
    }
    csb |= 1 << level;
    rec_sol(level + 1, cs + arr[level]);
    csb &= ~(1 << level);
    rec_sol(level + 1, cs);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    sort(begin(arr), next(begin(arr), n));
    reverse(begin(arr), next(begin(arr), n));
    csb = 0;
    rec_sol(0, 0);
    cout << ans << "\n";
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
