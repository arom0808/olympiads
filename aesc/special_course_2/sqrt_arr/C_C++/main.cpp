#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

const std::uint32_t sqrt_m = 100;

void solute(std::istream &ins, std::ostream &outs) {
    std::uint32_t n, m;
    ins >> n >> m;
    std::vector<std::vector<std::uint32_t>> adj(n);
    for (auto &line: adj) line.reserve(sqrt_m);
    for (std::uint32_t i = 0, l, r; i < m; ++i) {
        ins >> l >> r;
        adj[l - 1].push_back(r - 1);
        adj[r - 1].push_back(l - 1);
    }
    auto cmp = [&adj](std::uint32_t a, std::uint32_t b) {
        if (adj[a].size() < adj[b].size()) return true;
        if (adj[a].size() > adj[b].size()) return false;
        return a < b;
    };
    std::vector<std::uint32_t> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), cmp);
    for (auto &line: adj) std::sort(line.begin(), line.end(), cmp);
    std::vector<bool> used(n, false);
    std::uint32_t ans = 0;
    for (auto v: order) {
        for (auto u: adj[v]) used[u] = true;
        for (auto u: adj[v]) {
            if (!cmp(u, v)) break;
            for (auto w: adj[u]) {
                if (!cmp(w, u)) break;
                if (used[w]) ++ans;
            }
        }
        for (auto u: adj[v]) used[u] = false;
    }
    outs << ans;
}

int main() {
    std::ifstream ins("owls.in");
    std::ofstream outs("owls.out");
    solute(ins, outs);
    ins.close();
    outs.close();
    return 0;
}
