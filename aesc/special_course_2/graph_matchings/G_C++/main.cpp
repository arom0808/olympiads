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
    cin >> n;
    vector<int32_t> boys(n);
    for (auto &boy: boys) cin >> boy;
    cin >> m;
    vector<int32_t> girls(m);
    for (auto &girl: girls) cin >> girl;
    vector<set<int32_t>> g(n);
    for (int32_t i = 0; i < n; ++i)
        for (int32_t j = 0; j < m; ++j)
            if (std::abs(boys[i] - girls[j]) <= 1)
                g[i].insert(j);
    vector<int32_t> rm(m, -1), used(n, -1);
    int32_t timer = 0, ans = 0;
    for (int32_t v = 0; v < n; ++v) {
        if (dfs(g, rm, used, timer, v)) {
            ++ans;
            ++timer;
        }
    }
    cout << ans;
    return 0;
}