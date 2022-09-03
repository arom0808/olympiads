#include <iostream>
#include <map>

using TownId = std::uint16_t;
using RoadLength = std::uint16_t;
using RoadsMap = std::multimap<TownId, std::pair<TownId, RoadLength>>;
using MaxWayWithoutPetrolMap = std::map<std::pair<TownId, TownId>, RoadLength>;

int main() {
    RoadsMap roads_map;
    MaxWayWithoutPetrolMap min_without_petrol_map;
    std::uint32_t N, K;
    std::cin >> N >> K;
    for (std::uint32_t i = 0; i < K; ++i) {
        TownId a, b;
        RoadLength c;
        std::cin >> a >> b >> c;
        roads_map.insert({a, {b, c}});
        roads_map.insert({b, {a, c}});
    }
    return 0;
}
