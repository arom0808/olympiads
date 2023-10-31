#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

const std::uint32_t inf = 1e5;

void DFS(const std::vector<std::unordered_set<std::uint32_t>> &g, std::unordered_set<std::uint32_t> &unused,
         std::vector<std::uint32_t> &h, std::vector<std::uint32_t> &d, std::set<std::uint32_t> &result,
         std::uint32_t v, std::uint32_t p = inf, std::uint32_t dep = 0) {
    unused.erase(v);
    h[v] = d[v] = dep;
    std::uint32_t childs_cnt = 0;
    for (auto u: g[v]) {
        if (u == p) continue;
        if (unused.find(u) == unused.end()) d[v] = std::min(d[v], h[u]);
        else {
            ++childs_cnt;
            DFS(g, unused, h, d, result, u, v, dep + 1);
            d[v] = std::min(d[v], d[u]);
            if (h[v] <= d[u] && p != inf) result.insert(v);
        }
    }
    if (p == inf && childs_cnt > 1) result.insert(v);
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::unordered_set<std::uint32_t>> g(n);
    for (std::uint64_t i = 0, b, c; i < m; ++i) {
        std::cin >> b >> c;
        g[b - 1].emplace(c - 1);
        g[c - 1].insert(b - 1);
    }
    std::vector<std::uint32_t> h(n), d(n);
    std::unordered_set<std::uint32_t> unused;
    std::set<std::uint32_t> result;
    for (std::uint32_t i = 0; i < n; ++i) unused.insert(i);
    while (!unused.empty()) DFS(g, unused, h, d, result, *unused.begin());
    std::cout << result.size() << "\n";
    for (auto r: result) std::cout << r + 1 << " ";
    return 0;
}
