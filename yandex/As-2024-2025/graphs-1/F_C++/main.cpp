#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using ll = int64_t;

constexpr int maxn = 1e5;
constexpr ll inf = 1e18;

int n, m, s, t, gu, gv;
ll dist_of_s[maxn], dist_of_u[maxn], dist_of_v[maxn];
bool used[maxn];
vector<int> fupd_s[maxn], fupd_u[maxn], fupd_v[maxn];
vector<pair<int, int> > g[maxn];
ll dp[maxn][2][2];

void dijkstra(int start_v, ll cds[maxn], vector<int> cfupd[maxn]) {
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<> > q;
    for (int i = 0; i < n; ++i) cds[i] = inf, used[i] = false;
    q.emplace(0, start_v);
    cds[start_v] = 0;
    while (!q.empty()) {
        auto [cd, v] = q.top();
        q.pop();
        if (used[v]) continue;
        used[v] = true;
        for (auto [u, w]: g[v]) {
            if (cds[u] < cds[v] + w) continue;
            if (cds[u] > cds[v] + w) {
                cfupd[u].clear();
                cds[u] = cds[v] + w;
                q.emplace(cds[u], u);
            }
            cfupd[u].push_back(v);
        }
    }
}

void update_dp_val(int v) {
    if (!dp[v][0][0]) return;
    dp[v][0][0] = 0;
    dp[v][1][0] = dist_of_u[v];
    dp[v][0][1] = dist_of_v[v];
    dp[v][1][1] = dist_of_u[v] + dist_of_v[v];
    for (auto u: fupd_s[v]) {
        update_dp_val(u);
        dp[v][1][0] = std::min(dp[v][1][0], dp[u][1][0]);
        dp[v][0][1] = std::min(dp[v][0][1], dp[u][0][1]);
        dp[v][1][1] = std::min(dp[v][1][1],
                               std::min(dp[u][1][1],
                                        std::min(dp[u][1][0] + dist_of_v[v], dp[u][0][1] + dist_of_u[v])));
    }
}

void solve() {
    cin >> n >> m >> s >> t >> gu >> gv, --s, --t, --gu, --gv;
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c, --a, --b;
        g[a].emplace_back(b, c), g[b].emplace_back(a, c);
    }
    dijkstra(s, dist_of_s, fupd_s);
    dijkstra(gu, dist_of_u, fupd_u);
    dijkstra(gv, dist_of_v, fupd_v);
    for (int i = 0; i < n; ++i) for (int i1 = 0; i1 < 2; ++i1) for (int i2 = 0; i2 < 2; ++i2) dp[i][i1][i2] = inf;
    update_dp_val(t);
    ll ans = dist_of_v[gu];
    for (int v = 0; v < n; ++v) ans = std::min(ans, dp[v][1][1]);
    cout << ans << "\n";
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
