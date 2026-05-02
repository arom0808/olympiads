#include <iostream>

using namespace std;
using ll = int64_t;

constexpr int maxn = 100, maxk = 1000, inf = 1e9 + 10;
int n, m, k;
__int128 buys[maxn][maxk], sells[maxn][maxk];
__int128 dist[maxn][maxn], mns[maxn][maxn];
__int128 fbdist[maxn];

bool check_dc(int dc) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mns[i][j] += dist[i][j] * dc;
            mns[i][j] *= 20001;
            mns[i][j] -= 1;
        }
    }
    for (int i = 0; i < n; ++i) fbdist[i] = 0;
    for (int _ = 0; _ < n; ++_)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                fbdist[j] = std::min(fbdist[j], fbdist[i] + mns[i][j]);
    bool otc_cycle_ex = false;
    for (int i = 0; i < n && !otc_cycle_ex; ++i)
        for (int j = 0; j < n && !otc_cycle_ex; ++j)
            if (fbdist[j] > fbdist[i] + mns[i][j]) otc_cycle_ex = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mns[i][j] += 1;
            mns[i][j] /= 20001;
            mns[i][j] -= dist[i][j] * dc;
        }
    }
    return otc_cycle_ex;
}

void solve() {
    ll tvl1, tvl2;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) dist[i][j] = inf, mns[i][j] = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < k; ++j) cin >> tvl1 >> tvl2, buys[i][j] = tvl1, sells[i][j] = tvl2;
    for (int i = 0, v, w, t; i < m; ++i) {
        cin >> v >> w >> t, --v, --w;
        dist[v][w] = t;
    }
    for (int mid = 0; mid < n; ++mid)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dist[i][j] = std::min(dist[i][j], dist[i][mid] + dist[mid][j]);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int t = 0; t < k; ++t)
                if (buys[i][t] != -1 && sells[j][t] != -1)
                    mns[i][j] = std::min(mns[i][j], buys[i][t] - sells[j][t]);
    int l = 0, r = 1e9 + 10;
    while (r - l != 1) {
        int mid = (l + r) / 2;
        if (check_dc(mid)) l = mid;
        else r = mid;
    }
    cout << l << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
