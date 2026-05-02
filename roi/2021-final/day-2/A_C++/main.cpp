#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 3e5 + 1;
constexpr ll inf = 2e18;

struct DPV {
    ll val;
    int cur_dig;
    int post_max_dig;

    DPV() = default;

    DPV(ll val, int cur_dig, int post_max_dig): val(val), cur_dig(cur_dig), post_max_dig(post_max_dig) {
    }

    void init() {
        val = -inf;
        cur_dig = post_max_dig = -1;
    }

    bool operator<(const DPV &rhs) const {
        return val < rhs.val;
    }
};

ll vals[26];
string s;
DPV dp[maxn][26];

void solve_test() {
    cin >> s;
    for (auto &c: s) if (c != '?') c -= 'A';
    int n = s.size();
    for (int i = 0; i <= n; ++i) for (int j = 0; j < 26; ++j) dp[i][j].init();
    for (int i = 0; i < 26; ++i) dp[n][i].val = 0;
    for (int i = n - 1; i >= 0; --i) {
        int scv = s[i], fcv = s[i] + 1;
        if (s[i] == '?') scv = 0, fcv = 26;
        for (int cv = scv; cv < fcv; ++cv) {
            for (int pmd = 0; pmd < 26; ++pmd) {
                if (dp[i + 1][pmd].val == -inf) continue;
                DPV v(dp[i + 1][pmd].val, cv, pmd);
                if (cv >= pmd) v.val += vals[cv];
                else v.val -= vals[cv];
                dp[i][std::max(cv, pmd)] = std::max(dp[i][std::max(cv, pmd)], v);
            }
        }
        for (int j = 1; j < 26; ++j) if (dp[i][j - 1].val > dp[i][j].val) dp[i][j] = dp[i][j - 1];
    }
    int cpmd = 0;
    for (int i = 0; i < 26; ++i) if (dp[0][i].val > dp[0][cpmd].val) cpmd = i;
    cout << dp[0][cpmd].val << "\n";
    for (int i = 0; i < n; ++i) {
        cout << static_cast<char>(dp[i][cpmd].cur_dig + 'A');
        cpmd = dp[i][cpmd].post_max_dig;
    }
    cout << "\n";
}

void solve() {
    for (ll i = 0, v = 1; i < 26; i += 2, v *= 10) {
        vals[i] = v;
        vals[i + 1] = v * 5;
    }
    int t;
    cin >> t;
    while (t--) solve_test();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
