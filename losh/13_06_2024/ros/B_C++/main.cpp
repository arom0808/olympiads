#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

const int32_t maxn = 1e5;
vector<int32_t> g[maxn];

uint32_t seed = 1234124130;
mt19937 rng(seed);
int32_t used[maxn], depth[maxn], parent[maxn];
int32_t timer = 0;
bool result_found = false;
vector<int32_t> result;

void dfs(int32_t v, int32_t d = 0, int32_t p = -1) {
    if (used[v] == timer || result_found) return;
    used[v] = timer, depth[v] = d, parent[v] = p;
    for (auto u: g[v]) {
        if (u == p || result_found) continue;
        if (used[u] == timer) {
            if ((depth[v] - depth[u]) % 2 == 1) {
                result_found = true;
                result.push_back(v);
                do {
                    v = parent[v];
                    result.push_back(v);
                } while (v != u);
                return;
            }
        } else {
            dfs(u, d + 1, v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m;
    cin >> n >> m;
    for (int32_t i = 0, a, b; i < m; ++i) {
        cin >> a >> b, --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int32_t i = 0; i < 50 && !result_found; ++i) {
        for (int32_t j = 0; j < n; ++j) shuffle(g[j].begin(), g[j].end(), rng);
        ++timer;
        for (int32_t j = 0; j < n; ++j) if (used[j] != timer) dfs(j);
    }
    if (result_found) {
        cout << "YES\n";
        cout << result.size() << "\n";
        for (auto v: result) cout << v + 1 << " ";
        cout << "\n";
    } else cout << "NO\n";
}