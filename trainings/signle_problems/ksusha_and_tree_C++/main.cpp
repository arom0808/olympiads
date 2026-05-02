#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int32_t maxn = 1e5, inf = 1e9, c = 320;
const int32_t twice_maxn = 2e5, twice_maxlogn = 18;

int32_t dist[maxn], fep[maxn];
vector<int32_t> euler;
vector<int32_t> g[maxn];
vector<int32_t> cb, nb;
int32_t n, m;

namespace SparseTable {
    int32_t tree[twice_maxlogn][twice_maxn];

    void init() {
        for (int32_t i = 0; i < euler.size(); ++i) tree[0][i] = euler[i];
        for (int32_t i = euler.size(); i < twice_maxn; ++i) tree[0][i] = inf;
        for (uint32_t k = 1; k < twice_maxlogn; ++k)
            for (uint32_t i = 0; i + (1 << (k - 1)) < euler.size(); ++i)
                tree[k][i] = std::min(tree[k - 1][i], tree[k - 1][i + (1 << (k - 1))]);
    }

    int32_t min(int32_t l, int32_t r) {
        int32_t k = __lg(r - l);
        return std::min(tree[k][l], tree[k][r - (1 << k)]);
    }
}

void init() {
    for (auto &el: dist) el = inf;
}

int32_t path_len(int32_t v, int32_t u) {
    if (fep[v] > fep[u]) swap(v, u);
    return euler[fep[v]] + euler[fep[u]] - 2 * SparseTable::min(fep[v], fep[u] + 1);
}

void euler_dfs(int32_t v, int32_t depth = 0, int32_t p = -1) {
    fep[v] = euler.size();
    euler.push_back(depth);
    for (auto u: g[v]) {
        if (u == p) continue;
        euler_dfs(u, depth + 1, v);
        euler.push_back(depth);
    }
}

void bfs() {
    for (auto &el: dist) el = inf;
    deque<int32_t> que(cb.begin(), cb.end());
    for (auto el: cb) dist[el] = 0;
    while (!que.empty()) {
        auto v = que.front();
        que.pop_front();
        for (auto u: g[v]) {
            if (dist[v] + 1 >= dist[u]) continue;
            dist[u] = dist[v] + 1;
            que.push_back(u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    init();
    cin >> n >> m;
    for (int32_t i = 0, a, b; i + 1 < n; ++i) {
        cin >> a >> b, --a, --b;
        g[a].push_back(b), g[b].push_back(a);
    }
    euler_dfs(0);
    SparseTable::init();
    nb.push_back(0);
    for (int32_t i = 0, t, v; i < m; ++i) {
        if (i % c == 0) {
            cb.insert(cb.end(), nb.begin(), nb.end());
            nb.clear();
            bfs();
        }
        cin >> t >> v, --v;
        if (t == 1) nb.push_back(v);
        else {
            int32_t res = dist[v];
            for (auto u: nb) res = std::min(res, path_len(v, u));
            cout << res << "\n";
        }
    }
    return 0;
}
