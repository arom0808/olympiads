#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 2e5;

vector<int> g[maxn], tg[maxn];
int comp[maxn];
vector<int> topsort;
int used[maxn];
int timer = 1;

void dfs_topsort(int v) {
    used[v] = timer;
    for (auto u: g[v]) if (used[u] != timer) dfs_topsort(u);
    topsort.push_back(v);
}

void dfs_set_comp(int v, int cid) {
    used[v] = timer;
    comp[v] = cid;
    for (auto u: tg[v]) if (used[u] != timer) dfs_set_comp(u, cid);
}

bool solve() {
    int n, m;
    cin >> n >> m;
    if (cin.eof()) return false;
    for (int i = 0; i < n; ++i)
        g[i * 2].clear(), g[i * 2 + 1].clear(), tg[i * 2].clear(), tg[i * 2 + 1].clear(),
                comp[i * 2] = -1, comp[i * 2 + 1] = -1;
    for (int i = 0, i1, i2, e1, e2; i < m; ++i) {
        cin >> i1 >> e1 >> i2 >> e2;
        i1 = i1 * 2 + e1, i2 = i2 * 2 + e2;
        g[i1 ^ 1].push_back(i2), g[i2 ^ 1].push_back(i1);
        tg[i2].push_back(i1 ^ 1), tg[i1].push_back(i2 ^ 1);
    }
    topsort.clear();
    ++timer;
    for (int v = 0; v < n * 2; ++v) if (used[v] != timer) dfs_topsort(v);
    reverse(topsort.begin(),topsort.end());
    ++timer;
    int cid = 0;
    for (auto v: topsort) if (used[v] != timer) dfs_set_comp(v, cid++);
    for (int i = 0; i < n; ++i) {
        if (comp[i * 2] > comp[i * 2 + 1]) cout << "0";
        else cout << "1";
    }
    cout << "\n";
    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    while (solve()) {
    }
    return 0;
}
