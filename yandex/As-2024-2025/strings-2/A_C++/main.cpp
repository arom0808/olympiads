#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 150001;

int n, m;
int s[maxn];
int cnt_sort[maxn], pf_cnt_sort[maxn + 1], tsort_arr[maxn];
int lcpa[maxn];
int sa[maxn], isa[maxn], cls[maxn], tcls[maxn];

void calc_suff_arr() {
    for (int i = 0; i <= m; ++i) cnt_sort[i] = 0;
    for (int i = 0; i < n; ++i) ++cnt_sort[s[i]];
    pf_cnt_sort[0] = 0;
    for (int i = 0; i <= m; ++i) pf_cnt_sort[i + 1] = pf_cnt_sort[i] + cnt_sort[i];
    for (int i = 0; i < n; ++i) sa[pf_cnt_sort[s[i]]++] = i;
    for (int i = 0; i < n; ++i) isa[sa[i]] = i;
    int cnt = 1, tcnt = 0;
    cls[0] = cnt - 1;
    for (int i = 1; i < n; ++i) {
        if (s[sa[i]] != s[sa[i - 1]]) ++cnt;
        cls[i] = cnt - 1;
    }
    for (int k = 0; (1 << k) < n; ++k) {
        for (int i = 0; i < n; ++i) sa[i] = i;
        for (int i = 0; i < cnt; ++i) cnt_sort[i] = 0;
        for (int i = 0; i < n; ++i) ++cnt_sort[cls[i]];
        pf_cnt_sort[0] = 0;
        for (int i = 0; i < cnt; ++i)
            pf_cnt_sort[i + 1] = pf_cnt_sort[i] + cnt_sort[i];
        for (int i = 0; i < n; ++i)
            tsort_arr[pf_cnt_sort[cls[isa[(sa[i] + (1 << k)) % n]]]++] = sa[i];
        swap(sa, tsort_arr);
        pf_cnt_sort[0] = 0;
        for (int i = 0; i < cnt; ++i)
            pf_cnt_sort[i + 1] = pf_cnt_sort[i] + cnt_sort[i];
        for (int i = 0; i < n; ++i)
            tsort_arr[pf_cnt_sort[cls[isa[sa[i]]]]++] = sa[i];
        swap(sa, tsort_arr);
        tcnt = 1;
        tcls[0] = tcnt - 1;
        for (int i = 1; i < n; ++i) {
            if (cls[isa[sa[i]]] != cls[isa[sa[i - 1]]] ||
                cls[isa[(sa[i] + (1 << k)) % n]] != cls[isa[(sa[i - 1] + (1 << k)) % n]])
                ++tcnt;
            tcls[i] = tcnt - 1;
        }
        for (int i = 0; i < n; ++i) isa[sa[i]] = i;
        swap(cls, tcls), swap(cnt, tcnt);
    }
}

void calc_lcp_arr() {
    int start_len = 0;
    for (int i = 0; i < n; ++i) {
        int pos = isa[i];
        if (pos == n - 1) continue;
        int p1 = i, p2 = sa[pos + 1];
        lcpa[pos] = start_len;
        while (p1 + lcpa[pos] < n && p2 + lcpa[pos] < n && s[p1 + lcpa[pos]] == s[p2 + lcpa[pos]]) ++lcpa[pos];
        start_len = std::max(lcpa[pos] - 1, 0);
    }
}


void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> s[i];
    s[n++] = 0;
    calc_suff_arr();
    calc_lcp_arr();
    ll ans;
    int ans_len, ans_start;
    ans = n - 1, ans_len = n - 1, ans_start = 0;
    vector<pair<int, int> > d;
    for (int i = 1; i + 1 < n; ++i) {
        while (!d.empty() && d.back().first >= lcpa[i]) {
            int len = d.back().first;
            d.pop_back();
            int cnt = i - (d.empty() ? 0 : d.back().second);
            ll cans = 1ll * cnt * len;
            if (cans > ans) ans = cans, ans_len = len, ans_start = sa[i];
        }
        d.emplace_back(lcpa[i], i);
    }
    while (!d.empty()) {
        int len = d.back().first, cnt = n - d.back().second;
        ll cans = 1ll * cnt * len;
        if (cans > ans) ans = cans, ans_len = len, ans_start = sa[n - 1];
        d.pop_back();
    }
    cout << ans << "\n";
    cout << ans_len << "\n";
    for (int i = 0; i < ans_len; ++i) cout << s[ans_start + i] << " ";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
