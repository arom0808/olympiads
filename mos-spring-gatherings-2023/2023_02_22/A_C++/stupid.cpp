#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 1e6;
vector<int> low_borders[maxn], high_borders[maxn];
vector<int> g[maxn];
int n, k;
int ans;

void dfs1(int v, int dist, vector<int> low_cur_box, vector<int> high_cur_box, int p = -1) {
    for (int i = 0; i < k; ++i) low_cur_box[i] = std::max(low_cur_box[i], low_borders[v][i]);
    for (int i = 0; i < k; ++i) high_cur_box[i] = std::min(high_cur_box[i], high_borders[v][i]);
    for (int i = 0; i < k; ++i) {
        if (low_cur_box[i] > high_cur_box[i]) {
            ans = std::min(ans, dist);
            return;
        }
    }
    for (auto u: g[v]) if (u != p) dfs1(u, dist + 1, low_cur_box, high_cur_box, v);
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) low_borders[i].resize(k), high_borders[i].resize(k);
    for (int i = 0; i < n; ++i) {
        for (auto &c: low_borders[i]) cin >> c;
        for (auto &c: high_borders[i]) cin >> c;
        for (int j = 0; j < k; ++j)
            if (low_borders[i][j] > high_borders[i][j])
                swap(low_borders[i][j], high_borders[i][j]);
    }
    for (int i = 0, u, v; i + 1 < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    vector<int> lcb(k, -1e9 - 1), hcb(k, 1e9 + 1);
    ans = n;
    for (int v = 0; v < n; ++v) dfs1(v, 0, lcb, hcb);
    cout << ((ans == n) ? (-1) : ans) << "\n";
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


// #include <iostream>
// #include <vector>
// #include <algorithm>
//
// using namespace std;
//
// constexpr int maxn = 1e6;
// vector<int> low_borders[maxn], high_borders[maxn];
// vector<int> g[maxn];
// int n, k;
//
// struct Sq {
//     vector<pair<int, int> > vec;
//
//     void insert(int h, int val) {
//         vec.emplace_back(h, val);
//     }
//
//     void set_min_eq(int val) {
//         for (auto &[h,v]: vec) v = std::min(v, val);
//     }
//
//     void set_max_eq(int val) {
//         for (auto &[h,v]: vec) v = std::max(v, val);
//     }
//
//     void increase_h() {
//         for (auto &[h,v]: vec) ++h;
//     }
//
//     int get_min_h_greater(int val) {
//         int ans = -1;
//         for (auto [h,v]: vec) if (v > val && (ans == -1 || h < ans)) ans = h;
//         return ans;
//     }
//
//     int get_min_h_less(int val) {
//         int ans = -1;
//         for (auto [h,v]: vec) if (v < val && (ans == -1 || h < ans)) ans = h;
//         return ans;
//     }
// };
//
// vector<Sq> dp_low[maxn];
// vector<Sq> dp_high[maxn];
// int sz[maxn];
//
// int dfs1(int v, int p = -1) {
//     sz[v] = 1;
//     if (p != -1) g[v].erase(find(g[v].begin(), g[v].end(), p));
//     for (auto u: g[v]) sz[v] += dfs1(u, v);
//     for (auto &u: g[v]) if (sz[u] > sz[g[v][0]]) swap(u, g[v][0]);
//     return sz[v];
// }
//
// int ans = n;
//
// void dfs2(int v) {
//     if (g[v].empty()) {
//         for (int i = 0; i < k; ++i) dp_low[v][i].insert(0, low_borders[v][i]);
//         for (int i = 0; i < k; ++i) dp_high[v][i].insert(0, high_borders[v][i]);
//         return;
//     }
//     for (auto u: g[v]) dfs2(u);
//     dp_low[v].swap(dp_low[g[v][0]]);
//     dp_high[v].swap(dp_high[g[v][0]]);
//     for (int i = 0; i < k; ++i) dp_low[v][i].increase_h();
//     for (int i = 0; i < k; ++i) dp_high[v][i].increase_h();
//     for (int i = 0; i < k; ++i) {
//         int c1 = dp_low[v][i].get_min_h_greater(high_borders[v][i]);
//         int c2 = dp_high[v][i].get_min_h_less(low_borders[v][i]);
//         if (c1 != -1) ans = std::min(ans, c1);
//         if (c2 != -1) ans = std::min(ans, c2);
//     }
//     for (int i = 0; i < k; ++i) dp_low[v][i].insert(0, low_borders[v][i]);
//     for (int i = 0; i < k; ++i) dp_high[v][i].insert(0, high_borders[v][i]);
//     for (int i = 0; i < k; ++i) dp_low[v][i].set_max_eq(low_borders[v][i]);
//     for (int i = 0; i < k; ++i) dp_high[v][i].set_min_eq(high_borders[v][i]);
//     for (int _ = 1; _ < g[v].size(); ++_) {
//         int u = g[v][_];
//         for (int i = 0; i < k; ++i) {
//             for (auto [h, val]: dp_low[u][i].vec) {
//                 int c = dp_high[v][i].get_min_h_less(val);
//                 if (c != -1) ans = std::min(ans, c + h);
//             }
//             for (auto [h,val]: dp_high[u][i].vec) {
//                 int c = dp_low[v][i].get_min_h_greater(val);
//                 if (c != -1) ans = std::min(ans, c + h);
//             }
//             dp_low[u][i].set_max_eq(low_borders[v][i]);
//             dp_high[u][i].set_min_eq(high_borders[v][i]);
//             for (auto [h,val]: dp_low[v][i].vec) dp_low[v][i].insert(h, val);
//             for (auto [h,val]: dp_high[v][i].vec) dp_high[v][i].insert(h, val);
//         }
//     }
// }
//
// void solve() {
//     cin >> n >> k;
//     for (int i = 0; i < n; ++i) low_borders[i].resize(k), high_borders[i].resize(k);
//     for (int i = 0; i < n; ++i) {
//         for (auto &c: low_borders[i]) cin >> c;
//         for (auto &c: high_borders[i]) cin >> c;
//         for (int j = 0; j < k; ++j)
//             if (low_borders[i][j] > high_borders[i][j])
//                 swap(low_borders[i][j], high_borders[i][j]);
//     }
//     for (int i = 0, u, v; i + 1 < n; ++i) {
//         cin >> u >> v, --u, --v;
//         g[u].push_back(v), g[v].push_back(u);
//     }
//     for (int i = 0; i < n; ++i) dp_low[i].resize(k), dp_high[i].resize(k);
//     ans = n;
//     dfs1(0);
//     dfs2(0);
//     cout << (ans == n ? (-1) : ans) << "\n";
// }
//
// int main() {
//     ios::sync_with_stdio(false), cin.tie(nullptr);
// #ifdef LOCAL
//     freopen("input.txt", "r",stdin);
//     freopen("output.txt", "w",stdout);
// #elifdef TEST
//     freopen("input.txt", "r",stdin);
// #endif
//     solve();
//     return 0;
// }
