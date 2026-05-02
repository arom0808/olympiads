#include <iostream>

using namespace std;

constexpr int32_t maxn = 1e4, maxk = 100, maxa = 1e6 + 1;
constexpr int64_t inf = 1e18;
int32_t n, k;

int64_t dp[maxk + 1][maxn + 1];
int64_t xs[maxn];

struct Line {
    int64_t k, b;
    int64_t get(int64_t x) const { return k * x + b; }
};

namespace LiChaoTree {
    struct Node {
        Line line;
        bool inited;

        void init() {
            inited = true;
            line.k = 0, line.b = inf;
        }
    };

    Node tree[maxa * 4];
    int32_t size = maxa;

    void transfer_init(int32_t v, int32_t l, int32_t r) {
        if (l >= r || !tree[v].inited) return;
        if (r - l > 1) tree[v * 2].init(), tree[v * 2 + 1].init();
        tree[v].inited = false;
    }

    void _add(int32_t v, int32_t l, int32_t r, Line cur) {
        if (l >= r) return;
        transfer_init(v, l, r);
        int32_t m = (l + r) / 2;
        bool a = cur.get(l) < tree[v].line.get(l), b = cur.get(m) < tree[v].line.get(m);
        if (b) swap(tree[v].line, cur);
        if (r - l == 1) return;
        if (a != b) _add(v * 2, l, (l + r) / 2, cur);
        else _add(v * 2 + 1, (l + r) / 2, r, cur);
    }

    int64_t _min_val(int32_t v, int32_t l, int32_t r, int32_t x) {
        if (l >= r || l > x || x >= r) return inf;
        transfer_init(v, l, r);
        if (r - l == 1) return tree[v].line.get(x);
        int32_t m = (l + r) / 2;
        if (x < m) return std::min(tree[v].line.get(x), _min_val(v * 2, l, m, x));
        return std::min(tree[v].line.get(x), _min_val(v * 2 + 1, m, r, x));
    }

    void init() {
        tree[1].init();
    }

    void add(Line cur) {
        _add(1, 0, size, cur);
    }

    int64_t min_val(int32_t x) {
        return _min_val(1, 0, size, x);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> k;
    for (int32_t i = 0; i < n; ++i) cin >> xs[i];
    for (int32_t i = 1; i <= n; ++i) dp[1][i] = (xs[i - 1] - xs[0]) * (xs[i - 1] - xs[0]);
    for (int32_t j = 2; j <= k; ++j) {
        LiChaoTree::init();
        for (int32_t i = j; i <= n; ++i) {
            LiChaoTree::add(Line(-xs[i - 1] * 2, dp[j - 1][i - 1] + xs[i - 1] * xs[i - 1]));
            dp[j][i] = LiChaoTree::min_val(xs[i - 1]) + xs[i - 1] * xs[i - 1];
        }
    }
    cout << dp[k][n] << "\n";
    return 0;
}
