#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Point {
    std::int32_t path_length;
    std::int32_t closest_point_to_beginning;
};

std::vector<std::uint32_t> ClosestWay(const std::vector<std::vector<std::uint32_t>> &graph, std::uint32_t start_point,
                                      std::uint32_t finish_point) {
    std::vector<Point> points(graph.size(), Point{-1, -1});
    std::vector<bool> is_visited(graph.size(), false);
    std::queue<std::uint32_t> points_queue;
    points_queue.push(start_point);
    points[start_point] = Point{0, -1};
    while (!points_queue.empty()) {
        std::uint32_t point_id = points_queue.front();
        points_queue.pop();
        if (is_visited[point_id]) continue;
        is_visited[point_id] = true;
        for (std::uint32_t i = 0; i < graph[point_id].size(); ++i) {
            if (!graph[point_id][i]) continue;
            points_queue.push(i);
            if (points[i].path_length == -1 || points[i].path_length > points[point_id].path_length + 1) {
                points[i].path_length = points[point_id].path_length + 1;
                points[i].closest_point_to_beginning = static_cast<std::int32_t>(point_id);
            }
        }
    }
    std::vector<std::uint32_t> result;
    result.reserve(graph.size());
    if (points[finish_point].path_length == -1) return result;
    result.push_back(finish_point);
    auto cur_point = points[finish_point];
    while (cur_point.closest_point_to_beginning != -1) {
        result.push_back(cur_point.closest_point_to_beginning);
        cur_point = points[cur_point.closest_point_to_beginning];
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::vector<std::uint32_t>> graph(N, std::vector<std::uint32_t>(N));
    char buff_ch;
    for (auto &&row: graph) {
        for (auto &&value: row) {
            std::cin >> buff_ch;
            if (buff_ch == '0') value = false;
            else value = true;
        }
    }
    std::uint32_t start_point, finish_point;
    std::cin >> start_point >> finish_point;
    if (start_point == finish_point) {
        std::cout << 0;
        return 0;
    }
    auto closest_way = ClosestWay(graph, start_point - 1, finish_point - 1);
    if (closest_way.empty()) {
        std::cout << -1;
        return 0;
    }
    std::cout << closest_way.size() - 1 << std::endl;
    for (const auto &point_id: closest_way) std::cout << point_id + 1 << " ";
    return 0;
}
