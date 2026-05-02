#include <iostream>
#include <vector>
#include <set>

using namespace std;

constexpr int maxn = 2e6 + 10;
int n, d, t;
int arr[maxn];
vector<int> g[maxn];
int p[maxn];
bool used[maxn];
bool not_need[maxn];
int depth[maxn];
int max_depth_child[maxn];
int ans = 0;

void dfs(int v) {
    used[v] = true;
    depth[v] = 1;
    max_depth_child[v] = -1;
    for (auto u: g[v]) {
        dfs(u);
        if (depth[u] + 1 > depth[v]) {
            depth[v] = depth[u] + 1;
            max_depth_child[v] = u;
        }
    }
}

set<pair<int, int> > trees;

void dfs2(int v) {
    ++ans;
    for (auto u: g[v]) if (u != max_depth_child[v]) trees.emplace(depth[u], u);
    if (max_depth_child[v] != -1) dfs2(max_depth_child[v]);
}

void solve() {
    cin >> n >> d >> t;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    for (int alarm_time = arr[0], i = 0; i < n; ++i) {
        alarm_time = std::min(alarm_time, arr[i]);
        if (alarm_time > t) not_need[i] = true, ++ans;
        ++alarm_time;
    }
    for (int i = 0; i < n; ++i) p[i] = -1;
    vector<int> st;
    for (int i = n - 1; i >= 0; --i) {
        if (not_need[i]) continue;
        while (!st.empty() && arr[i] + st.back() - i <= t) st.pop_back();
        if (arr[i] <= t) continue;
        if (!st.empty()) g[st.back()].push_back(i), p[i] = st.back();
        st.push_back(i);
    }
    for (int i = n - 1; i >= 0; --i) {
        if (not_need[i] || arr[i] <= t || used[i]) continue;
        dfs(i);
        trees.emplace(depth[i], i);
    }
    while (d && !trees.empty()) {
        auto [cd, v] = *prev(trees.end());
        trees.erase(prev(trees.end()));
        dfs2(v);
        --d;
    }
    cout << n - ans << "\n";
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
