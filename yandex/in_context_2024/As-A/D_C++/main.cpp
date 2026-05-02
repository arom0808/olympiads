#include <iostream>
#include <vector>

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

int64_t res = 0;

int32_t dbs(int32_t _l, int32_t _r, int64_t sum) {
    int32_t l = _l, r = _r;
    while (l != r) {
        int32_t m = (l + r) / 2 + (l + r) % 2;
        if (ps::sum(_l, m) <= sum) l = m;
        else r = m - 1;
    }
    return l - _l;
}

int32_t rbs(int32_t _l, int32_t _r, int64_t sum) {
    int32_t l = _l, r = _r;
    while (l != r) {
        int32_t m = (l + r) / 2;
        if (ps::sum(m, _r) <= sum) r = m;
        else l = m + 1;
    }
    return _r - l;
}

inline int32_t ubs(int32_t _l, int32_t _r, int64_t sum, bool rev = false, int32_t minus_val = 0) {
    int32_t nr = (rev ? rbs(_l, _r, sum) : dbs(_l, _r, sum)) - minus_val;
    return nr < 0 ? 0 : nr;
}

void dac(int32_t l, int32_t r) {
    if (l == r) return;
    int32_t min_pos = st::min_el(l, r).second;
    if (r - l < min(r - min_pos, min_pos - l + 1) * (__lg(max(r - min_pos, min_pos - l + 1)) + 1)) {
        for (int32_t t = l, y = min_pos + 1; t <= min_pos; ++t) {
            while (y < r && ps::sum(t, y) + a[min_pos] + b[y] <= x) ++y;
            if (ps::sum(t, y) + a[min_pos] <= x) res += 1ll * (y - min_pos);
        }
    } else {
        if (r - min_pos > min_pos - l + 1)
            for (int32_t t = l; t <= min_pos; ++t)
                res += 1ll * ubs(t, r, x - a[min_pos], false, min_pos - t);
        else
            for (int32_t y = min_pos; y < r; ++y)
                res += ubs(l, y + 1, x - a[min_pos], true, y - min_pos);
    }
    dac(l, min_pos);
    dac(min_pos + 1, r);
}

int main() {
//    freopen("test.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> x;
    for (int32_t i = 0; i < n; ++i) cin >> a[i];
    for (int32_t i = 0; i < n; ++i) cin >> b[i];
    st::assign();
    ps::assign();
    dac(0, n);
    cout << res << "\n";
    return 0;
}
