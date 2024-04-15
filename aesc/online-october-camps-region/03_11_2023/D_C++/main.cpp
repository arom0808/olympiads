#include <iostream>
#include <vector>
#include <set>


std::uint32_t
init_node(std::vector<std::vector<std::pair<std::uint32_t, std::uint32_t>>> &g,
          std::uint32_t left, std::uint32_t right) {
    if (left + 1 == right) return left;
    g.emplace_back();
    if (left >= right) return g.size() - 1;
    auto son1 = init_node(g, left, (left + right) / 2), son2 = init_node(g, (left + right) / 2, right);
    g.back().emplace_back(son1, left + 1 == (left + right) / 2);
    g.back().emplace_back(son2, (left + right) / 2 + 1 == right);
    return g.size() - 1;
}

void upd_main_node(std::vector<std::vector<std::pair<std::uint32_t, std::uint32_t>>> &g,
                   std::uint32_t target, std::uint32_t node_id,
                   std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
                   std::uint32_t req_right) {
    if (node_left >= node_right) return;
    if (req_right <= node_left || req_left >= node_right) return;
    if (req_left <= node_left && req_right >= node_right) {
        g[target].emplace_back(node_id, node_left + 1 == node_right);
        return;
    }
    upd_main_node(g, target, g[node_id].front().first, node_left, (node_left + node_right) / 2, req_left, req_right);
    upd_main_node(g, target, g[node_id].back().first, (node_left + node_right) / 2, node_right, req_left, req_right);
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::vector<std::pair<std::uint32_t, std::uint32_t>>> g(n);
    g.reserve(2 * n);
    init_node(g, 0, n);
    for (std::uint32_t i = 0, l, r; i < n; ++i) {
        std::cin >> l >> r;
        upd_main_node(g, i, n, 0, n, l - 1, r);
    }
    std::vector<std::uint32_t> fd(n, 1e9), ld(n, 1e9), last_fd(n, 1e9), last_ld(n, 1e9);
    std::set<std::uint32_t> que;
    return 0;
}
