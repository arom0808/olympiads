#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    int n, a, k, o = 0, p, l = 0, i;
    cin >> n >> a >> k;
    vector<int> arr;
    for (int i = 0; a > 0; i++) {
        p = pow(n, i);
        o += (a % 10) * p;
        a /= 10;
    }
    while (o != 0) {
        i = o % k;
        o /= k;
        arr.push_back(i);
        l++;
    }
    for (int y = l - 1; y >= 0; y--) {
        cout << arr[y];
    }
    cout << endl;
    return 0;
}


// #include <iostream>
// #include <vector>
// #include <queue>
//
// using namespace std;
// using ll = long long;
//
// constexpr ll maxn = 1e5, mod = 1e9 + 7;
// constexpr ll inf = 1e18;
//
// vector<pair<ll, ll> > g[maxn];
// ll n, m;
// bool used[maxn], in_way[maxn];
// ll dist1[maxn], dist2[maxn];
// ll cnt_from_1[maxn], cnt_from_2[maxn];
//
// void djktstra(ll *dist, ll s) {
//     for (ll i = 0; i < n; ++i) dist[i] = inf;
//     for (ll i = 0; i < n; ++i) used[i] = false;
//     dist[s] = 0;
//     priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<> > que;
//     que.emplace(0, s);
//     while (!que.empty()) {
//         auto [d,v] = que.top();
//         que.pop();
//         if (used[v]) continue;
//         used[v] = true;
//         for (auto [u,w]: g[v]) {
//             if (dist[v] + w >= dist[u]) continue;
//             dist[u] = dist[v] + w;
//             que.emplace(dist[u], u);
//         }
//     }
// }
//
// ll calc_cnt(ll *cnt_arr, ll *dist, ll s, ll v) {
//     if (cnt_arr[v] != -1) return cnt_arr[v];
//     if (s == v) return cnt_arr[v] = 1;
//     cnt_arr[v] = 0;
//     for (auto [u,w]: g[v])
//         if (dist[u] == dist[v] - w)
//             cnt_arr[v] = (cnt_arr[v] + calc_cnt(cnt_arr, dist, s, u)) % mod;
//     return cnt_arr[v];
// }
//
// void solve() {
//     cin >> n >> m;
//     ll s, f;
//     cin >> s >> f, --s, --f;
//     for (ll i = 0, u, v, d; i < m; ++i) {
//         cin >> u >> v >> d, --u, --v;
//         g[u].emplace_back(v, d);
//         g[v].emplace_back(u, d);
//     }
//     djktstra(dist1, s);
//     djktstra(dist2, f);
//     for (ll i = 0; i < n; ++i) cnt_from_1[i] = -1;
//     calc_cnt(cnt_from_1, dist1, s, f);
//     for (ll i = 0; i < n; ++i) cnt_from_2[i] = -1;
//     calc_cnt(cnt_from_2, dist2, f, s);
//     ll ans = 1ll * cnt_from_1[f] * cnt_from_2[s] % mod;
//     for (ll v = 0; v < n; ++v) {
//         if (dist1[v] == dist2[v]) {
//             ans = (ans - (1ll * cnt_from_1[v] * cnt_from_2[v] % mod) + mod) % mod;
//         }
//         for (auto [u,w]: g[v]) {
//             if (!cnt_from_1[v] || !cnt_from_1[u] || dist1[v] + w != dist1[u]) continue;
//             ll mll = std::max(dist1[v], dist2[u]), maxt = std::min(dist1[u], dist2[v]);
//             if (mll >= maxt) continue;
//             ans = (ans - (1ll * cnt_from_1[v] * cnt_from_2[u] % mod) + mod) % mod;
//         }
//     }
//     cout << ans << "\n";
// }
//
// int  main() {
//     ios::sync_with_stdio(false), cin.tie(nullptr);
// #ifdef LOCAL
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
//     solve();
//     return 0;
// }
