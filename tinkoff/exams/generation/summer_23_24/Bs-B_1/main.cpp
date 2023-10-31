#include <iostream>
#include <limits>
#include <vector>
#include <queue>

class RawRoute {
public:
    std::int32_t id = 0, P = 0;
    std::vector<std::pair<std::int32_t, std::int32_t>> stations;
};

bool input(std::int32_t &H, std::int32_t &D, std::int32_t &R, std::vector<RawRoute> &raw_routes) {
    std::cin >> H >> D >> R;
    if (H == 0 && D == 0 && R == 0) return false;
    --H;
    raw_routes.resize(R);
    for (std::uint32_t i = 0; i < R; ++i) {
        auto &raw_route = raw_routes[i];
        raw_route.id = i;
        std::int32_t raw_route_size;
        std::cin >> raw_route_size >> raw_route.P;
        raw_route.stations.resize(raw_route_size);
        for (auto &&[id, time]: raw_route.stations) {
            std::cin >> id;
            --id;
        }
        for (auto &&[id, time]: raw_route.stations) std::cin >> time;
    }
    return true;
}

struct StatRoute {
public:
    std::int32_t id, stat_in_route_id, start_time, period, route_time, target;

    std::int32_t nearest_bus_time(std::int32_t time) const {
        if (std::abs(time - start_time) % period == 0) return time;
        if (time < start_time) return start_time - ((start_time - time) / period * period);
        else return start_time + ((time - start_time) / period + 1) * period;
    }

    StatRoute(std::int32_t id, std::int32_t stat_in_route_id, std::int32_t start_time, std::int32_t period,
              std::int32_t route_time, std::int32_t target) :
            id(id), stat_in_route_id(stat_in_route_id), start_time(start_time), period(period), route_time(route_time),
            target(target) {}
};

class Station {
public:
    std::int32_t min_visit_time = std::numeric_limits<std::int32_t>::max();
    std::vector<StatRoute> routes;
};

class DequeElem {
public:
    std::int32_t station_id, time, route_id, stat_in_route_id;

    DequeElem(std::int32_t station_id, std::int32_t time, std::int32_t route_id, std::int32_t stat_in_route_id)
            : station_id(station_id), time(time), route_id(route_id), stat_in_route_id(stat_in_route_id) {}
};

std::int32_t resolve(std::int32_t &H, std::int32_t &D, std::int32_t &R, std::vector<RawRoute> &raw_routes) {
    std::vector<Station> stations(500);
    for (const auto &raw_route: raw_routes) {
        for (std::int32_t i = 0; i < raw_route.stations.size() - 1; ++i) {
            const auto &now_station = raw_route.stations[i], &next_station = raw_route.stations[i + 1];
            stations[now_station.first].routes
                    .emplace_back(raw_route.id, i, now_station.second, raw_route.P,
                                  next_station.second - now_station.second,
                                  next_station.first);
        }
    }
    std::queue<DequeElem> que;
    que.emplace(H, 0, -1, -1);
    auto &target_station = stations[0];
    while (!que.empty()) {
        auto req = que.front();
        que.pop();
        if (req.time >= target_station.min_visit_time) continue;
        auto &station = stations[req.station_id];
        if (req.time < station.min_visit_time) station.min_visit_time = req.time;
        for (auto &route: station.routes) {
            auto &arrival_station = stations[route.target];
            std::int32_t arrival_time =
                    route.nearest_bus_time(
                            (req.route_id == route.id && req.stat_in_route_id == route.stat_in_route_id) ? req.time :
                            req.time + D) + route.route_time;
            if (arrival_time >= target_station.min_visit_time) continue;
            que.emplace(route.target, arrival_time, route.id, route.stat_in_route_id + 1);
        }
    }
    return target_station.min_visit_time;
}

int main() {
    std::int32_t H, D, R;
    std::vector<RawRoute> raw_routes;
    while (input(H, D, R, raw_routes))
        std::cout << resolve(H, D, R, raw_routes) << "\n";
    return 0;
}
