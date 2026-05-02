#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int maxn = 1e5 + 1;

string s;
int n;
int sort_cnt[maxn], pf_sort_cnt[maxn], temp_sort_arr[maxn];
int sa[maxn], isa[maxn], cls[maxn], tcls[maxn];

void calc_sa() {
    int cnt = 256;
    for (int i = 0; i < cnt; ++i) sort_cnt[i] = 0;
    for (int i = 0; i < n; ++i) ++sort_cnt[s[i]];
    pf_sort_cnt[0] = 0;
    for (int i = 0; i < cnt; ++i) pf_sort_cnt[i + 1] = pf_sort_cnt[i] + sort_cnt[i];
    for (int i = 0; i < n; ++i) sa[pf_sort_cnt[s[i]]++] = i;
    for (int i = 0; i < n; ++i) isa[sa[i]] = i;
    cnt = 1;
    cls[0] = cnt - 1;
    for (int i = 1; i < n; ++i) {
        if (s[sa[i - 1]] != s[sa[i]]) ++cnt;
        cls[i] = cnt - 1;
    }
    for (int k = 0; (1 << k) < n; ++k) {
        for (int i = 0; i < n; ++i) sa[i] = i;
        for (int i = 0; i < cnt; ++i) sort_cnt[i] = 0;
        for (int i = 0; i < n; ++i) ++sort_cnt[cls[i]];
        pf_sort_cnt[0] = 0;
        for (int i = 0; i < cnt; ++i) pf_sort_cnt[i + 1] = pf_sort_cnt[i] + sort_cnt[i];
        for (int i = 0; i < n; ++i) temp_sort_arr[pf_sort_cnt[cls[isa[(sa[i] + (1 << k)) % n]]]++] = sa[i];
        swap(sa, temp_sort_arr);
        pf_sort_cnt[0] = 0;
        for (int i = 0; i < cnt; ++i) pf_sort_cnt[i + 1] = pf_sort_cnt[i] + sort_cnt[i];
        for (int i = 0; i < n; ++i) temp_sort_arr[pf_sort_cnt[cls[isa[sa[i]]]]++] = sa[i];
        swap(sa, temp_sort_arr);
        cnt = 1;
        tcls[0] = cnt - 1;
        for (int i = 1; i < n; ++i) {
            if (cls[isa[sa[i]]] != cls[isa[sa[i - 1]]] ||
                cls[isa[(sa[i] + (1 << k)) % n]] != cls[isa[(sa[i - 1] + (1 << k)) % n]])
                ++cnt;
            tcls[i] = cnt - 1;
        }
        for (int i = 0; i < n; ++i) isa[sa[i]] = i;
        swap(cls, tcls);
    }
}

void solve() {
    int k;
    std::getline(cin, s);
    cin >> k, --k;
    n = s.size();
    calc_sa();
    if (cls[n - 1] < k) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    int sa_id = lower_bound(cls, cls + n, k) - cls;
    int shift = sa[sa_id];
    rotate(s.begin(), s.begin() + shift, s.end());
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // stupid_solve();
    solve();
    return 0;
}
