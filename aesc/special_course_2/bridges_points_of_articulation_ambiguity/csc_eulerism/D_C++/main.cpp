#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>


bool
get_euler(const std::vector<std::uint32_t> &edges, std::vector<std::set<std::uint32_t>> &g,
          std::vector<std::uint32_t> &seq) {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> deleted_edges;
    seq.reserve(g.size());
    deleted_edges.reserve(edges.size());
    std::stack<std::uint32_t> st;
    st.push(0);
    while (!st.empty()) {
        auto v = st.top();
        if (g[v].empty()) {
            seq.push_back(v);
            st.pop();
        } else {
            auto edge_id = *g[v].begin();
            st.push(edges[edge_id] ^ v);
            g[v].erase(edge_id);
            g[edges[edge_id] ^ v].erase(edge_id);
            deleted_edges.emplace_back(v, edge_id);
        }
    }
    for (auto [v, edge_id]: deleted_edges) {
        g[v].emplace(edge_id);
        g[edges[edge_id] ^ v].emplace(edge_id);
    }
    return deleted_edges.size() == edges.size();
}

bool solute(std::vector<std::uint32_t> &edges, std::vector<std::set<std::uint32_t>> &g,
            const std::vector<std::uint32_t> &odd_points, std::vector<std::uint32_t> &seq) {
    if (odd_points.empty()) return get_euler(edges, g, seq);
    auto v = odd_points.front(), u = odd_points.back();
    edges.emplace_back(v ^ u);
    g[v].emplace(edges.size() - 1);
    g[u].emplace(edges.size() - 1);
    bool euler_ok = get_euler(edges, g, seq);
    g[v].erase(edges.size() - 1);
    g[u].erase(edges.size() - 1);
    edges.pop_back();
    if (!euler_ok) return false;
    std::uint32_t to_add_i;
    for (to_add_i = 0; to_add_i + 1 < seq.size() && !((seq[to_add_i] == v && seq[to_add_i + 1] == u) ||
                                                      (seq[to_add_i] == u && seq[to_add_i + 1] == v)); ++to_add_i);
    std::rotate(seq.begin(), std::next(seq.begin(), to_add_i + 1), seq.end());
    seq.erase(std::unique(seq.begin(), seq.end()), seq.end());
    return true;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> edges, odd_points;
    std::vector<std::set<std::uint32_t>> g(n);
    edges.reserve(100001);
    for (std::uint32_t i = 0, m, u, w; i < n; ++i) {
        std::cin >> m;
        if (m % 2 != 0) odd_points.push_back(i);
        for (std::uint32_t j = 0; j < m; ++j) {
            std::cin >> u >> w;
            if (i >= u) continue;
            edges.emplace_back(i ^ (u - 1));
            g[i].emplace(edges.size() - 1);
            g[u - 1].emplace(edges.size() - 1);
        }
    }
    std::vector<std::uint32_t> seq;
    bool ok = solute(edges, g, odd_points, seq);
    if (!ok) std::cout << "-1";
    else {
        std::cout << seq.size() - 1 << "\n";
        for (auto el: seq) std::cout << el + 1 << " ";
    }
    return 0;
}
