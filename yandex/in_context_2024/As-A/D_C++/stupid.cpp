#include <iostream>

using namespace std;

const int32_t maxn = 2e5, maxlogn = 18;
const int64_t inf = 1e18;
int64_t x, a[maxn];
int32_t n, b[maxn];


namespace st {
    pair<int64_t, int32_t> tree[maxlogn][maxn];

    pair<int64_t, int32_t> min_el(int32_t l, int32_t r) {
        int32_t t = __lg(r - l);
        return std::min(tree[t][l], tree[t][r - (1 << t)]);
    }

    void assign() {
        for (int32_t i = 0; i < n; ++i) tree[0][i] = {a[i], i};
        for (int32_t i = n; i < maxn; ++i) tree[0][i] = {inf, i};
        for (int32_t l = 0; l + 1 < maxlogn; ++l)
            for (int32_t i = 0; i + (2 << l) <= maxn; ++i)
                tree[l + 1][i] = std::min(tree[l][i], tree[l][i + (1 << l)]);
    }
}

namespace ps {
    int64_t ps[maxn + 1];

    void assign() {
        ps[0] = 0;
        for (int32_t i = 0; i < maxn; ++i) ps[i + 1] = ps[i] + b[i];
    }

    int64_t sum(int32_t l, int32_t r) {
        return ps[r] - ps[l];
    }
}


int main() {
    freopen("test.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> x;
    for (int32_t i = 0; i < n; ++i) cin >> a[i];
    for (int32_t i = 0; i < n; ++i) cin >> b[i];
    st::assign();
    ps::assign();
    int64_t res = 0;
    for (int32_t l = 0; l < n; ++l) {
        for (int32_t r = l + 1; r <= n; ++r) {
            if (st::min_el(l, r).first + ps::sum(l, r) <= x)++res;
        }
    }
    cout << res << "\n";
}