#include <algorithm>
#include <iostream>
#include <random>
#include <set>

using namespace std;
using ll = long long;
using ull = unsigned long long;

constexpr ull mod1 = 1000000000000000003ull, mod2 = 0;

template<ull M>
struct HV {
    ull val = 0;

    HV() = default;

    HV(ull _val): val(_val) {
        if (M && val >= M) val %= M;
    }

    HV(const HV<M> &hv): val(hv.val) {
    }

    HV operator+(const HV &rhs) const {
        if (val + rhs.val >= M) return val + rhs.val - M;
        return val + rhs.val;
    }

    HV operator-(const HV &rhs) const {
        if (val < rhs.val) return val - rhs.val + M;
        return val - rhs.val;
    }

    bool operator<(const HV &rhs) const {
        return val < rhs.val;
    }

    bool operator!=(const HV &rhs) const {
        return val != rhs.val;
    }
};

struct pHV {
    HV<mod1> v1;
    HV<mod2> v2;

    pHV() = default;

    pHV(ull val): v1(val), v2(val) {
    }

    pHV(const HV<mod1> &v1, const HV<mod2> &v2): v1(v1), v2(v2) {
    }

    pHV operator+(const pHV &rhs) const {
        return {v1 + rhs.v1, v2 + rhs.v2};
    }

    pHV operator-(const pHV &rhs) const {
        return {v1 - rhs.v1, v2 - rhs.v2};
    }

    bool operator<(const pHV &rhs) const {
        if (v1 != rhs.v1) return v1 < rhs.v1;
        return v2 < rhs.v2;
    }
};

constexpr int maxn = 1002, maxval = 1e5 + 2;
mt19937_64 rng(235235);
int arr1[maxn], arr2[maxn];
pHV hbv[maxval];
pHV hpf1[maxn], hpf2[maxn];
int n, m;
set<pHV> hset1[maxn], hset2[maxn], hset_intersct[maxn];

void solve() {
    for (int i = 0; i < maxval; ++i) hbv[i] = rng();
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr1[i];
    for (int i = 0; i < n; ++i) hpf1[i + 1] = hpf1[i] + hbv[arr1[i]];
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> arr2[i];
    for (int i = 0; i < m; ++i) hpf2[i + 1] = hpf2[i] + hbv[arr2[i]];
    for (int len = 1; len <= n; ++len) for (int i = 0; i + len <= n; ++i) hset1[len].insert(hpf1[i + len] - hpf1[i]);
    for (int len = 1; len <= m; ++len) for (int i = 0; i + len <= m; ++i) hset2[len].insert(hpf2[i + len] - hpf2[i]);
    for (int len = std::min(n, m); len; --len) {
        set_intersection(hset1[len].begin(), hset1[len].end(), hset2[len].begin(), hset2[len].end(),
                         inserter(hset_intersct[len], hset_intersct[len].begin()));
        if (!hset_intersct[len].empty()) {
            cout << len << "\n";
            return;
        }
    }
    cout << "0\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
