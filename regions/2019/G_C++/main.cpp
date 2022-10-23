#include <iostream>
#include <vector>
#include <algorithm>

const std::uint32_t null_value = 3e6 + 1;

bool IsCycleInLinkComponentExists(std::vector<std::vector<bool>> &edges, std::vector<bool> &is_visited,
                                  std::uint32_t current_vertex) {
    bool result = false;
    is_visited[current_vertex] = true;
    for (std::uint32_t i = 0; i < edges.size(); ++i) {
        if (edges[current_vertex][i]) {
            if (is_visited[i]) result = true;
            else {
                if (IsCycleInLinkComponentExists(edges, is_visited, i))
                    result = true;
            }
            break;
        }
    }
    return result;
}

std::uint32_t GetOut(std::vector<std::vector<bool>> &edges, std::vector<std::uint32_t> &with,
                     std::vector<std::uint32_t> &out, std::uint32_t vertex);

std::uint32_t GetWith(std::vector<std::vector<bool>> &edges, std::vector<std::uint32_t> &with,
                      std::vector<std::uint32_t> &out, std::uint32_t vertex) {
    if (with[vertex] != null_value) return with[vertex];
    std::uint32_t result = 1;
    for (std::uint32_t i = 0; i < edges.size(); ++i)
        if (edges[i][vertex]) result += GetOut(edges, with, out, i);
    with[vertex] = result;
    return with[vertex];
}

std::uint32_t GetOut(std::vector<std::vector<bool>> &edges, std::vector<std::uint32_t> &with,
                     std::vector<std::uint32_t> &out, std::uint32_t vertex) {
    if (out[vertex] != null_value) return out[vertex];
    std::uint32_t result = 0;
    for (std::uint32_t i = 0; i < edges.size(); ++i)
        if (edges[i][vertex])
            result += std::max(GetWith(edges, with, out, i), GetOut(edges, with, out, i));
    out[vertex] = result;
    return out[vertex];
}

std::uint32_t MaxInTreeWithRoot(std::vector<std::vector<bool>> &edges, std::vector<std::uint32_t> &with,
                                std::vector<std::uint32_t> &out, std::uint32_t root) {
    return std::max(GetWith(edges, with, out, root), GetOut(edges, with, out, root));
}

std::uint32_t NotCycleLinkComponentMaxCount(std::vector<std::vector<bool>> &edges, std::vector<std::uint32_t> &with,
                                            std::vector<std::uint32_t> &out, std::uint32_t current_vertex) {
    std::uint32_t root = current_vertex;
    bool is_root;
    while (true) {
        is_root = true;
        for (std::uint32_t i = 0; i < edges.size(); ++i) {
            if (edges[root][i]) {
                root = i;
                is_root = false;
                break;
            }
        }
        if (is_root) break;
    }
    return MaxInTreeWithRoot(edges, with, out, root);
}

std::uint32_t LinkComponentMaxCount(std::vector<std::vector<bool>> &edges, std::vector<std::uint32_t> &with,
                                    std::vector<std::uint32_t> &out, std::vector<bool> &is_visited,
                                    std::uint32_t current_vertex) {
    bool is_cycle_exists = IsCycleInLinkComponentExists(edges, is_visited, current_vertex);
    if (!is_cycle_exists) return NotCycleLinkComponentMaxCount(edges, with, out, current_vertex);
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::vector<bool>> edges(n, std::vector<bool>(n, false));
    std::int32_t temp_number;
    for (std::uint32_t i = 0; i < n; ++i) {
        std::cin >> temp_number;
        if (temp_number != -1) edges[i][temp_number - 1] = true;
    }
    std::vector<std::uint32_t> with(n, null_value), out(n, null_value);
    std::vector<bool> is_visited(n, false);
    std::uint32_t result = 0;
    for (std::uint32_t i = 0; i < n; ++i) {
        if (is_visited[i]) continue;
        result += LinkComponentMaxCount(edges, with, out, is_visited, i);
    }
    std::cout << result;
    return 0;
}
