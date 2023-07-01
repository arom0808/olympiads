#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <set>

void AddWayToWays(std::map<std::uint8_t, std::set<std::uint8_t>> &ways, std::uint8_t from, std::uint8_t to) {
    auto f_it = ways.find(from);
    if (f_it == ways.end()) { ways.emplace(from, std::set<std::uint8_t>{to}); }
    else f_it->second.emplace(to);
}

bool dfs(std::map<std::uint8_t, std::set<std::uint8_t>> &ways, std::vector<char> &colors, std::uint8_t point_from) {
    auto it = ways.find(point_from);
    if (it == ways.end()) return false;
    colors[point_from] = 'g';
    for (auto point_to: it->second) {
        if (colors[point_to] == 'g') return true;
        if (colors[point_to] == 'b') continue;
        if (dfs(ways, colors, point_to)) return true;
    }
    colors[point_from] = 'b';
    return false;
}

bool dfs_search(std::map<std::uint8_t, std::set<std::uint8_t>> &ways, std::uint8_t point_from,
                std::uint8_t search_point, std::map<std::pair<std::uint8_t, std::uint8_t>, bool> &cache) {
    if (point_from == search_point) return true;
    auto it = ways.find(point_from);
    if (it == ways.end()) return false;
    auto c_it = cache.find({point_from, search_point});
    if (c_it != cache.end()) return c_it->second;
    for (auto point_to: it->second) {
        if (dfs_search(ways, point_to, search_point, cache)) {
            cache.emplace(std::pair<std::uint8_t, std::uint8_t>{point_from, search_point}, true);
            return true;
        }
    }
    cache.emplace(std::pair<std::uint8_t, std::uint8_t>{point_from, search_point}, false);
    return false;
}

int main() {
    std::uint32_t N, M;
    std::cin >> N >> M;
    std::map<std::uint8_t, std::set<std::uint8_t>> ways;
    std::uint32_t from, to;
    for (std::uint32_t i = 0; i < M; ++i) {
        std::cin >> from >> to;
        AddWayToWays(ways, --from, --to);
    }
    std::vector<char> colors(N, 'w');
    for (std::uint32_t i = 0; i < N; ++i) {
        if (colors[i] != 'w') continue;
        if (dfs(ways, colors, i)) {
            std::cout << "No";
            return 0;
        }
    }
    std::vector<std::uint8_t> students(N);
    for (std::uint32_t i = 0; i < N; ++i) students[i] = i;
    std::map<std::pair<std::uint8_t, std::uint8_t>, bool> cache;
    for (std::uint32_t i = 0; i < N; ++i) {
        for (std::uint32_t j = 0; j < N; ++j) {
            if (i < j) {
                if (dfs_search(ways, students[j], students[i], cache))
                    std::swap(students[i], students[j]);
            } else if (i > j) {
                if (dfs_search(ways, students[i], students[j], cache))
                    std::swap(students[i], students[j]);
            }
        }
    }
    std::cout << "Yes\n";
    for (auto num: students) std::cout << num + 1 << " ";
    return 0;
}
