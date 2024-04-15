#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack>

class DSU {
private:
    std::vector<std::uint64_t> link, size, _rich;

    std::uint64_t find(std::uint64_t v) {
        while (link[v] != v) v = link[v];
        return v;
    }

public:
    void unite(std::uint64_t a, std::uint64_t b) {
        a = link[a] = find(a);
        b = link[b] = find(b);
        if (a == b) return;
        if (size[a] < size[b]) {
            link[a] = b;
            size[b] += size[a];
            _rich[b] += _rich[a];
        } else {
            link[b] = a;
            size[a] += size[b];
            _rich[a] += _rich[b];
        }
    }

    std::uint64_t &rich(std::uint64_t v) { return _rich[link[v] = find(v)]; }

    std::uint64_t get(std::uint64_t v) {
        return link[v] = find(v);
    }

    explicit DSU(std::uint64_t els_count) : DSU(els_count, std::vector<std::uint64_t>(els_count, 0)) {}

    explicit DSU(std::uint64_t els_count, std::vector<std::uint64_t> rich)
            : link(els_count), size(els_count, 1), _rich(std::move(rich)) {
        std::iota(link.begin(), link.end(), 0);
    }
};

struct Edge {
    std::uint64_t id, v, u, w;
};

struct OstEdge {
    std::uint64_t id, x, w;
};

void
dfs(const std::vector<OstEdge> &edges, const std::vector<std::vector<std::uint32_t>> &g, std::vector<bool> &visited,
    DSU &rdsu, std::stack<std::uint64_t> &st, std::vector<std::uint64_t> &seq, std::uint64_t v) {
    visited[v] = true;
    for (auto ei: g[v]) {
        auto [id, x, w] = edges[ei];
        if (visited[x ^ v]) continue;
        dfs(edges, g, visited, rdsu, st, seq, x ^ v);
        if (rdsu.rich(v) + rdsu.rich(x ^ v) >= w) {
            rdsu.unite(v, x ^ v);
            rdsu.rich(v) -= w;
            seq.push_back(id);
        } else st.push(id);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::uint64_t n, m, g;
    std::cin >> n >> m >> g;
    std::uint64_t rich_sum = 0;
    std::vector<std::uint64_t> rich(n);
    for (auto &c: rich) {
        std::cin >> c;
        rich_sum += c;
    }
    std::vector<Edge> edges(m);
    for (std::uint64_t i = 0; i < m; ++i) {
        auto &[id, v, u, w] = edges[i];
        id = i;
        std::cin >> v >> u >> w;
        --v;
        --u;
    }
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) { return a.w < b.w; });
    DSU dsu(n);
    std::vector<OstEdge> ost_edges;
    ost_edges.reserve(n - 1);
    std::vector<std::vector<std::uint32_t>> ost_g(n);
    std::uint64_t ost_edges_sum = 0;
    for (auto [id, v, u, w]: edges) {
        if (dsu.get(v) == dsu.get(u)) continue;
        dsu.unite(v, u);
        ost_edges.emplace_back(id, v ^ u, w);
        ost_edges_sum += w;
        ost_g[v].push_back(ost_edges.size() - 1);
        ost_g[u].push_back(ost_edges.size() - 1);
    }
    if (ost_edges.size() < n - 1 || ost_edges_sum > rich_sum) {
        std::cout << "-1";
        return 0;
    }
    std::vector<bool> visited(n, false);
    DSU rdsu(n, rich);
    std::stack<std::uint64_t> st;
    std::vector<std::uint64_t> seq;
    seq.reserve(n - 1);
    dfs(ost_edges, ost_g, visited, rdsu, st, seq, 0);
    std::cout << n - 1 << "\n";
    for (auto &s: seq) std::cout << s + 1 << "\n";
    for (; !st.empty(); st.pop()) std::cout << st.top() + 1 << "\n";
    return 0;
}
