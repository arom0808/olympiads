#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int maxn = 5e5 + 10;
string s;
int sort_cnt[maxn], pf_sort_cnt[maxn], temp_sort_arr[maxn];
int sa[maxn], isa[maxn], cls[maxn], ncls[maxn], lcp[maxn];

void calc_sa() {
    int n = s.size();
    iota(sa, sa + n, 0);
    sort(sa, sa + n, [](int a, int b) { return s[a] < s[b]; });
    int cnt = 1;
    cls[0] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[sa[i]] != s[sa[i - 1]]) ++cnt;
        cls[i] = cnt - 1;
    }
    for (int i = 0; i < n; ++i) isa[sa[i]] = i;
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
        ncls[0] = cnt - 1;
        for (int i = 1; i < n; ++i) {
            if (cls[isa[sa[i]]] != cls[isa[sa[i - 1]]] ||
                cls[isa[(sa[i] + (1 << k)) % n]] != cls[isa[(sa[i - 1] + (1 << k)) % n]])
                ++cnt;
            ncls[i] = cnt - 1;
        }
        for (int i = 0; i < n; ++i) isa[sa[i]] = i;
        swap(cls, ncls);
    }
}

void calc_lcp() {
    int start_len = 0;
    for (int i = 0; i < s.size(); ++i) {
        int cpos = isa[i];
        if (cpos == s.size() - 1) continue;
        lcp[cpos] = start_len;
        int fpos = sa[cpos], spos = sa[cpos + 1];
        while (fpos + lcp[cpos] < s.size() && spos + lcp[cpos] < s.size() && s[fpos + lcp[cpos]] == s[spos + lcp[cpos]])
            ++lcp[cpos];
        start_len = std::max(0, lcp[cpos] - 1);
    }
}

namespace lcpST {
    int tree[maxn * 4];

    void _init(int v, int l, int r) {
        if (r - l == 1) {
            tree[v] = lcp[l];
            return;
        }
        int mid = (l + r) >> 1;
        _init(v << 1, l, mid);
        _init(v << 1 | 1, mid, r);
        tree[v] = std::min(tree[v << 1], tree[v << 1 | 1]);
    }

    void init() {
        _init(1, 0, s.size());
    }

    int _get_rightest_less(int v, int l, int r, int a, int b, int val) {
        if (l >= b || a >= r || tree[v] >= val) return a - 1;
        if (r - l == 1) return l;
        int mid = (l + r) >> 1;
        int v1 = _get_rightest_less(v << 1 | 1, mid, r, a, b, val);
        if (v1 != a - 1) return v1;
        return _get_rightest_less(v << 1, l, mid, a, b, val);
    }

    int get_rightest_less(int a, int b, int val) {
        return _get_rightest_less(1, 0, s.size(), a, b, val);
    }

    int _get_leftest_less(int v, int l, int r, int a, int b, int val) {
        if (l >= b || a >= r || tree[v] >= val) return b;
        if (r - l == 1) return l;
        int mid = (l + r) >> 1;
        int v1 = _get_leftest_less(v << 1, l, mid, a, b, val);
        if (v1 != b) return v1;
        return _get_leftest_less(v << 1 | 1, mid, r, a, b, val);
    }

    int get_leftest_less(int a, int b, int val) {
        return _get_leftest_less(1, 0, s.size(), a, b, val);
    }
}

namespace ST {
    vector<int> tree[maxn * 2];

    void init() {
        for (int i = 0; i < s.size(); ++i) tree[i + s.size()].push_back(sa[i]);
        for (int i = s.size() - 1; i; --i) {
            tree[i].reserve(tree[i << 1].size() + tree[i << 1 | 1].size());
            merge(tree[i << 1].begin(), tree[i << 1].end(), tree[i << 1 | 1].begin(), tree[i << 1 | 1].end(),
                  back_inserter(tree[i]));
        }
    }

    int cnt_in_seg_in_vec(const vector<int> &vec, int a, int b) {
        return upper_bound(vec.begin(), vec.end(), b) - lower_bound(vec.begin(), vec.end(), a);
    }

    int cnt_in_seg(int l, int r, int a, int b) {
        l += s.size(), r += s.size();
        int ans = 0;
        while (l != r) {
            if (l & 1) ans += cnt_in_seg_in_vec(tree[l++], a, b);
            if (r & 1) ans += cnt_in_seg_in_vec(tree[--r], a, b);
            l >>= 1, r >>= 1;
        }
        return ans;
    }
}

void solve() {
    int n;
    string t;
    cin >> t >> s;
    for (auto &c: s) c = c - 'a' + 1;
    for (auto &c: t) c = c - 'a' + 1;
    n = s.size();
    s.push_back(0);
    s += t;
    s.push_back(0);
    calc_sa();
    calc_lcp();
    lcpST::init();
    ST::init();
    int q;
    cin >> q;
    for (int _ = 0; _ < q; ++_) {
        int sb, se, tb, te;
        cin >> tb >> te >> sb >> se, --sb, --tb;
        int sa_pos = isa[n + 1 + tb];
        int from = lcpST::get_rightest_less(0, sa_pos, te - tb) + 1;
        int to = lcpST::get_leftest_less(sa_pos, s.size() - 1, te - tb) + 1;
        int a = sb, b = se - (te - tb);
        if (a > b) {
            cout << "0\n";
            continue;
        }
        cout << ST::cnt_in_seg(from, to, a, b) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
