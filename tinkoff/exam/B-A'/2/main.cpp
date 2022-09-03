#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

struct Road {
    bool is_exists;
    std::uint64_t length;

    explicit Road(bool is_exists = false, std::uint64_t length = 0)
            : is_exists(is_exists), length(length) {}
};

struct RoadToTown {
    bool is_exists;
    std::uint64_t town_id;
    std::uint64_t how_many_used;

    explicit RoadToTown(bool is_exists = false, std::uint64_t town_id = 0, std::uint64_t how_many_used = 0)
            : is_exists(is_exists), town_id(town_id), how_many_used(how_many_used) {}
};

struct Town {
public:
    std::uint64_t id;
    Road road_to_start;
    bool is_visited = false;
    RoadToTown last_used_road;

    explicit Town(std::uint64_t id) : id(id) {}

    void IncrementRoadUses(std::vector<Town> &towns) {
        if (last_used_road.is_exists) {
            ++last_used_road.how_many_used;
            towns[last_used_road.town_id].IncrementRoadUses(towns);
        }
    }

    void DecrementRoadUses(std::vector<Town> &towns) {
        if (last_used_road.is_exists) {
            --last_used_road.how_many_used;
            towns[last_used_road.town_id].DecrementRoadUses(towns);
        }
    }
};

using RoadMap = std::vector<std::vector<Road>>;

int main() {
    std::uint64_t vertex_cnt;
    std::cin >> vertex_cnt;
    RoadMap roadmap(vertex_cnt, std::vector<Road>(vertex_cnt));
    for (std::uint64_t i = 0; i < vertex_cnt; ++i) {
        for (std::uint64_t j = 0; j < vertex_cnt; ++j) {
            std::int64_t raw_road;
            std::cin >> raw_road;
            if (raw_road >= 0) roadmap[i][j] = Road{true, static_cast<std::uint64_t>(raw_road)};
        }
    }
    std::vector<Town> towns;
    towns.reserve(vertex_cnt);
    for (std::uint64_t i = 0; i < vertex_cnt; ++i) towns.emplace_back(i);
    towns[0].road_to_start.is_exists = true;
    towns[0].road_to_start.length = 0;
    while (!std::all_of(towns.begin(), towns.end(), [](const Town &town) { return town.is_visited; })) {
        auto cur_town_it = std::min_element(towns.begin(), towns.end(), [](const Town &a, const Town &b) {
            if ((!a.is_visited) && b.is_visited) return true;
            if (a.is_visited && (!b.is_visited)) return false;
            if ((!a.road_to_start.is_exists) && (!b.road_to_start.is_exists)) return false;
            if (a.road_to_start.is_exists && (!b.road_to_start.is_exists)) return true;
            if (b.road_to_start.is_exists && (!a.road_to_start.is_exists)) return false;
            return a.road_to_start.length < b.road_to_start.length;
        });
        cur_town_it->is_visited = true;
        auto cur_roads = roadmap[cur_town_it->id];
        for (std::uint64_t i = 0; i < cur_roads.size(); ++i) {
            if (i == cur_town_it->id) continue;
            if (!cur_roads[i].is_exists) continue;
            if (towns[i].is_visited) continue;
            if ((!towns[i].road_to_start.is_exists) ||
                towns[i].road_to_start.length > cur_town_it->road_to_start.length + cur_roads[i].length) {
                towns[i].road_to_start.is_exists = true;
                towns[i].road_to_start.length = cur_town_it->road_to_start.length + cur_roads[i].length;
                if (towns[i].last_used_road.is_exists) towns[i].DecrementRoadUses(towns);
                else towns[i].last_used_road.is_exists = true;
                towns[i].last_used_road.town_id = cur_town_it->id;
                towns[i].IncrementRoadUses(towns);
            }
        }
    }
    std::uint64_t max_uses = 0;
    for (const auto &town: towns)
        if (town.last_used_road.is_exists)
            if (town.last_used_road.how_many_used > max_uses)
                max_uses = town.last_used_road.how_many_used;
    std::cout << max_uses;
    return 0;
}
