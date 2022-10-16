#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

struct LiftRequest {
    std::uint32_t id = 0, time = 0, floor = 0;
    bool processed = false;
};

bool LiftRequestComp(const LiftRequest &left, const LiftRequest &right) {
    return left.time < right.time;
}

int main() {
    std::uint32_t humans_count, floors_count;
    std::cin >> humans_count >> floors_count;
    auto cmp = [](const LiftRequest &left, const LiftRequest &right) { return left.id < right.id; };
    std::set<LiftRequest, decltype(cmp)> lift_requests(cmp);
    std::vector<std::uint32_t> results(humans_count, 0);
    for (std::uint32_t t_id = 0; t_id < humans_count; ++t_id) {
        LiftRequest t_req;
        t_req.id = t_id;
        std::cin >> t_req.time >> t_req.floor;
        lift_requests.insert(t_req);
    }
    std::uint32_t time = 0;
    while (std::any_of(lift_requests.begin(), lift_requests.end(),
                       [](const LiftRequest &req) { return !req.processed; })) {
        auto ln_req = std::find_if(lift_requests.begin(), lift_requests.end(),
                                   [](const LiftRequest &req) { return !req.processed; });
        auto request = *ln_req;
        ln_req->processed = true;
        std::uint32_t start_time = std::max(time, request.time);
        std::uint32_t floor_time = start_time + request.floor - 1;
        std::uint32_t finish_time = floor_time + request.floor - 1;
        results[request.id] = finish_time;
        for (auto it = lift_requests.begin(); it != lift_requests.end();) {
            auto cur_it = it;
            ++it;
            if (cur_it->time > finish_time) break;
            if (cur_it->processed) continue;
            if (cur_it->floor > request.floor) continue;
            if (cur_it->time > floor_time + request.floor - cur_it->floor) continue;
            results[cur_it->id] = finish_time;
            lift_requests.erase(cur_it);
        }
        time = finish_time;
    }
    for (const auto &result: results) std::cout << result << std::endl;
    return 0;
}
