#pragma GCC optimize("Ofast")
#pragma GCC optimize(O3)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <set>
#include <unordered_map>

const std::uint32_t inf = 1e9;

class DSU {
private:
    std::vector<std::uint32_t> link, _size;

    std::uint32_t find(std::uint32_t v) {
        while (link[v] != v) v = link[v];
        return v;
    }

public:
    void unite(std::uint32_t a, std::uint32_t b) {
        a = link[a] = find(a);
        b = link[b] = find(b);
        if (a == b) return;
        if (_size[a] < _size[b]) {
            link[a] = b;
            _size[b] += _size[a];
        } else {
            link[b] = a;
            _size[a] += _size[b];
        }
    }

    std::uint32_t get(std::uint32_t v) {
        return link[v] = find(v);
    }

    [[nodiscard]] std::uint32_t size(std::uint32_t v) { return _size[link[v] = find(v)]; }

    explicit DSU(std::uint32_t els_count) : link(els_count), _size(els_count, 1) {
        std::iota(link.begin(), link.end(), 0);
    }
};


class SegmentTree {
private:
    struct Node {
        std::uint32_t min;
    };

    std::vector<Node> nodes;
    std::uint32_t _size;

    void abstract_init_node(std::uint32_t node_id, std::uint32_t left, std::uint32_t right,
                            const std::function<std::uint32_t(std::uint32_t)> &func) {
        if (left >= right) nodes[node_id].min = inf;
        else if (left + 1 == right) nodes[node_id].min = func(left);
        else {
            abstract_init_node(node_id * 2, left, (left + right) / 2, func);
            abstract_init_node(node_id * 2 + 1, (left + right) / 2, right, func);
            nodes[node_id].min = std::min(nodes[node_id * 2].min, nodes[node_id * 2 + 1].min);
        }
    }

    [[nodiscard]] std::uint32_t
    _min(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
         std::uint32_t req_right) const {
        if (node_left >= node_right || req_right <= node_left || req_left >= node_right) return inf;
        if (req_left <= node_left && req_right >= node_right) return nodes[node_id].min;
        return std::min(_min(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right),
                        _min(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right));
    }

    void _set(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
              std::uint32_t req_right, std::uint32_t val) {
        if (node_left >= node_right || req_right <= node_left || req_left >= node_right) return;
        if (node_left + 1 == node_right) nodes[node_id].min = val;
        else {
            _set(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
            _set(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
            nodes[node_id].min = std::min(nodes[node_id * 2].min, nodes[node_id * 2 + 1].min);
        }
    }

    [[nodiscard]] std::uint32_t
    _max_pos_x(std::uint32_t node_id, std::uint32_t node_left, std::uint32_t node_right, std::uint32_t req_left,
               std::uint32_t req_right, std::uint32_t x) const {
        if (node_left >= node_right || req_right <= node_left || req_left >= node_right ||
            nodes[node_id].min >= x)
            return inf;
        if (node_left + 1 == node_right) return node_left;
        auto r1 = _max_pos_x(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, x);
        if (r1 != inf) return r1;
        return _max_pos_x(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, x);
    }


public:
    explicit SegmentTree(std::uint32_t n, std::uint32_t value) : nodes(n * 4), _size(n) {
        abstract_init_node(1, 0, _size, [value](std::uint32_t i) { return value; });
    }

    void set(std::uint32_t left, std::uint32_t right, std::uint32_t val) {
        _set(1, 0, _size, left, right, val);
    }

    [[nodiscard]] std::uint32_t min(std::uint32_t left, std::uint32_t right) const {
        return _min(1, 0, _size, left, right);
    }

    [[nodiscard]] std::uint32_t max_pos_x(std::uint32_t left, std::uint32_t right, std::uint32_t x) const {
        return _max_pos_x(1, 0, _size, left, right, x);
    }

    [[nodiscard]] std::uint32_t size() const { return _size; }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::uint32_t> els(n);
    for (auto &e: els) {
        std::cin >> e;
        --e;
    }
    DSU groups_dsu(n);
    for (std::uint32_t i = 0, u, v; i < m; ++i) {
        std::cin >> u >> v;
        groups_dsu.unite(u - 1, v - 1);
    }
    std::vector<std::uint32_t> p_gr(n);
    std::set<std::uint32_t> used_gs;
    for (std::uint32_t i = 0; i < n; ++i)
        used_gs.insert(p_gr[i] = groups_dsu.get(i));
    std::vector<std::uint32_t> used_dzc(used_gs.begin(), used_gs.end());
    for (std::uint32_t i = 0; i < n; ++i)
        p_gr[i] = std::distance(used_dzc.begin(), std::lower_bound(used_dzc.begin(), used_dzc.end(), p_gr[i]));
    std::vector<std::vector<std::uint32_t>> groups(used_dzc.size());
    for (std::uint32_t i = 0; i < n; ++i)
        if (groups[p_gr[i]].capacity() < groups_dsu.size(i))
            groups[p_gr[i]].reserve(groups_dsu.size(i));
    for (std::uint32_t i = 0; i < n; ++i) groups[p_gr[i]].push_back(i);
    for (auto &group: groups) std::sort(group.begin(), group.end());
    SegmentTree dpmin(n + 1, inf);
    std::uint32_t max_res = 0;
    std::unordered_map<std::uint32_t, std::uint32_t> to_add;
    for (std::uint32_t i = 0; i < n; ++i) {
        for (std::uint32_t j = 0; j < groups[p_gr[i]].size(); ++j) {
            std::uint32_t pos = groups[p_gr[i]][j];
            auto max_pre_len = dpmin.max_pos_x(0, n, els[pos]);
            if (max_pre_len == inf) max_pre_len = 0;
            auto it = to_add.find(max_pre_len + 1);
            if (it == to_add.end()) to_add.emplace(max_pre_len + 1, els[pos]);
            else if (it->second > els[pos]) it->second = els[pos];
            if (max_pre_len + 1 > max_res) max_res = max_pre_len + 1;
        }
        while (!to_add.empty()) {
            auto [pos, v] = *to_add.begin();
            to_add.erase(to_add.begin());
            if (dpmin.min(pos, pos + 1) > v) dpmin.set(pos, pos + 1, v);
        }
    }
    std::cout << max_res;
    return 0;
}
