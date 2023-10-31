#include <iostream>
#include <vector>

const std::int32_t inf = 1e9;

struct Edge {
    std::uint32_t u;
    std::int32_t w;

    Edge(std::uint32_t u, std::int32_t w) : u(u), w(w) {}
};

void dfs(const std::vector<std::vector<Edge>> &g, std::vector<bool> &visited, std::vector<std::uint32_t> &topsort,
         std::uint32_t &time, std::uint32_t v) {
    if (visited[v]) return;
    visited[v] = true;
    for (const auto &[u, w]: g[v]) dfs(g, visited, topsort, time, u);
    topsort[v] = time++;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::uint32_t n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s;
    --t;
    std::vector<std::vector<Edge>> g(n);
    for (std::int32_t i = 0, b, e, w; i < m; ++i) {
        std::cin >> b >> e >> w;
        g[b - 1].emplace_back(e - 1, w);
    }
    std::vector<bool> visited(n, false);
    std::vector<std::uint32_t> topsort(n), order(n);
    std::uint32_t max_time = 0;
    for (std::uint32_t i = 0; i < n; ++i) if (!visited[i]) dfs(g, visited, topsort, max_time, i);
    for (std::uint32_t i = 0; i < n; ++i) order[n - 1 - topsort[i]] = i;
    std::vector<std::int32_t> d(n, inf);
    d[s] = 0;
    std::uint32_t s_i = n - 1 - topsort[s], t_i = n - 1 - topsort[t];
    for (std::uint32_t i = s_i; i < t_i; ++i)
        for (const auto &[u, w]: g[order[i]])
            if (d[order[i]] != inf && d[u] > d[order[i]] + w)
                d[u] = d[order[i]] + w;
    if (d[t] == inf) std::cout << "Unreachable";
    else std::cout << d[t];
    return 0;
}
