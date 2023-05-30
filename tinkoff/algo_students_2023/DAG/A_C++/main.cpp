#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <set>

using Graph = std::map<std::uint32_t, std::vector<std::uint32_t>>;
using MapII = std::map<std::uint32_t, std::uint32_t>;

std::uint32_t GetLinksCount(const Graph::const_iterator &it, const Graph &graph) {
    if (it == graph.end()) return 0;
    return it->second.size();
}

void InFirstDFS(const Graph &graph, std::vector<bool> &used, std::vector<std::uint32_t> &counters_on_ids,
                std::uint32_t &counter, std::uint32_t start_id) {
    std::deque<std::pair<std::uint32_t, std::uint32_t>> stack;
    stack.emplace_back(start_id, 0);
    while (!stack.empty()) {
        auto &now_act = stack.back();
        used[now_act.first] = true;
        counters_on_ids[now_act.first] = ++counter;
        auto it = graph.find(now_act.first);
        if (now_act.second >= GetLinksCount(it, graph)) {
            stack.pop_back();
            continue;
        }
        std::uint32_t next_son_id = it->second[now_act.second++];
        if (!used[next_son_id]) stack.emplace_back(next_son_id, 0);
    }
}

void FirstDFS(std::uint32_t n, const Graph &graph, MapII &ids_on_counters) {
    ids_on_counters.clear();
    std::vector<std::uint32_t> counters_on_ids(n);
    std::vector<bool> used(n, false);
    std::uint32_t counter = 0;
    for (std::uint32_t i = 0; i < n; ++i) {
        if (!used[i]) {
            InFirstDFS(graph, used, counters_on_ids, counter, i);
            ++counter;
        }
    }
    for (std::uint32_t i = 0; i < n; ++i) ids_on_counters.emplace(counters_on_ids[i], i);
}

void InSecondDFS(std::uint32_t n, std::uint32_t now_comp, const Graph &reversed_graph,
                 std::vector<std::uint32_t> &comp_on_id, std::uint32_t start_id) {
    std::deque<std::pair<std::uint32_t, std::uint32_t>> stack;
    stack.emplace_back(start_id, 0);
    while (!stack.empty()) {
        auto &now_act = stack.back();
        comp_on_id[now_act.first] = now_comp;
        auto it = reversed_graph.find(now_act.first);
        if (now_act.second >= GetLinksCount(it, reversed_graph)) {
            stack.pop_back();
            continue;
        }
        std::uint32_t next_son_id = it->second[now_act.second++];
        if (comp_on_id[next_son_id] == n + 1) stack.emplace_back(next_son_id, 0);
    }
}

std::uint32_t SecondDFS(std::uint32_t n, const Graph &reversed_graph, const MapII &ids_on_counters,
                        std::vector<std::uint32_t> &comp_on_id) {
    std::uint32_t now_comp = 0;
    for (auto it = ids_on_counters.rbegin(); it != ids_on_counters.rend(); ++it) {
        if (comp_on_id[it->second] == n + 1) {
            InSecondDFS(n, now_comp, reversed_graph, comp_on_id, it->second);
            ++now_comp;
        }
    }
    return now_comp;
}

void AddWayToGraph(Graph &graph, std::uint32_t a, std::uint32_t b) {
    auto it = graph.find(a);
    if (it != graph.end()) it->second.push_back(b);
    else graph.emplace(a, std::vector<std::uint32_t>{b});
}

std::uint32_t
GetCondensedGraph(std::uint32_t n, const Graph &graph, const Graph &reversed_graph, Graph &condensed_graph) {
    condensed_graph.clear();
    MapII ids_on_counters;
    FirstDFS(n, graph, ids_on_counters);
    std::vector<std::uint32_t> comp_on_id(n, n + 1);
    std::uint32_t comps_count = SecondDFS(n, reversed_graph, ids_on_counters, comp_on_id);
    for (std::uint32_t i = 0; i < n; ++i) {
        auto it = graph.find(i);
        if (it == graph.end()) continue;
        for (const auto &linked_id: it->second) {
            if (comp_on_id[i] == comp_on_id[linked_id]) continue;
            AddWayToGraph(condensed_graph, comp_on_id[i], comp_on_id[linked_id]);
        }
    }
    return comps_count;
}

void InThirdDFS(std::uint32_t n, const Graph &graph, std::vector<bool> &used, std::uint32_t start_id) {
    std::deque<std::pair<std::uint32_t, std::uint32_t>> stack;
    stack.emplace_back(start_id, 0);
    while (!stack.empty()) {
        auto &now_act = stack.back();
        used[now_act.first] = true;
        auto it = graph.find(now_act.first);
        if (now_act.second >= GetLinksCount(it, graph)) {
            stack.pop_back();
            continue;
        }
        std::uint32_t next_son_id = it->second[now_act.second++];
        if (!used[next_son_id]) stack.emplace_back(next_son_id, 0);
    }
}

std::uint32_t ThirdDFS(std::uint32_t n, const Graph &graph, const MapII &ids_on_counters) {
    std::uint32_t steps_cnt = 0;
    std::vector<bool> used(n, false);
    for (auto it = ids_on_counters.rbegin(); it != ids_on_counters.rend(); ++it) {
        if (!used[it->second]) {
            InThirdDFS(n, graph, used, it->second);
            ++steps_cnt;
        }
    }
    return steps_cnt;
}

void ReverseGraph(const Graph &graph, Graph &reversed_graph) {
    reversed_graph.clear();
    for (const auto &i: graph) for (const auto &j: i.second) AddWayToGraph(reversed_graph, j, i.first);
}

int main() {
    std::uint32_t n, m, a, b;
    std::cin >> n >> m;
    Graph graph, reversed_graph;
    for (std::uint32_t i = 0; i < m; ++i) {
        std::cin >> a >> b;
        AddWayToGraph(graph, a - 1, b - 1);
        AddWayToGraph(reversed_graph, b - 1, a - 1);
    }
    Graph condensed_graph, reversed_condensed_graph;
    std::uint32_t condensed_size = GetCondensedGraph(n, graph, reversed_graph, condensed_graph);
    ReverseGraph(condensed_graph, reversed_condensed_graph);
    MapII ids_on_counters;
    FirstDFS(condensed_size, reversed_condensed_graph, ids_on_counters);
    std::cout << ThirdDFS(condensed_size, reversed_condensed_graph, ids_on_counters);
    return 0;
}
