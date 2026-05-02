#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 3e5 + 10, inf = 2e9 + 10;

int n, m, P;

struct CableWay {
    int a, b, c;
};

vector<int> all_cs;
CableWay cabways[maxn];
vector<int> bs_by_c[maxn];
int cnt_by_b[maxn];
int min_length[maxn];
int zeros_cnt;

int zip(int c) {
    return lower_bound(all_cs.begin(), all_cs.end(), c) - all_cs.begin();
}

void add_c(int c) {
    for (auto b: bs_by_c[c]) if (cnt_by_b[b]++ == 0) --zeros_cnt;
}

void erase_c(int c) {
    for (auto b: bs_by_c[c]) if (--cnt_by_b[b] == 0) ++zeros_cnt;
}

namespace ST {
    int tree[maxn * 2];
    int sz;

    void init() {
        sz = all_cs.size();
        for (int i = 0; i < sz; ++i) tree[i + sz] = min_length[i];
        for (int i = sz - 1; i; --i) tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
    }

    int get_min(int l, int r) {
        l += sz, r += sz;
        int ans = inf;
        for (; l != r; l >>= 1, r >>= 1) {
            if (l & 1) ans = std::min(ans, tree[l++]);
            if (r & 1) ans = std::min(ans, tree[--r]);
        }
        return ans;
    }
}

void solve() {
    cin >> n >> m >> P;
    for (int i = 0; i < m; ++i) {
        auto &[a,b,c] = cabways[i];
        cin >> a >> b >> c, --a, --b;
        all_cs.push_back(c);
    }
    sort(all_cs.begin(), all_cs.end());
    all_cs.erase(unique(all_cs.begin(), all_cs.end()), all_cs.end());
    for (int i = 0; i < m; ++i) cabways[i].c = zip(cabways[i].c);
    for (int i = 0; i < m; ++i) bs_by_c[cabways[i].c].push_back(cabways[i].b);
    zeros_cnt = n - 1;
    for (int i = 0, j = 0; i < all_cs.size(); ++i) {
        for (; j < all_cs.size() && zeros_cnt; ++j) add_c(j);
        if (!zeros_cnt) min_length[i] = all_cs[j - 1] - all_cs[i] + 1;
        else min_length[i] = inf;
        erase_c(i);
    }
    ST::init();
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        int mlen = r - l + 1 + x;
        int sp = lower_bound(all_cs.begin(), all_cs.end(), l - x) - all_cs.begin();
        int fp = upper_bound(all_cs.begin(), all_cs.end(), l) - all_cs.begin();
        bool ok = ST::get_min(sp, fp) <= mlen;
        if (!ok) {
            int cp = lower_bound(all_cs.begin(), all_cs.end(), l) - all_cs.begin();
            if (cp < all_cs.size()) {
                int mcl = ST::get_min(cp, cp + 1);
                if (0ll + all_cs[cp] + mcl <= r + x) ok = true;
            }
        }
        if (ok) cout << "Yes\n";
        else cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}