#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int32_t maxn = 3e5;
int32_t n, m;

vector<int32_t> g[maxn];
int32_t order[maxn];
bool used[maxn];

bool cmp(int32_t a, int32_t b) {
    if (g[a].size() != g[b].size()) return g[a].size() < g[b].size();
    return a < b;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    for (int32_t i = 0, a, b; i < m; ++i) {
        cin >> a >> b, --a, --b;
        g[a].push_back(b), g[b].push_back(a);
    }
    iota(begin(order), next(begin(order), n), 0);
    sort(begin(order), next(begin(order), n), &cmp);
    for (auto &row: g) sort(row.begin(), row.end(), &cmp);
    uint64_t ans = 0;
    for (int32_t i = 0; i < n; ++i) {
        auto v = order[i];
        for (auto u: g[v]) used[u] = true;
        for (auto u: g[v]) {
            if (!cmp(u, v)) break;
            for (auto w: g[u]) {
                if (!cmp(w, u)) break;
                if (used[w]) ++ans;
            }
        }
        for (auto u: g[v]) used[u] = false;
    }
    cout << ans;
    return 0;
}