#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = int64_t;

constexpr ll inf = 1e18;
constexpr int maxn = 2e6;

struct Kef {
    int exp_date, id;

    bool operator<(const Kef &rhs) const {
        if (exp_date != rhs.exp_date) return exp_date < rhs.exp_date;
        return id < rhs.id;
    }
};

Kef kefs[maxn];
int n, m, k;

ll mvals[maxn];
// ll min_suf[maxn + 1];
int cnt_pref[maxn + 1];

void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < n + m; ++i) cin >> kefs[i].exp_date, kefs[i].id = i;
    sort(begin(kefs), next(begin(kefs), n + m));
    cnt_pref[0] = 0;
    for (int i = 0; i < n + m; ++i) mvals[i] = inf;
    for (int i = 0; i < n + m; ++i) {
        if (kefs[i].id >= n) {
            cnt_pref[i + 1] = cnt_pref[i];
            continue;
        }
        cnt_pref[i + 1] = cnt_pref[i] + 1;
        mvals[i] = 1ll * (kefs[i].exp_date + 1) * k - 1 - cnt_pref[i];
        if (mvals[i] < 0) {
            cout << "-1\n";
            return;
        }
    }
    // min_suf[n + m] = inf;
    // for (int i = n + m - 1; i >= 0; --i) {
    // min_suf[i] = std::min(min_suf[i + 1], mvals[i]);
    // }
    int added_cnt = 0;
    ll added_min = inf;
    for (int i = n + m - 1; i >= 0; --i) {
        if (kefs[i].id < n) {
            added_min = std::min(added_min, mvals[i]);
            continue;
        }
        ll cv = 1ll * (kefs[i].exp_date + 1) * k - 1 - cnt_pref[i];
        if (cv < 0) continue;
        if (added_min - 1 < 0) continue;
        mvals[i] = cv;
        ++added_cnt;
        added_min = std::min(added_min - 1, mvals[i]);
    }
    cout << added_cnt << "\n";
    for (int i = 0; i < n + m; ++i) {
        if (kefs[i].id < n || mvals[i] == inf) continue;
        cout << kefs[i].id - n + 1 << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    // freopen("input.txt", "r",stdin);
    solve();
#endif
    return 0;
}
