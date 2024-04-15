#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool dfs(const vector<set<int32_t>> &g, vector<int32_t> &rm, vector<int32_t> &used, int32_t timer, int32_t v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto u: g[v]) {
        if (rm[u] == -1) {
            rm[u] = v;
            return true;
        }
    }
    for (auto u: g[v]) {
        if (dfs(g, rm, used, timer, rm[u])) {
            rm[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int32_t n, m;
    cin >> n >> m;
    bool reversed = n > m;
    if (reversed) swap(n, m);
    vector<set<int32_t>> g(n);
    for (int32_t i = 0, neight; i < (reversed ? m : n); ++i) {
        for (cin >> neight; neight; cin >> neight) {
            if (reversed) g[neight - 1].insert(i);
            else g[i].insert(neight - 1);
        }
    }
    vector<int32_t> rm(m, -1), used(n, -1);
    int32_t timer = 0, ans = 0;
    for (int32_t v = 0; v < n; ++v) {
        if (dfs(g, rm, used, timer, v)) {
            ++ans;
            ++timer;
        }
    }
    cout << ans << "\n";
    for (int32_t u = 0; u < m; ++u)
        if (rm[u] >= 0)
            cout << (reversed ? u : rm[u]) + 1 << " " << (reversed ? rm[u] : u) + 1 << "\n";
    return 0;
}
