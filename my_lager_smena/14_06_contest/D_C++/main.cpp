#include <iostream>
#include <vector>
#include <set>

bool is_allowed(const std::vector<std::set<std::uint32_t>> &allowed_after, const std::set<std::uint32_t> &visited,
                std::uint32_t cur_ver) {
    for (auto to_allow: allowed_after[cur_ver]) if (visited.find(to_allow) == visited.end()) return false;
    return true;
}

void DFS(const std::vector<std::set<std::uint32_t>> &ways, const std::vector<std::set<std::uint32_t>> &allowed_after,
         std::set<std::uint32_t> &visited, std::uint32_t cur_ver, std::uint32_t &res) {
    if (visited.find(cur_ver) != visited.end()) return;
    if (!is_allowed(allowed_after, visited, cur_ver)) return;
    visited.emplace(cur_ver);
    if (visited.size() == ways.size()) ++res;
    else for (auto way_to: ways[cur_ver]) DFS(ways, allowed_after, visited, way_to, res);
    visited.erase(cur_ver);
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::set<std::uint32_t>> ways(n);
    for (std::uint32_t i = 0, t_1, t_2; i < n - 1; ++i) {
        std::cin >> t_1 >> t_2;
        ways[t_1 - 1].emplace(t_2 - 1);
        ways[t_2 - 1].emplace(t_1 - 1);
    }
    std::vector<std::set<std::uint32_t>> allowed_after(n);
    for (std::uint32_t i = 0, a, b; i < m; ++i) {
        std::cin >> a >> b;
        allowed_after[b - 1].emplace(a - 1);
    }
    std::set<std::uint32_t> visited;
    std::uint32_t res = 0;
    DFS(ways, allowed_after, visited, 0, res);
    std::cout << res;
    return 0;
}
