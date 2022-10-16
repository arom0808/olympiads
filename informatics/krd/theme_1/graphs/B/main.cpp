#include <iostream>
#include <vector>

bool VisitNeighbours(std::uint32_t vertex, const std::vector<std::vector<bool>> &graph_matrix,
                     std::vector<bool> &is_visited) {
    is_visited[vertex] = true;
    for (std::uint32_t i = 0; i < graph_matrix.size(); ++i) {
        if (graph_matrix[vertex][i]) {
            if (is_visited[i]) {
                return true;
            } else {
                bool temp_result = VisitNeighbours(i, graph_matrix, is_visited);
                if (temp_result) return true;
            }
        }
    }
    return false;
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::vector<bool>> graph_matrix(N, std::vector<bool>(N, false));
    std::uint32_t temp_number;
    for (std::uint32_t i = 0; i < N; ++i) {
        for (std::uint32_t j = 0; j < N; ++j) {
            std::cin >> temp_number;
            if (temp_number == 0) graph_matrix[i][j] = false;
            else graph_matrix[i][j] = true;
        }
    }
    std::vector<bool> is_visited(N, false);
    for (std::uint32_t i = 0; i < N; ++i) {
        if (!is_visited[i]) {
            if (VisitNeighbours(i, graph_matrix, is_visited)) {
                std::cout << "1";
                return 0;
            }
        }
    }
    std::cout << "0";
    return 0;
}