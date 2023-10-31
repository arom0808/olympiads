#include <iostream>
#include <vector>
#include <algorithm>

const std::uint32_t inf = 1e8;

struct Edge {
    std::uint32_t id, u;
    bool multiple = false;

    Edge(std::uint32_t id, std::uint32_t u) : id(id), u(u) {}

    bool operator<(const Edge &other) const {
        if (u != other.u) return u < other.u;
        return id < other.id;
    }
};

struct TreeEdge {
    std::uint32_t u;
    bool bridge;

    explicit TreeEdge(std::uint32_t u, bool bridge = false) : u(u), bridge(bridge) {}

    bool operator<(const TreeEdge &other) const { return u < other.u; }
};

void bridgeDFS(const std::vector<std::vector<Edge>> &g, std::vector<bool> &visited,
               std::vector<std::uint32_t> &h, std::vector<std::uint32_t> &d,
               std::vector<std::vector<TreeEdge>> &tree_g,
               std::uint32_t v, std::uint32_t p = inf, std::uint32_t dep = 0) {
    if (visited[v]) return;
    visited[v] = true;
    h[v] = d[v] = dep;
    for (const auto &[edge_id, u, multiple]: g[v]) {
        if (u == p) continue;
        if (visited[u]) d[v] = std::min(d[v], h[u]);
        else {
            bridgeDFS(g, visited, h, d, tree_g, u, v, dep + 1);
            d[v] = std::min(d[v], d[u]);
            tree_g[v].emplace_back(u, h[v] < d[u] && !multiple);
        }
    }
}

void
colorDFS(const std::vector<std::vector<TreeEdge>> &tree_g, std::vector<bool> &visited,
         std::vector<std::uint32_t> &colors, std::uint32_t this_color, std::uint32_t &last_used_color,
         std::uint32_t v) {
    visited[v] = true;
    colors[v] = this_color;
    for (auto [u, bridge]: tree_g[v]) {
        if (bridge) colorDFS(tree_g, visited, colors, ++last_used_color, last_used_color, u);
        else colorDFS(tree_g, visited, colors, this_color, last_used_color, u);
    }
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<Edge>> g(n);
    for (std::uint32_t i = 0, b, c; i < m; ++i) {
        std::cin >> b >> c;
        g[b - 1].emplace_back(i, c - 1);
        g[c - 1].emplace_back(i, b - 1);
    }
    for (auto &edges: g) {
        std::sort(edges.begin(), edges.end());
        for (std::uint32_t i = 1; i < edges.size(); ++i)
            if (edges[i].u == edges[i - 1].u)
                edges[i].multiple = edges[i - 1].multiple = true;
    }
    std::vector<std::uint32_t> h(n), d(n), colors(n);
    std::vector<std::vector<TreeEdge>> tree_g(n);
    std::vector<bool> visited(n, false);
    for (std::uint32_t i = 0; i < n; ++i) if (!visited[i]) bridgeDFS(g, visited, h, d, tree_g, i);
    std::uint32_t last_used_color = 0;
    std::fill(visited.begin(), visited.end(), false);
    for (std::uint32_t i = 0; i < n; ++i)
        if (!visited[i])
            colorDFS(tree_g, visited, colors, ++last_used_color, last_used_color, i);
    std::vector<std::uint32_t> color_for_sort(last_used_color + 1, inf);
    last_used_color = 0;
    for (std::uint32_t i = 0; i < n; ++i)
        if (color_for_sort[colors[i]] == inf)
            color_for_sort[colors[i]] = ++last_used_color;
    std::cout << last_used_color << "\n";
    for (auto c: colors) std::cout << color_for_sort[c] << " ";
    return 0;
}