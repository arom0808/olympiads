#include <iostream>
#include <numeric>
#include <list>
#include <vector>

using namespace std;
using ll = long long;

constexpr int maxn = 5e4, maxlogn = 16;
constexpr ll inf = 1e18;
int nums[maxn];
int n;
ll pf[maxn + 1];

namespace SpT {
    ll tree[maxlogn][maxn + 1];

    void build() {
        for (int i = 0; i <= n; ++i) tree[0][i] = pf[i];
        for (int p = 1; (1 << p) <= n + 1; ++p)
            for (int i = 0; i + (1 << p) <= n + 1; ++i)
                tree[p][i] = std::max(tree[p - 1][i], tree[p - 1][i + (1 << (p - 1))]);
    }

    ll max_val(int l, int r) {
        int p = __lg(r - l);
        return std::max(tree[p][l], tree[p][r - (1 << p)]);
    }
}

namespace ST {
    ll tree[maxn * 2];

    void init() {
        for (int i = 0; i < n * 2; ++i) tree[i] = -inf;
    }

    void set(int pos, ll val) {
        pos += n;
        tree[pos] = val;
        for (pos >>= 1; pos; pos >>= 1) tree[pos] = std::max(tree[pos << 1], tree[pos << 1 | 1]);
    }

    ll max_val(int l, int r) {
        l += n, r += n;
        ll ans = -inf;
        while (l < r) {
            if (l & 1) ans = std::max(ans, tree[l++]);
            if (r & 1) ans = std::max(ans, tree[--r]);
            l >>= 1, r >>= 1;
        }
        return ans;
    }
}

struct MSEl {
    int pos, max_val;
    ll max_sumdmax;
};

int get_last_pre(int pos, const vector<MSEl> &arr) {
    if (arr.back().pos >= pos) return arr.size();
    int l = -1, r = arr.size() - 1;
    while (r - l != 1) {
        int m = (r + l) / 2;
        if (arr[m].pos < pos) r = m;
        else l = m;
    }
    return r;
}

void solve() {
    ll ans = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    for (int i = 0; i < n; ++i) pf[i + 1] = pf[i] + nums[i];
    SpT::build();
    ST::init();
    list<pair<int, int> > glist;
    glist.emplace_back(n, 0);
    vector<MSEl> max_stack;
    for (int i = n - 1; i >= 0; --i) {
        while (!max_stack.empty() && nums[i] >= max_stack.back().max_val) {
            max_stack.pop_back();
            ST::set(max_stack.size(), -inf);
        }
        max_stack.emplace_back(i, nums[i]);
        max_stack.back().max_sumdmax =
                SpT::max_val(i + 1, (max_stack.size() == 1) ? (n + 1) : (max_stack[max_stack.size() - 2].pos + 1)) -
                nums[i];
        ST::set(max_stack.size() - 1, max_stack.back().max_sumdmax);
        glist.emplace_front(i, nums[i]);
        for (auto it = glist.begin(); next(it) != glist.end(); ++it)
            it->second = std::gcd(it->second, nums[i]);
        for (auto it = glist.begin(), nit = next(it); nit != glist.end(); nit = next(it)) {
            if (it->second == nit->second) glist.erase(nit);
            else ++it;
        }
        for (auto it = glist.begin(), nit = next(it); nit != glist.end(); it = nit, ++nit) {
            int l = it->first, r = nit->first;
            int midl = get_last_pre(l, max_stack), midr = get_last_pre(r, max_stack);
            if (midl < max_stack.size() && (!midl || max_stack[midl - 1].pos != l)) {
                int cr = std::min(!midl ? n : max_stack[midl - 1].pos, r);
                ans = std::max(ans, (SpT::max_val(l + 1, cr + 1) - max_stack[midl].max_val - pf[i]) * it->second);
            }
            if (midr < max_stack.size()) {
                int cr = std::min(midr == 0 ? n : max_stack[midr - 1].pos, r);
                ans = std::max(ans, (SpT::max_val(l + 1, cr + 1) - max_stack[midr].max_val - pf[i]) * it->second);
            }
            if (midr + 1 < midl)
                ans = std::max(ans, (ST::max_val(midr + 1, midl) - pf[i]) * it->second);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
