#include <iostream>

using namespace std;
using ll = long long;

constexpr int maxn = 50;

int n, m;
ll nums[maxn];
ll dp[maxn + 1][maxn + 1];
ll pf[maxn + 1];

ll ans = 0;

void stupid_solve(ll pre_and, int pre_s_cnt, int nid) {
    if (nid == n) {
        if (pre_s_cnt == m) ans = std::max(ans, pre_and);
        return;
    }
    for (int cnid = nid + 1; cnid <= n && cnid + (m - pre_s_cnt - 1) <= n; ++cnid) {
        stupid_solve(pre_and & (pf[cnid] - pf[nid]), pre_s_cnt + 1, cnid);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    for (int i = 0; i < n; ++i) pf[i + 1] = pf[i] + nums[i];
    stupid_solve((1ll << 50) - 1, 0, 0);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    solve();
    return 0;
}
