#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;

constexpr int maxn = 1e5 + 1;
string s, ts;

int za[maxn], zb[maxn];

void calc_z(const string &cs, int *zarr) {
    int l = 0, r = 0;
    zarr[0] = zarr[1] = 0;
    for (int i = 1; i < cs.size(); ++i) {
        zarr[i] = std::max(0, std::min(zarr[i - l], r - i));
        while (i + zarr[i] < cs.size() && cs[zarr[i]] == cs[i + zarr[i]]) ++zarr[i];
        if (i + zarr[i] > r) l = i, r = i + zarr[i];
    }
}

ll cnt_in_left_part(int l, int r, bool reversed) {
    int m = (l + r) / 2;
    if (reversed && ((r - l) & 1) == 0) --m;
    ts = s.substr(l, m - l + 1);
    reverse(ts.begin(), ts.end());
    calc_z(ts, za);
    ts = s.substr(m + 1, r - (m + 1)) + '#' + s.substr(l, m - l);
    calc_z(ts, zb);
    ll res = 0;
    for (int i = 0; i <= m - l; ++i) {
        int ap = i ? za[m - l - i + 1] : 0;
        int bp = (i == m - l) ? 0 : zb[r - m + i];
        int k = m - l - i + 1;
        int cnt = std::min(ap, k) - std::max(k - bp, 0) + 1;
        if (cnt >= 0) res += cnt;
    }
    return res;
}

ll count_repeats(int l, int r) {
    if (r - l < 2) return 0;
    ll res = 0;
    res += cnt_in_left_part(l, r, false);
    reverse(s.begin() + l, s.begin() + r);
    res += cnt_in_left_part(l, r, true);
    reverse(s.begin() + l, s.begin() + r);
    int m = (l + r) / 2;
    res += count_repeats(l, m);
    res += count_repeats(m + 1, r);
    return res;
}

void solve() {
    while (true) {
        cin >> s;
        if (s == "0") break;
        cout << count_repeats(0, s.size()) << "\n";
    }
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
