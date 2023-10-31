#include <iostream>
#include <vector>

struct Vertex {
    bool is_ok;
    std::vector<std::uint32_t> neighbours;

    Vertex(bool is_ok = false) : is_ok(is_ok) {}
};

struct Rebro {
    std::uint32_t l, r, cnt_l, cnt_r;
};

std::uint32_t vert_cnt(const std::vector<Vertex> &adj, std::uint32_t v, std::uint32_t no_way) {
    if (!adj[v].is_ok) return 0;
    std::uint32_t res = 1;
    for (auto u: adj[v].neighbours) {
        if (u == no_way || !adj[u].is_ok) continue;
        res += vert_cnt(adj, u, v);
    }
    return res;
}

void
one_side_new_gen(const std::vector<Vertex> &adj, std::vector<Vertex> &new_adj, std::vector<Rebro> &new_rebras,
                 std::uint32_t v, std::uint32_t no_way) {
    if (!adj[v].is_ok) return;
    new_adj[v].is_ok = true;
    for (auto u: adj[v].neighbours) {
        if (u == no_way || !adj[u].is_ok) continue;
        new_rebras.push_back(Rebro{u, v, 0, 0});
        new_adj[v].neighbours.push_back(u);
        new_adj[u].neighbours.push_back(v);
        one_side_new_gen(adj, new_adj, new_rebras, u, v);
    }
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<Vertex> adj(n, Vertex(true));
    std::vector<Rebro> rebras;
    for (std::uint32_t i = 0, a, b; i < n - 1; ++i) {
        std::cin >> a >> b;
        adj[a - 1].neighbours.push_back(b - 1);
        adj[b - 1].neighbours.push_back(a - 1);
        rebras.push_back(Rebro{a - 1, b - 1, 0, 0});
    }
    std::vector<Vertex> new_adj;
    std::vector<Rebro> new_rebras;
    while (!rebras.empty()) {
        for (auto &rebro: rebras) {
            rebro.cnt_l = vert_cnt(adj, rebro.l, rebro.r);
            rebro.cnt_r = vert_cnt(adj, rebro.r, rebro.l);
        }
        std::uint32_t mid_rebro = 0, min_dif = 1000;
        for (std::uint32_t i = 0; i < rebras.size(); ++i) {
            auto dif = std::max(rebras[i].cnt_l, rebras[i].cnt_r) - std::min(rebras[i].cnt_l, rebras[i].cnt_r);
            if (dif < min_dif) {
                mid_rebro = i;
                min_dif = dif;
            }
        }
        std::cout << "? " << rebras[mid_rebro].l + 1 << " " << rebras[mid_rebro].r + 1 << "\n";
        std::cout.flush();
        std::uint32_t new_v_start;
        std::cin >> new_v_start;
        --new_v_start;
        new_adj.clear();
        new_adj.resize(n);
        new_rebras.clear();
        one_side_new_gen(adj, new_adj, new_rebras, new_v_start,
                         (new_v_start == rebras[mid_rebro].l ? rebras[mid_rebro].r : rebras[mid_rebro].l));
        adj = new_adj;
        rebras = new_rebras;
    }
    for (std::uint32_t i = 0; i < n; ++i) {
        if (adj[i].is_ok) {
            std::cout << "! " << i + 1;
            return 0;
        }
    }
    return 0;
}
