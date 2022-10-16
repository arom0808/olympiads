#include <iostream>
#include <vector>
#include <algorithm>

void VisitNeighbours(std::uint32_t vertex, const std::vector<std::vector<bool>> &graph_matrix,
                     std::vector<bool> &is_visited) {
    is_visited[vertex] = true;
    for (std::uint32_t i = 0; i < graph_matrix.size(); ++i)
        if (graph_matrix[vertex][i])
            if (!is_visited[i])
                VisitNeighbours(i, graph_matrix, is_visited);
}

int main() {
    std::uint32_t N, S;
    std::cin >> N >> S;
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
    VisitNeighbours(S, graph_matrix, is_visited);
    std::uint32_t result = std::count_if(is_visited.begin(), is_visited.end(), [](bool c_i_v) { return c_i_v; });
    std::cout << result;
    return 0;
}
