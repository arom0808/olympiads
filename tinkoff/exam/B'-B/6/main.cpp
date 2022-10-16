#include <iostream>
#include <vector>
#include <set>

std::uint64_t max_variants_count = 1000000007ull;

std::uint64_t GetExistsRosesCountInNearestTowns(const std::vector<bool> &towns_is_rose_exists,
                                                std::vector<bool> &towns_is_visited,
                                                const std::vector<std::set<std::uint64_t>> &ways,
                                                std::uint64_t town_id, std::uint64_t recursion_level) {
    std::uint64_t result = 0;
    if (recursion_level != 0) if (towns_is_rose_exists[town_id]) ++result;
    if (recursion_level >= 2) return result;
    towns_is_visited[town_id] = true;
    for (const auto way_to_town_id: ways[town_id]) {
        if (!towns_is_visited[way_to_town_id]) {
            result += GetExistsRosesCountInNearestTowns(towns_is_rose_exists, towns_is_visited, ways,
                                                        way_to_town_id, recursion_level + 1);
        }
    }
    towns_is_visited[town_id] = false;
    return result;
}

int main() {
    std::uint64_t n, s;
    std::cin >> n >> s;
    std::vector<bool> towns_is_rose_exists(n, false);
    std::vector<bool> towns_is_visited(n, false);
    std::vector<std::set<std::uint64_t>> ways(n);
    for (std::uint64_t i = 0; i < n - 1; ++i) {
        std::uint64_t u, v;
        std::cin >> u >> v;
        --u;
        --v;
        ways[u].insert(v);
        ways[v].insert(u);
    }
    std::uint64_t result_variants_count = 1;
    for (std::uint64_t town_id = 0; town_id < n; ++town_id) {
        std::uint64_t local_nearest_roses_exists_count =
                GetExistsRosesCountInNearestTowns(towns_is_rose_exists, towns_is_visited, ways, town_id, 0);
        std::uint64_t local_roses_variants_count = s - local_nearest_roses_exists_count;
        result_variants_count =
                (result_variants_count * (local_roses_variants_count % max_variants_count)) % max_variants_count;
        towns_is_rose_exists[town_id] = true;
    }
    std::cout << result_variants_count;
    return 0;
}
