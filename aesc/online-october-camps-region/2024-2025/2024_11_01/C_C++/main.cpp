#pragma GCC optimize("Ofast,O3")

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = int64_t;

constexpr int maxn = 40;
int ohs[maxn], ocs[maxn];
int hs1[maxn / 2], cs1[maxn / 2];
int hs2[maxn / 2], cs2[maxn / 2];
int sz1, sz2;
vector<ll> sums2[maxn / 2];

int n;
ll k;
bool easy_task = true;

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> ohs[i] >> ocs[i];
    for (int i = 1; i < n; ++i) if (ohs[i - 1] > ohs[i]) easy_task = false;
    if (n == 1) {
        if (ocs[0] >= k) cout << "1\n";
        else cout << "0\n";
        return;
    }
    sz2 = std::max(n / 2 - 1, 1), sz1 = n - sz2;
    for (int i = 0; i < n; ++i) {
        if (i < sz1) hs1[i] = ohs[i], cs1[i] = ocs[i];
        else hs2[i - sz1] = ohs[i], cs2[i - sz1] = ocs[i];
    }
    ll ans = 0;
    for (int i = sz2 - 1; i >= 0; --i) sums2[i].reserve(1 << (sz2 - i - 1));
    for (int mask = 1; mask < (1 << sz2); ++mask) {
        int mh = 0, fj = -1;
        ll cc = 0;
        bool ok = true;
        for (int j = 0; j < sz2 && ok; ++j) {
            if (mask & (1 << j)) {
                if (fj == -1) fj = j;
                if (hs2[j] >= mh) cc += cs2[j], mh = hs2[j];
                else ok = false;
            }
        }
        if (!ok) continue;
        sums2[fj].push_back(cc);
        if (cc >= k) ++ans;
    }
    vector<ll> all_sums;
    if (easy_task) {
        int nsz = 0;
        for (int i = 0; i < sz2; ++i) nsz += static_cast<int>(sums2[i].size());
        all_sums.reserve(nsz);
        for (int i = 0; i < sz2; ++i) all_sums.insert(all_sums.end(), sums2[i].begin(), sums2[i].end());
        sort(all_sums.begin(), all_sums.end());
    } else {
        for (int i = 0; i < sz2; ++i) sort(sums2[i].begin(), sums2[i].end());
    }
    for (int mask = 1; mask < (1 << sz1); ++mask) {
        int mh = 0, lj = -1;
        ll cc = 0;
        bool ok = true;
        for (int j = 0; j < sz1 && ok; ++j) {
            if (mask & (1 << j)) {
                lj = j;
                if (hs1[j] >= mh) cc += cs1[j], mh = hs1[j];
                else ok = false;
            }
        }
        if (!ok) continue;
        if (cc >= k) ++ans;
        if (easy_task) {
            ans += distance(lower_bound(all_sums.begin(), all_sums.end(), k - cc), all_sums.end());
        } else {
            for (int ss = 0; ss < sz2; ++ss) {
                if (hs1[lj] > hs2[ss]) continue;
                ans += distance(lower_bound(sums2[ss].begin(), sums2[ss].end(), k - cc), sums2[ss].end());
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
