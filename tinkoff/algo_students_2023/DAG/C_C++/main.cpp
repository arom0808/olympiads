#include <iostream>
#include <vector>
#include <map>
#include <deque>

using Graph = std::map<std::uint64_t, std::vector<std::uint64_t>>;
using MapII = std::map<std::uint64_t, std::uint64_t>;

std::uint64_t GetLinksCount(const Graph::const_iterator &it, const Graph &graph) {
    if (it == graph.end()) return 0;
    return it->second.size();
}

void AddWayToGraph(Graph &graph, std::uint64_t a, std::uint64_t b) {
    auto it = graph.find(a);
    if (it != graph.end()) it->second.push_back(b);
    else graph.emplace(a, std::vector<std::uint64_t>{b});
}

void GenerateSupportData(std::uint64_t n, const Graph &graph, const std::vector<std::uint64_t> &time_to_do,
                         MapII &id_on_count, std::uint64_t &result_time,
                         std::uint64_t &result_detail_cnt) {
    std::vector<bool> used(n, false);
    result_detail_cnt = result_time = 0;
    std::vector<std::uint64_t> counters_on_ids(n, 0);
    std::uint64_t counter = 0;
    std::deque<std::pair<std::uint64_t, std::uint64_t>> stack;
    stack.emplace_back(0, 0);
    while (!stack.empty()) {
        auto &now_act = stack.back();
        counters_on_ids[now_act.first] = ++counter;
        if (!used[now_act.first]) {
            result_time += time_to_do[now_act.first];
            ++result_detail_cnt;
        }
        used[now_act.first] = true;
        auto it = graph.find(now_act.first);
        if (now_act.second >= GetLinksCount(it, graph)) { stack.pop_back(); }
        else {
            std::uint64_t next_son_id = it->second[now_act.second++];
//            if (counters_on_ids[next_son_id] == 0)
            stack.emplace_back(next_son_id, 0);
        }
    }
    id_on_count.clear();
    for (std::uint64_t i = 0; i < n; ++i) if (counters_on_ids[i] != 0) id_on_count.emplace(counters_on_ids[i], i);
}

int main() {
    std::uint64_t n;
    std::cin >> n;
    std::vector<std::uint64_t> time_to_do(n);
    for (auto &&i: time_to_do) std::cin >> i;
    Graph graph, reversed_graph;
    for (std::uint64_t i = 0, k; i < n; ++i) {
        std::cin >> k;
        for (std::uint64_t j = 0, h; j < k; ++j) {
            std::cin >> h;
            AddWayToGraph(graph, i, h - 1);
            AddWayToGraph(reversed_graph, h - 1, i);
        }
    }
    MapII id_on_count;
    std::uint64_t result_time, result_detail_cnt;
    GenerateSupportData(n, graph, time_to_do, id_on_count, result_time, result_detail_cnt);
    std::cout << result_time << " " << result_detail_cnt << "\n";
    for (auto &it: id_on_count) std::cout << it.second + 1 << " ";
    return 0;
}

//#include <iostream>
//#include <vector>
//#include <map>
//#include <deque>
//#include <algorithm>
//
//using Graph = std::map<std::uint32_t, std::vector<std::uint32_t>>;
//using MapII = std::map<std::uint32_t, std::uint32_t>;
//
//std::uint32_t GetLinksCount(const Graph::const_iterator &it, const Graph &graph) {
//    if (it == graph.end()) return 0;
//    return it->second.size();
//}
//
//void AddWayToGraph(Graph &graph, std::uint32_t a, std::uint32_t b) {
//    auto it = graph.find(a);
//    if (it != graph.end()) it->second.push_back(b);
//    else graph.emplace(a, std::vector<std::uint32_t>{b});
//}
//
//void GenerateUsed(std::uint32_t n, const Graph &graph, std::vector<bool> &used) {
//    used.clear();
//    used.resize(n, false);
//    std::deque<std::pair<std::uint32_t, std::uint32_t>> stack;
//    stack.emplace_back(0, 0);
//    while (!stack.empty()) {
//        auto &now_act = stack.back();
//        used[now_act.first] = true;
//        auto it = graph.find(now_act.first);
//        if (now_act.second >= GetLinksCount(it, graph)) { stack.pop_back(); }
//        else {
//            std::uint32_t next_son_id = it->second[now_act.second++];
//            if (!used[next_son_id]) stack.emplace_back(next_son_id, 0);
//        }
//    }
//}
//
//std::uint32_t DeleteUnused(Graph &graph, const Graph &reversed_graph, const std::vector<bool> &used) {
//    std::uint32_t deleted_cnt = 0;
//    for (std::uint32_t i = 0; i < used.size(); ++i) {
//        if (used[i]) continue;
//        ++deleted_cnt;
//        graph.erase(i);
//        auto it = reversed_graph.find(i);
//        if (it == reversed_graph.end()) continue;
//        for (const auto &j: it->second) {
//            auto it_2 = graph.find(j);
//            it_2->second.erase(std::lower_bound(it_2->second.begin(), it_2->second.end(), i));
//        }
//    }
//    return used.size() - deleted_cnt;
//}
//
//std::uint32_t GenerateCounters(std::uint32_t n, const Graph &graph, const std::vector<std::uint32_t> &time_to_do,
//                               MapII &id_on_counter) {
//    std::uint32_t counter = 0, result_time = 0;
//    id_on_counter.clear();
//    std::vector<std::uint32_t> counter_on_id(n, 0);
//    std::deque<std::pair<std::uint32_t, std::uint32_t>> stack;
//    if (graph.find(0) != graph.end()) stack.emplace_back(0, 0);
//    else result_time += time_to_do[0];
//    while (!stack.empty()) {
//        auto &now_act = stack.back();
//        counter_on_id[now_act.first] = ++counter;
//        if (now_act.second == 0) result_time += time_to_do[now_act.first];
//        auto it = graph.find(now_act.first);
//        if (now_act.second >= GetLinksCount(it, graph)) {
//            stack.pop_back();
//            continue;
//        }
//        std::uint32_t next_son_id = it->second[now_act.second++];
//        if (counter_on_id[next_son_id] == 0) stack.emplace_back(next_son_id, 0);
//    }
//    for (std::uint32_t i = 0; i < n; ++i) if (counter_on_id[i] != 0) id_on_counter.emplace(counter_on_id[i], i);
//    return result_time;
//}
//
//int main() {
//    std::uint32_t n;
//    std::cin >> n;
//    std::vector<std::uint32_t> time_to_do(n);
//    for (auto &&i: time_to_do) std::cin >> i;
//    Graph graph, reversed_graph;
//    for (std::uint32_t i = 0, k; i < n; ++i) {
//        std::cin >> k;
//        for (std::uint32_t j = 0, h; j < k; ++j) {
//            std::cin >> h;
//            AddWayToGraph(graph, i, h - 1);
//            AddWayToGraph(reversed_graph, h - 1, i);
//        }
//    }
//    for (auto &i: graph) std::sort(i.second.begin(), i.second.end());
//    for (auto &i: reversed_graph) std::sort(i.second.begin(), i.second.end());
//    std::vector<bool> used;
//    GenerateUsed(n, graph, used);
//    std::uint32_t new_size = DeleteUnused(graph, reversed_graph, used);
//    MapII id_on_counter;
//    std::uint32_t res_time = GenerateCounters(new_size, graph, time_to_do, id_on_counter);
//    std::cout << res_time << " " << new_size << "\n";
//    for (const auto &dd: id_on_counter) std::cout << dd.second + 1 << " ";
//    return 0;
//}
