#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 5010;

int dp[maxn], ps[maxn];
int tarr[maxn];
int timer = 0;

void dp_init() {
    dp[1] = 0;
    for (int l = 2; l <= 5000; ++l) {
        ++timer;
        for (int i = (l + 1) >> 1; i < l; ++i) {
            if (dp[i] < maxn) tarr[dp[i]] = timer;
            if (!dp[i] && !ps[l]) ps[l] = i;
        }
        int mv = 0;
        for (; mv < maxn; ++mv) if (tarr[mv] != timer) break;
        dp[l] = mv;
    }
}

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    int ta[3] = {a, b, c};
    if (dp[a] ^ dp[b] ^ dp[c]) {
        cout << "YES\n";
        for (int i = 0; i < 3; ++i) {
            for (int nv = ta[i] - 1; nv; --nv) {
                int xv = 0;
                for (int j = 0; j < 3; ++j) xv ^= i == j ? dp[nv] : dp[ta[j]];
                if (xv) continue;
                for (int j = 0; j < 3; ++j) cout << (i == j ? nv : ta[j]) << " ";
                cout << "\n";
                return;
            }
        }
    } else {
        cout << "NO\n";
    }
}

int main() {
    dp_init();
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    cin >> t;
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    while (t--) solve();
    return 0;
}
