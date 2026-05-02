#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 5e5 + 2, maxlogn = 19;
string s;
int n;
int sort_cnt[maxn], pf_sort_cnt[maxn], temp_sort_arr[maxn];
int sa[maxn], isa[maxn], cls[maxn], temp_cls[maxn];
int lcp[maxn];

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
        if (s[sa[i]] != s[sa[i - 1]]) ++cnt;
        cls[i] = cnt - 1;
    }
    for (int k = 0; (1 << k) < n; ++k) {
        for (int i = 0; i < cnt; ++i) sort_cnt[i] = 0;
        for (int i = 0; i < n; ++i) ++sort_cnt[cls[i]];
        pf_sort_cnt[0] = 0;
        for (int i = 0; i < cnt; ++i) pf_sort_cnt[i + 1] = pf_sort_cnt[i] + sort_cnt[i];
        for (int i = 0; i < n; ++i) sa[pf_sort_cnt[cls[isa[(i + (1 << k)) % n]]]++] = i;
        pf_sort_cnt[0] = 0;
        for (int i = 0; i < cnt; ++i) pf_sort_cnt[i + 1] = pf_sort_cnt[i] + sort_cnt[i];
        for (int i = 0; i < n; ++i) temp_sort_arr[pf_sort_cnt[cls[isa[sa[i]]]]++] = sa[i];
        swap(sa, temp_sort_arr);
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
        if (isa[i] + 1 == n) continue;
        lcp[isa[i]] = start_len;
        while (i + lcp[isa[i]] < n && sa[isa[i] + 1] + lcp[isa[i]] < n &&
               s[i + lcp[isa[i]]] == s[sa[isa[i] + 1] + lcp[isa[i]]])
            ++lcp[isa[i]];
        start_len = max(0, lcp[isa[i]] - 1);
    }
    lcp[n - 1] = 0;
}

namespace ST {
    int min_tree[maxlogn][maxn], max_tree[maxlogn][maxn];

    void init() {
        for (int i = 0; i < n; ++i) min_tree[0][i] = max_tree[0][i] = n - sa[i] - 1;
        for (int k = 1; (1 << k) <= n; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                min_tree[k][i] = std::min(min_tree[k - 1][i], min_tree[k - 1][i + (1 << (k - 1))]);
                max_tree[k][i] = std::max(max_tree[k - 1][i], max_tree[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int get_max(int l, int r) {
        int k = __lg(r - l);
        return std::max(max_tree[k][l], max_tree[k][r - (1 << k)]);
    }

    int get_min(int l, int r) {
        int k = __lg(r - l);
        return std::min(min_tree[k][l], min_tree[k][r - (1 << k)]);
    }
}

namespace oST {
    int tree[maxlogn][maxn];

    void init() {
        for (int i = 0; i < n; ++i) tree[0][i] = lcp[i];
        for (int k = 1; (1 << k) <= n; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                tree[k][i] = std::min(tree[k - 1][i], tree[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int get_min(int l, int r) {
        int k = __lg(r - l);
        return std::min(tree[k][l], tree[k][r - (1 << k)]);
    }
}

int left_lower[maxn], right_lower[maxn];

void calc_lower() {
    vector<pair<int, int> > st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.back().first >= lcp[i]) st.pop_back();
        left_lower[i] = st.empty() ? -1 : st.back().second;
        st.emplace_back(lcp[i], i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && st.back().first >= lcp[i]) st.pop_back();
        right_lower[i] = st.empty() ? n - 1 : st.back().second;
        st.emplace_back(lcp[i], i);
    }
}

void stupid_solve() {
    cin >> s;
    s += '\0';
    n = s.size();
    calc_sa();
    calc_lcp();
    ST::init();
    oST::init();
    calc_lower();
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ll a = oST::get_min(i, j);
            int l1 = n - sa[i] - 1, l2 = n - sa[j] - 1;
            ans = std::max(ans, a * a + a + std::max(l1, l2) - std::min(l1, l2));
        }
    }
    cout << ans << "\n";
}

// void solve() {
//     cin >> s;
//     s += '\0';
//     n = s.size();
//     calc_sa();
//     calc_lcp();
//     ST::init();
//     oST::init();
//     calc_lower();
//     ll ans = 0;
//     // for (int i = 1; i + 1 < n; ++i) {
//     //     int l = left_lower[i], r = right_lower[i];
//     //     ans = std::max(ans, 1ll * lcp[i] * lcp[i] + lcp[i] + ST::get_max(l + 1, r + 1) - ST::get_min(l + 1, r + 1));
//     // }
//     cout << ans << "\n";
// }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    stupid_solve();
    return 0;
}
