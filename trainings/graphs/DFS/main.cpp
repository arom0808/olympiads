#include <iostream>
#include <vector>
#include <queue>

std::uint32_t LinkedPointsCount(const std::vector<std::vector<bool>> &graph, std::uint32_t S) {
    std::queue<std::uint32_t> points_queue;
    std::vector<bool> points_is_visited(graph.size(), false);
    points_queue.push(S);
    std::uint32_t result = 0;
    while (!points_queue.empty()) {
        std::uint32_t cur_point = points_queue.front();
        points_queue.pop();
        if (points_is_visited[cur_point]) continue;
        points_is_visited[cur_point] = true;
        ++result;
        for (std::uint32_t i = 0; i < graph[cur_point].size(); ++i) if (graph[cur_point][i]) points_queue.push(i);
    }
    return result;
}

int main() {
    std::uint32_t N, S;
    std::cin >> N >> S;
    std::vector<std::vector<bool>> graph(N, std::vector<bool>(N));
    char buf;
    for (auto &&row: graph) {
        for (auto &&value: row) {
            std::cin >> buf;
            if (buf == '0') value = false;
            else value = true;
        }
    }
    std::cout << LinkedPointsCount(graph, S - 1);
    return 0;
}
