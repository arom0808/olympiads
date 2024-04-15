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
    int32_t n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<bool>> table(n, vector<bool>(m));
    int32_t free_cnt = 0;
    char c;
    for (auto &row: table) {
        for (_Bit_reference v: row) {
            cin >> c;
            v = c == '.';
            if (!v) ++free_cnt;
        }
    }
    if (2 * b <= a) {
        cout << free_cnt * b;
        return 0;
    }
    vector<set<int32_t>> g(n * m);
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < m; ++j) {
            if (i + 1 < n && !table[i][j] && !table[i + 1][j]) {
                if ((i + j) % 2 == 0) g[i * m + j].insert((i + 1) * m + j);
                else g[(i + 1) * m + j].insert(i * m + j);
            }
            if (j + 1 < m && !table[i][j] && !table[i][j + 1]) {
                if ((i + j) % 2 == 0) g[i * m + j].insert(i * m + j + 1);
                else g[i * m + j + 1].insert(i * m + j);
            }
        }
    }
    vector<int32_t> rm(n * m, -1), used(n * m, -1);
    int32_t timer = 0, ans = 0;
    for (int32_t v = 0; v < n * m; ++v) {
        if (dfs(g, rm, used, timer, v)) {
            ++ans;
            ++timer;
        }
    }
    cout << ans * a + (free_cnt - ans * 2) * b;
    return 0;
}