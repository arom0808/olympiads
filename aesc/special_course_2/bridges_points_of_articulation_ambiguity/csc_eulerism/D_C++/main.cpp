#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

const std::uint64_t inf = 1e18;

struct Edge {
    std::uint32_t x, w;
    bool deleted = false;
};

//TODO: rewrite get_euler to normal.
void get_euler(std::vector<Edge> &edges, const std::vector<std::vector<std::uint32_t>> &g,
               std::uint64_t &len, std::vector<std::uint32_t> &seq, std::uint32_t start = 0) {
    len = 0;
    seq.clear();
    seq.reserve(g.size());
    std::uint32_t next = start;
    while (true) {
        bool any = false;
        for (auto edge_id: g[next]) {
            if (edges[edge_id].deleted) continue;
            seq.push_back(next);
            len += edges[edge_id].w;
            next = edges[edge_id].x ^ next;
            edges[edge_id].deleted = true;
            any = true;
            break;
        }
        if (!any) break;
    }
    for (const auto &edge: edges) {
        if (!edge.deleted) {
            len = inf;
            return;
        }
    }
}

void min_way(const std::vector<Edge> &edges, const std::vector<std::vector<std::uint32_t>> &g,
             std::uint64_t &len, std::vector<std::uint32_t> &seq, std::uint32_t s, std::uint32_t t) {
    std::uint32_t n = g.size();
    std::vector<std::uint32_t> prevs(n);
    std::vector<std::uint64_t> dists(n);
    auto cmp = [](const std::pair<std::uint32_t, std::uint64_t> &a, const std::pair<std::uint32_t, std::uint64_t> &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    };
    std::set<std::pair<std::uint32_t, std::uint64_t>, decltype(cmp)> bfs_que;
    bfs_que.emplace(s, 0);
    dists[s] = 0;
    while (!bfs_que.empty()) {
        auto [v, d] = *bfs_que.begin();
        bfs_que.erase(bfs_que.begin());
        if (dists[v] == inf) break;
        for (auto edge_id: g[v]) {
            auto u = edges[edge_id].x ^ v;
            if (dists[u] > dists[v] + edges[edge_id].w) {
                dists[u] = dists[v] + edges[edge_id].w;
                prevs[u] = v;
                bfs_que.emplace(u, dists[u]);
            }
        }
    }
    len = dists[t];
    if (len == inf) return;
    seq.clear();
    for (std::uint32_t i = prevs[t]; i != s; i = prevs[i]) seq.push_back(i);
    std::reverse(seq.begin(), seq.end());
}

void for_two_solute(std::vector<Edge> &edges, const std::vector<std::vector<std::uint32_t>> &g,
                    std::uint32_t odd_1, std::uint32_t odd_2,
                    std::uint64_t &len, std::vector<std::uint32_t> &seq, std::uint32_t start = 0) {
    auto v = odd_1, u = odd_2;
    edges.emplace_back(v ^ u, 0);
    get_euler(edges, g, len, seq, start);
    for (auto &edge: edges) edge.deleted = false;
    if (len == inf) return;
    std::uint32_t to_add_i;
    for (to_add_i = 0; to_add_i + 1 < seq.size(); ++to_add_i)
        if ((seq[to_add_i] == v && seq[to_add_i + 1] == u) || (seq[to_add_i] == u && seq[to_add_i + 1] == v))
            break;
    if (to_add_i + 1 >= seq.size()) return;
    v = seq[to_add_i];
    u = seq[to_add_i + 1];
    std::uint64_t in_way_len;
    std::vector<std::uint32_t> in_way;
    min_way(edges, g, in_way_len, in_way, v, u);
    if (in_way_len == inf) {
        len = inf;
        return;
    }
    seq.insert(std::next(seq.begin(), to_add_i + 1), in_way.begin(), in_way.end());
    len += in_way_len;
}

void solute(std::vector<Edge> &edges, const std::vector<std::vector<std::uint32_t>> &g,
            const std::vector<std::uint32_t> &odd_points, std::uint64_t &len,
            std::vector<std::uint32_t> &seq) {
    if (odd_points.empty()) {
        get_euler(edges, g, len, seq);
    } else if (odd_points.size() == 1) {
        get_euler(edges, g, len, seq, odd_points.front());
    } else if (odd_points.size() == 2) {
        for_two_solute(edges, g, odd_points.front(), odd_points.back(), len, seq);
    } else {
        len = inf;
        std::uint64_t in_len;
        std::vector<std::uint32_t> in_seq;
        for_two_solute(edges, g, odd_points[0], odd_points[1], in_len, in_seq, odd_points[2]);
        if (in_len < len) {
            len = in_len;
            seq = in_seq;
        }
        for_two_solute(edges, g, odd_points[1], odd_points[2], in_len, in_seq, odd_points[0]);
        if (in_len < len) {
            len = in_len;
            seq = in_seq;
        }
        for_two_solute(edges, g, odd_points[2], odd_points[0], in_len, in_seq, odd_points[1]);
        if (in_len < len) {
            len = in_len;
            seq = in_seq;
        }
    }
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<Edge> edges;
    edges.reserve(100001);
    std::vector<std::vector<std::uint32_t>> g(n);
    std::vector<std::uint32_t> odd_points;
    for (std::uint32_t i = 0, m, u, w; i < n; ++i) {
        std::cin >> m;
        if (m % 2 != 0) odd_points.push_back(i);
        for (std::uint32_t j = 0; j < m; ++j) {
            std::cin >> u >> w;
            if (i >= u) continue;
            edges.emplace_back(i ^ (u - 1), w);
            g[i].push_back(edges.size() - 1);
            g[u - 1].push_back(edges.size() - 1);
        }
    }
    std::uint64_t len;
    std::vector<std::uint32_t> seq;
    solute(edges, g, odd_points, len, seq);
    if (len == inf) std::cout << "-1";
    else {
        std::cout << seq.size() - 1 << "\n";
        for (auto el: seq) std::cout << el << " ";
    }
    return 0;
}
