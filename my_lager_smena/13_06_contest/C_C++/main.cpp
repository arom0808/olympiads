#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

class DSU {
public:
    std::vector<std::uint32_t> parent;
    std::vector<std::uint32_t> size;
    std::vector<std::map<std::uint32_t, std::uint32_t>> elements_links_cnts;
//    std::vector<std::uint32_t> min_links_cnt;

    std::uint32_t get_set_size(std::uint32_t v) {
        auto a = find_set(v);
        if (a == 1e9) return 0;
        return size[a];
    }

    void make_set(std::uint32_t v) {
        parent[v] = v;
        size[v] = 1;
        elements_links_cnts[v].emplace(0, 1);
    }

    std::uint32_t find_set(std::uint32_t v) {
        if (parent[v] == 1e9) return 1e9;
        if (parent[v] == v) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(std::uint32_t a, std::uint32_t b) {
        a = find_set(a);
        b = find_set(b);
        if (a == 1e9 || b == 1e9) return;
        if (a != b) {
            if (size[a] < size[b]) std::swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            elements_links_cnts[a].merge(elements_links_cnts[b]);
            for (auto [el, cnt]: elements_links_cnts[b]) elements_links_cnts[a][el] += cnt;
            elements_links_cnts[b].clear();
        }
    }

    explicit DSU(std::uint32_t max_el) : parent(max_el + 1, 1e9), size(max_el + 1, 0),
                                         elements_links_cnts(max_el + 1) {}
};

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::set<std::uint32_t>> links(n);
    std::vector<std::pair<std::uint32_t, std::uint32_t>> vertexes_ans_links_cnt
            (n, std::pair<std::uint32_t, std::uint32_t>(0, 0));
    for (std::uint32_t i = 0; i < n; ++i) vertexes_ans_links_cnt[i].first = i;
    for (std::uint32_t i = 0, t_1, t_2; i < m; ++i) {
        std::cin >> t_1 >> t_2;
        --t_1;
        --t_2;
        ++vertexes_ans_links_cnt[t_1].second;
        ++vertexes_ans_links_cnt[t_2].second;
        links[t_1].emplace(t_2);
        links[t_2].emplace(t_1);
    }
    std::sort(vertexes_ans_links_cnt.rbegin(), vertexes_ans_links_cnt.rend(),
              [](const std::pair<std::uint32_t, std::uint32_t> &a, const std::pair<std::uint32_t, std::uint32_t> &b) {
                  return a.second < b.second;
              });
    DSU dsu(n);
    std::vector<std::uint32_t> links_cnt(n, 0);
    std::uint32_t max_res = 0;
    for (const auto &[now_id, start_router_links_cnt]: vertexes_ans_links_cnt) {
        dsu.make_set(now_id);
        for (auto linked: links[now_id]) {
            auto a = dsu.find_set(linked);
            if (a == 1e9) continue;
            dsu.union_sets(now_id, a);
            a = dsu.find_set(now_id);
            auto it = dsu.elements_links_cnts[a].find(links_cnt[now_id]);
            if (--it->second == 0) dsu.elements_links_cnts[a].erase(it);
            ++links_cnt[now_id];
            it = dsu.elements_links_cnts[a].find(links_cnt[now_id]);
            if (it == dsu.elements_links_cnts[a].end()) dsu.elements_links_cnts[a].emplace(links_cnt[now_id], 1);
            else ++it->second;
            it = dsu.elements_links_cnts[a].find(links_cnt[linked]);
            if (--it->second == 0) dsu.elements_links_cnts[a].erase(it);
            ++links_cnt[linked];
            it = dsu.elements_links_cnts[a].find(links_cnt[linked]);
            if (it == dsu.elements_links_cnts[a].end()) dsu.elements_links_cnts[a].emplace(links_cnt[linked], 1);
            else ++it->second;
        }
        std::uint32_t cur_res =
                dsu.elements_links_cnts[dsu.find_set(now_id)].begin()->first * dsu.get_set_size(now_id);
        if (cur_res > max_res) max_res = cur_res;
    }
    std::cout << max_res;
    return 0;
}