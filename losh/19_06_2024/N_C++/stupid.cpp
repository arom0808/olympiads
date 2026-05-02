//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//#define x first
//#define y second

using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int ll
//mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
//mt19937 mt(52);
//double EPS = 0.000000000000001;
//const unsigned int rnd_max = 4294967295;
using namespace __gnu_pbds;
//double rng() { return (double) mt() / (1.0 * rnd_max); }
double EPS = 1e-9;

int fnd(vector<pair<pair<int, int>, int>> &a, pair<pair<int, int>, int> el) {
    int l = -1, r = a.size();
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m] < el) l = m;
        else
            r = m;
    }
    return l;
}

void solve() {
    int hl, hr, n;
    cin >> hl >> hr >> n;
    int at[100000], af[100000];
    for (auto &el: at) el = 0;
    for (auto &el: af) el = 0;
    vector<pair<pair<int, int>, int>> st, sf;
    for (int i = 0; i < n; ++i) {
        int v, a, b;
        char c;
        cin >> v >> c >> a >> b;
        if (c == 'T') {
            st.push_back({{a, b}, 0});
            for (int x = a; x < b; ++x) at[x] = v;
        } else {
            sf.push_back({{a, b}, 0});
            for (int x = a; x < b; ++x) af[x] = v;
        }
    }
    sort(st.begin(), st.end());
    sort(sf.begin(), sf.end());
    int x1 = 0, y1 = hl, x2 = 100000;
    int ans = 0;
    for (int k = -n; k <= n; ++k) {
        auto sst = st, ssf = sf;
        if (k == 0) continue;
        int y2 = (k % 2 ? 100 * (k + 1) - hr : 100 * k + hr);
        double p = 1.0 * (y1 - y2) / (x1 - x2), q = 1.0 * y2 - 1.0 * x2 * (y1 - y2) / (x1 - x2);
        int cur = 0;
        bool found = 1;
        for (int otr = 0; otr <= abs(k) - 1; ++otr) {
            if (!found) break;
            bool top = 0;
            int yp;
            if (k > 0) {
                yp = 100 * (otr + 1);
                top = otr % 2 == 0;
            } else {
                yp = -100 * otr;
                top = otr % 2;
            }
            double xp = (1.0 * yp - q) / p;
            if (top) {
                if ((xp < 0 || xp > 100000) || at[(int) floor(xp)] == 0) {
                    found = 0;
                    break;
                }
                int idx = fnd(sst, {{xp, 1000000000}, 1000000000});
                if (sst[idx].second == 1) {
                    found = 0;
                    break;
                }
                cur += at[(int) floor(xp)];
                sst[idx].second = 1;
            } else {
                if ((xp < 0 || xp > 100000) || af[(int) floor(xp)] == 0) {
                    found = 0;
                    break;
                }
                int idx = fnd(ssf, {{xp, 1000000000}, 1000000000});
                if (ssf[idx].second == 1) {
                    found = 0;
                    break;
                }
                cur += af[(int) floor(xp)];
                ssf[idx].second = 1;
            }
        }
        if (!found) continue;
        ans = max(ans, cur);
    }
    cout << ans;
}

signed main() {
//#ifdef LOCAL
//    freopen("INPUT.TXT", "r", stdin);
//    freopen("OUTPUT.TXT", "w", stdout);
//#endif
    freopen("test.txt", "r", stdin);
    int cfmode = 0;
    if (cfmode) {
        int t;
        cin >> t;
        while (t--) {
            solve();
        }
    } else
        solve();
}
