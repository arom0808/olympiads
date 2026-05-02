#include <iostream>
#include <limits>

using namespace std;
using ll = long long;


constexpr int maxn = 1e5 + 2;
int n;
string s;
int sort_cnt[maxn], pf_sort_cnt[maxn], temp_sa[maxn];
int sa[maxn], isa[maxn], cls[maxn], temp_cls[maxn];
int cnt;
int lcp[maxn];

void calc_sa() {
    cnt = 256;
    for (int i = 0; i < cnt; ++i) sort_cnt[i] = 0;
    for (int i = 0; i < n; ++i) ++sort_cnt[128 + s[i]];
    pf_sort_cnt[0] = 0;
    for (int i = 0; i < cnt; ++i) pf_sort_cnt[i + 1] = pf_sort_cnt[i] + sort_cnt[i];
    for (int i = 0; i < n; ++i) sa[pf_sort_cnt[128 + s[i]]++] = i;
    for (int i = 0; i < n; ++i) isa[sa[i]] = i;
    cnt = 1;
    cls[0] = cnt - 1;
    for (int i = 1; i < n; ++i) {
        if (s[sa[i]] != s[sa[i - 1]]) ++cnt;
        cls[i] = cnt - 1;
    }
    for (int k = 0; (1 << k) < n; ++k) {
        for (int i = 0; i < n; ++i) sa[i] = i;
        for (int i = 0; i < cnt; ++i) sort_cnt[i] = 0;
        for (int i = 0; i < n; ++i) ++sort_cnt[cls[i]];
        pf_sort_cnt[0] = 0;
        for (int i = 0; i < cnt; ++i) pf_sort_cnt[i + 1] = pf_sort_cnt[i] + sort_cnt[i];
        for (int i = 0; i < n; ++i) temp_sa[pf_sort_cnt[cls[isa[(sa[i] + (1 << k)) % n]]]++] = sa[i];
        swap(sa, temp_sa);
        pf_sort_cnt[0] = 0;
        for (int i = 0; i < cnt; ++i) pf_sort_cnt[i + 1] = pf_sort_cnt[i] + sort_cnt[i];
        for (int i = 0; i < n; ++i) temp_sa[pf_sort_cnt[cls[isa[sa[i]]]]++] = sa[i];
        swap(sa, temp_sa);
        cnt = 1;
        temp_cls[0] = cnt - 1;
        for (int i = 1; i < n; ++i) {
            if (cls[isa[sa[i]]] != cls[isa[sa[i - 1]]] ||
                cls[isa[(sa[i] + (1 << k)) % n]] != cls[isa[(sa[i - 1] + (1 << k)) % n]])
                ++cnt;
            temp_cls[i] = cnt - 1;
        }
        swap(cls, temp_cls);
        for (int i = 0; i < n; ++i) isa[sa[i]] = i;
    }
}

void calc_lcp() {
    int start_len = 0;
    for (int i = 0; i < n; ++i) {
        int cpos = isa[i];
        if (cpos == n - 1) continue;
        lcp[cpos] = start_len;
        int fpos = sa[cpos], spos = sa[cpos + 1];
        while (fpos + lcp[cpos] < n && spos + lcp[cpos] < n && s[fpos + lcp[cpos]] == s[spos + lcp[cpos]])
            ++lcp[cpos];
        start_len = std::max(0, lcp[cpos] - 1);
    }
}

void solve() {
    std::getline(cin, s);
    s += numeric_limits<char>::min();
    n = s.size();
    calc_sa();
    calc_lcp();
    --n;
    s.pop_back();
    ll k;
    cin >> k, --k;
    for (int i = 1; i <= n; ++i) {
        int clen = n - sa[i] - lcp[i - 1];
        if (k < clen) {
            cout << s.substr(sa[i], lcp[i - 1] + k + 1) << "\n";
            return;
        }
        k -= clen;
    }
    cout << s.substr(sa[n]) << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
