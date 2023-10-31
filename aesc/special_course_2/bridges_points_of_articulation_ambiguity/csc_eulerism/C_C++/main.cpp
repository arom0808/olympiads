#include <iostream>
#include <vector>

const std::uint32_t inf = 2e9;
const std::uint64_t mod = 1e9 + 7;

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
    std::cin >> n;
    std::vector<std::uint32_t> costs(n);
    for (auto &cost: costs) std::cin >> cost;
    std::cin >> m;
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
    std::uint32_t comp_cnt = 0;
    std::fill(visited.begin(), visited.end(), false);
    for (std::uint32_t i = 0; i < n; ++i) if (!visited[order[i]]) dfs2(rg, visited, comps, comp_cnt++, order[i]);
    std::vector<std::pair<std::uint32_t, std::uint32_t>>
            min_cost_cnt(comp_cnt, std::pair<std::uint32_t, std::uint32_t>{inf, 0});
    for (std::uint32_t i = 0; i < n; ++i) {
        if (costs[i] < min_cost_cnt[comps[i]].first) min_cost_cnt[comps[i]] = {costs[i], 1};
        else if (costs[i] == min_cost_cnt[comps[i]].first) ++min_cost_cnt[comps[i]].second;
    }
    std::uint64_t res = 0, cnt_res = 1;
    for (auto [cost, cnt]: min_cost_cnt) {
        res += cost;
        cnt_res = (cnt_res * cnt) % mod;
    }
    std::cout << res << " " << cnt_res;
    return 0;
}
