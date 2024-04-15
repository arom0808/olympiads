#include <iostream>
#include <vector>
#include <list>
#include <numeric>

using namespace std;

class DSU {
public:
    vector<int32_t> heights, sizes, agents;

    int32_t agent(int32_t v) {
        return (v == agents[v]) ? v : agents[v] = agent(agents[v]);
    }

    void unite(int32_t a, int32_t b) {
        a = agent(a), b = agent(b);
        if (a == b) return;
        if (heights[a] > heights[b]) swap(a, b);
        agents[b] = a;
        sizes[a] += sizes[b];
    }

    explicit DSU(const vector<int32_t> &_heights) : heights(_heights), sizes(_heights.size(), 1),
                                                    agents(_heights.size()) {
        iota(agents.begin(), agents.end(), 0);
    }
};

void dfs(const vector<list<int32_t>> &rg, vector<int32_t> &parents, vector<int32_t> &heights, int32_t v, int32_t p,
         int32_t h) {
    parents[v] = p;
    heights[v] = h;
    for (auto u: rg[v]) if (u != p) dfs(rg, parents, heights, u, v, h + 1);
}

int main() {
    int32_t n;
    cin >> n;
    vector<list<int32_t>> rg(n);
    for (int32_t i = 1, v, u; i < n; ++i) {
        cin >> v >> u;
        rg[v - 1].push_back(u - 1);
        rg[u - 1].push_back(v - 1);
    }
    vector<int32_t> parents(n), heights(n);
    dfs(rg, parents, heights, 0, -1, 0);
    DSU dsu(heights);
    int32_t m;
    cin >> m;
    for (int32_t i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        x = dsu.agent(x - 1);
        y = dsu.agent(y - 1);
        while (x != y) {
            if (heights[x] > heights[y]) swap(x, y);
            dsu.unite(y, parents[y]);
            y = dsu.agent(y);
        }
    }
    int32_t res = 0;
    for (int32_t i = 0; i < n; ++i) if (i == dsu.agent(i)) res += dsu.sizes[i] - 1;
    cout << n - 1 - res;
    return 0;
}
