#include <iostream>
#include <vector>

void
dfs1(const std::vector<std::vector<std::uint32_t>> &g, std::vector<bool> &visited, std::vector<std::uint32_t> &topsort,
     std::uint32_t &time, std::uint32_t v) {
    if (visited[v]) return;
    visited[v] = true;
    for (auto u: g[v]) dfs1(g, visited, topsort, time, u);
    topsort[v] = time++;
}

void
dfs2(const std::vector<std::vector<std::uint32_t>> &g, std::vector<bool> &visited, std::vector<std::uint32_t> &comps,
     std::uint32_t comp, std::uint32_t v) {
    if (visited[v]) return;
    visited[v] = true;
    comps[v] = comp;
    for (auto u: g[v]) dfs2(g, visited, comps, comp, u);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::uint32_t>> g(n), rg(n);
    for (std::int32_t i = 0, v, u; i < m; ++i) {
        std::cin >> v >> u;
        g[v - 1].emplace_back(u - 1);
        rg[u - 1].emplace_back(v - 1);
    }
    std::vector<bool> visited(n, false);
    std::vector<std::uint32_t> topsort(n), order(n), comps(n);
    std::uint32_t max_time = 0;
    for (std::uint32_t i = 0; i < n; ++i) if (!visited[i]) dfs1(g, visited, topsort, max_time, i);
    for (std::uint32_t i = 0; i < n; ++i) order[n - 1 - topsort[i]] = i;
    std::uint32_t max_comp = 0;
    std::fill(visited.begin(), visited.end(), false);
    for (std::uint32_t i = 0; i < n; ++i) if (!visited[order[i]]) dfs2(rg, visited, comps, ++max_comp, order[i]);
    std::cout << max_comp << "\n";
    for (auto c: comps) std::cout << c << " ";
    return 0;
}
