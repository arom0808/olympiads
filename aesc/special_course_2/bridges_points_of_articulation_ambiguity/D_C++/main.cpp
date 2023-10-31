#include <iostream>
#include <vector>
#include <set>

const std::uint32_t inf = 1e8;

struct Edge {
    std::uint32_t id, u;

    bool operator<(const Edge &other) const {
        if (u != other.u) return u < other.u;
        return id < other.id;
    }

    Edge(std::uint32_t id, std::uint32_t u) : id(id), u(u) {}
};

void jointDFS(const std::vector<std::set<Edge>> &g, std::vector<bool> &visited,
              std::vector<std::uint32_t> &tin, std::vector<std::uint32_t> &up, std::vector<bool> &cutpoints,
              std::uint32_t &time, std::uint32_t v, std::uint32_t p = inf) {
    ++time;
    tin[v] = up[v] = time;
    visited[v] = true;
    std::uint32_t count = 0;
    for (auto [edge_id, u]: g[v]) {
        if (u == p) continue;
        if (visited[u]) up[v] = std::min(up[v], tin[u]);
        else {
            jointDFS(g, visited, tin, up, cutpoints, time, u, v);
            ++count;
            up[v] = std::min(up[v], up[u]);
            if (p != inf && up[u] >= tin[v]) cutpoints[v] = true;
        }
    }
    if (p == inf && count >= 2) cutpoints[v] = true;
}

void colorDFS(const std::vector<std::set<Edge>> &g, std::vector<bool> &visited,
              const std::vector<bool> &cutpoints, std::vector<std::uint32_t> &colors,
              std::uint32_t c, std::uint32_t v, std::uint32_t p = inf) {
    if (visited[v] || cutpoints[v]) return;
    visited[v] = true;
    for (auto [edge_id, u]: g[v]) {
        colors[edge_id] = c;
        colorDFS(g, visited, cutpoints, colors, c, u);
    }
}

void color_edge(const std::vector<std::set<Edge>> &g, const std::vector<std::pair<std::uint32_t, std::uint32_t>> &edges,
                std::vector<bool> &visited, const std::vector<bool> &cutpoints, std::vector<std::uint32_t> &colors,
                std::uint32_t c, std::uint32_t edge_id) {
    colors[edge_id] = c;
    colorDFS(g, visited, cutpoints, colors, c, edges[edge_id].first);
    colorDFS(g, visited, cutpoints, colors, c, edges[edge_id].second);
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::set<Edge>> g(n);
    std::vector<std::pair<std::uint32_t, std::uint32_t>> edges(m);
    for (std::uint32_t i = 0, b, c; i < m; ++i) {
        std::cin >> b >> c;
        g[b - 1].emplace(i, c - 1);
        g[c - 1].emplace(i, b - 1);
        edges[i] = {b - 1, c - 1};
    }
    std::vector<std::uint32_t> tin(n), up(n), colors(m, inf);
    std::vector<bool> cutpoints(n, false), visited(n, false);
    std::uint32_t time = 0;
    for (std::uint32_t i = 0; i < n; ++i)
        if (!visited[i])
            jointDFS(g, visited, tin, up, cutpoints, time, i);
    std::fill(visited.begin(), visited.end(), false);
    std::uint32_t max_color = 0;
    for (std::uint32_t i = 0; i < m; ++i)
        if (colors[i] == inf)
            color_edge(g, edges, visited, cutpoints, colors, ++max_color, i);
    std::vector<std::uint32_t> czs(m + 1, 0);
    max_color = 0;
    for (std::uint32_t i = 0; i < m; ++i) if (!czs[colors[i]]) czs[colors[i]] = ++max_color;
    std::cout << max_color << "\n";
    for (auto c: colors) std::cout << czs[c] << " ";
    return 0;
}