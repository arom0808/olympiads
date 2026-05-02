#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>

using namespace std;

constexpr int maxn = 2e5 + 2;
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
        temp_cls[0] = 0;
        for (int i = 1; i < n; ++i) {
            if (cls[isa[sa[i - 1]]] != cls[isa[sa[i]]] ||
                cls[isa[(sa[i - 1] + (1 << k)) % n]] != cls[isa[(sa[i] + (1 << k)) % n]])
                ++cnt;
            temp_cls[i] = cnt - 1;
        }
        swap(cls, temp_cls);
        for (int i = 0; i < n; ++i) isa[sa[i]] = i;
    }
}

void calc_lcp() {
    int start_val = 0;
    for (int i = 0; i < n; ++i) {
        int pos = isa[i];
        if (pos + 1 == n) continue;
        lcp[pos] = start_val;
        while (sa[pos] + lcp[pos] < n && sa[pos + 1] + lcp[pos] < n && s[sa[pos] + lcp[pos]] == s[
                   sa[pos + 1] + lcp[pos]])
            ++lcp[pos];
        start_val = std::max(0, lcp[pos] - 1);
    }
}

namespace SNM {
    struct Node {
        set<int> heights;
        int size, p;
    };

    Node tree[maxn];

    void init() {
        for (int i = 0; i < n; ++i) {
            tree[i].heights.insert(n - sa[i] - 1);
            tree[i].size = 1;
            tree[i].p = i;
        }
    }

    int get_root(int x) {
        if (tree[x].p == x) return x;
        return tree[x].p = get_root(tree[x].p);
    }

    int merge(int a, int b) {
        a = get_root(a), b = get_root(b);
        if (tree[a].size > tree[b].size) swap(a, b);
        int res = 1e9;
        for (auto ch: tree[a].heights) {
            auto it = tree[b].heights.lower_bound(ch);
            if (it != tree[b].heights.end()) res = std::min(res, std::abs(ch - *it));
            if (it != tree[b].heights.begin()) res = std::min(res, std::abs(ch - *prev(it)));
        }
        tree[b].heights.insert(tree[a].heights.begin(), tree[a].heights.end());
        tree[a].heights.clear();
        tree[b].size += tree[a].size;
        tree[a].p = b;
        return res;
    }
}

struct Fract {
    int a = 0, b = 0;

    Fract() = default;

    Fract(int a, int b): a(a), b(b) {
        simplify();
    }

    void simplify() {
        int g = std::gcd(a, b);
        a /= g, b /= g;
    }

    bool operator<(const Fract &rhs) const {
        return 1ll * a * rhs.b < 1ll * rhs.a * b;
    }
};

int poss[maxn];

void solve() {
    cin >> s;
    s += '\0';
    n = s.size();
    calc_sa();
    calc_lcp();
    SNM::init();
    iota(poss, poss + n, 0);
    sort(poss, poss + n, [](int a, int b) { return lcp[a] > lcp[b]; });
    Fract ans(1,1);
    for (int _ = 0; _ < n; ++_) {
        int lid = poss[_];
        if (lcp[lid] == 0) break;
        int cres = SNM::merge(lid, lid + 1);
        Fract cans(lcp[lid] + cres, cres);
        if (ans.a == 0 || ans < cans) ans = cans;
    }
    cout << ans.a << "/" << ans.b << "\n";
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
