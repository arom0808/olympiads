#include <iostream>
#include <vector>

const std::uint32_t sqrt_e = 500, full_colors_cnt = 1e5 + 1;

struct HeavyVertex {
    bool is_heavy = false;
    std::vector<std::uint32_t> neighbours;
    std::vector<std::uint32_t> cnt_col;
};

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::uint32_t ans = 0;
    std::vector<std::uint32_t> colors(n);
    for (auto &color: colors) std::cin >> color;
    std::vector<std::vector<std::uint32_t>> full_adj(n);
    for (auto &line: full_adj) line.reserve(100);
    for (std::uint32_t i = 0, a, b; i < m; ++i) {
        std::cin >> a >> b;
        full_adj[a - 1].push_back(b - 1);
        full_adj[b - 1].push_back(a - 1);
        if (colors[a - 1] != colors[b - 1]) ++ans;
    }
    std::vector<HeavyVertex> heavy_adj(n);
    for (std::uint32_t v = 0; v < n; ++v) {
        if (full_adj[v].size() < sqrt_e) {
            for (auto u: full_adj[v]) if (full_adj[u].size() >= sqrt_e) heavy_adj[v].neighbours.push_back(u);
        } else {
            heavy_adj[v].is_heavy = true;
            heavy_adj[v].cnt_col.resize(full_colors_cnt, 0);
            for (auto u: full_adj[v]) {
                if (full_adj[u].size() >= sqrt_e) heavy_adj[v].neighbours.push_back(u);
                ++heavy_adj[v].cnt_col[colors[u]];
            }
        }
    }
    std::uint32_t q;
    std::cin >> q;
    for (std::uint32_t i = 0, c, v; i < q; ++i) {
        std::cin >> c >> v;
        --c;
        for (auto u: heavy_adj[c].neighbours) {
            --heavy_adj[u].cnt_col[colors[c]];
            ++heavy_adj[u].cnt_col[v];
        }
        std::uint32_t pre_ok = 0, now_ok = 0;
        if (heavy_adj[c].is_heavy) {
            pre_ok = heavy_adj[c].cnt_col[colors[c]];
            now_ok = heavy_adj[c].cnt_col[v];
        } else {
            for (auto u: full_adj[c]) {
                if (colors[u] == colors[c]) ++pre_ok;
                if (colors[u] == v) ++now_ok;
            }
        }
        if (now_ok > pre_ok) ans -= now_ok - pre_ok;
        else if (now_ok < pre_ok) ans += pre_ok - now_ok;
        colors[c] = v;
        std::cout << ans << "\n";
    }
    return 0;
}
