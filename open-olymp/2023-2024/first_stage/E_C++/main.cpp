#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <algorithm>

using namespace std;

struct VertEdge {
    uint32_t to, color;
};

struct Edge {
    uint32_t v, u, color;
};

void dfs(const vector<vector<VertEdge>> &vert_edges, vector<bool> &visited, bool &cycled, uint32_t v, uint32_t p) {
    if (visited[v]) return;
    visited[v] = true;
    for (auto [to, color]: vert_edges[v]) {
        if (to == p) continue;
        if (!visited[to]) dfs(vert_edges, visited, cycled, to, v);
        else cycled = true;
    }
}

const uint32_t inf = numeric_limits<uint32_t>::max();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    vector<uint32_t> counts_by_color(k, 0);
    vector<Edge> edges(m);
    vector<list<VertEdge>> raw_vert_edges(n);
    for (uint32_t i = 0, v, u, c; i < m; ++i) {
        cin >> v >> u >> c;
        edges[i] = {v - 1, u - 1, c - 1};
        raw_vert_edges[v - 1].emplace_back(u - 1, c - 1);
        raw_vert_edges[u - 1].emplace_back(v - 1, c - 1);
        ++counts_by_color[c - 1];
    }
    vector<vector<VertEdge>> vert_edges(n);
    for (uint32_t i = 0; i < n; ++i) vert_edges[i].assign(raw_vert_edges[i].begin(), raw_vert_edges[i].end());
    raw_vert_edges.clear();

    vector<bool> visited(n, false);
    bool cycled = false;
    dfs(vert_edges, visited, cycled, 0, inf);
    bool connected = find(visited.begin(), visited.end(), false) == visited.end();

    uint32_t q;
    cin >> q;
    for (uint32_t i = 0, e, w; i < q; ++i) {
        cin >> e >> w;
        --counts_by_color[edges[e - 1].color];
        ++counts_by_color[edges[e - 1].color = w - 1];
        if (!connected || find(counts_by_color.begin(), counts_by_color.end(), 0) != counts_by_color.end())
            cout << "No\n";
        else {
            if (k <= 2) cout << "Yes\n";
            else if (k == 3) {
                if (n > 3 || !cycled) cout << "Yes\n";
                else cout << "No\n";
            }
        }
    }
    return 0;
}
