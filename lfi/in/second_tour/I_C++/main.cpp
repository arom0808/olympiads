#include <iostream>
#include <map>

const std::uint64_t ost = 998244353;

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::map<std::int64_t, std::uint64_t> walls;
    std::int64_t temp_1;
    std::uint64_t temp_2;
    for (std::uint32_t i = 0; i < N; ++i) {
        std::cin >> temp_1 >> temp_2;
        walls.emplace(temp_1, temp_2);
    };
    std::uint64_t now_time = 0, last_crash_time = 0;
    bool now_ball_direct = true;
    while (!walls.empty()) {
        if (now_ball_direct) {
            auto next_wall = walls.lower_bound(0);
            if (next_wall == walls.begin()) {
                std::cout << (now_time + (next_wall->first % ost)) % ost;
                return 0;
            }
            if (next_wall == walls.end()) {
                std::cout << last_crash_time;
                return 0;
            }
            auto pre_wall = std::prev(next_wall);
            if (pre_wall->second == next_wall->second) {
                now_time += (((((next_wall->first - pre_wall->first) % ost) * 2) % ost) * pre_wall->second) % ost;
                last_crash_time = now_time - ((0 - pre_wall->first) % ost);
                walls.erase(pre_wall);
                walls.erase(next_wall);
            } else if (pre_wall->second < next_wall->second) {
                now_time += (((((next_wall->first - pre_wall->first) % ost) * 2) % ost) * (pre_wall->second % ost)) +
                            ((2 * ((next_wall->first) % ost)) % ost);
                last_crash_time = ((((next_wall->first - pre_wall->first) % ost) * 2) % ost * pre_wall->second) % ost +
                                  (next_wall->first % ost);
                now_ball_direct = false;
                if (next_wall->second - pre_wall->second == 1) walls.erase(next_wall);
                else next_wall->second -= pre_wall->second + 1;
                walls.erase(pre_wall);
            } else {
                now_time += (((((next_wall->first - pre_wall->first) % ost) * 2) % ost) * (next_wall->second % ost) %
                             ost);
                last_crash_time = (now_time - ((0 - pre_wall->first) % ost)) % ost;
                pre_wall->second -= next_wall->second;
                walls.erase(next_wall);
            }
        } else {
            auto prev_right_wall = walls.lower_bound(0);
            if (prev_right_wall == walls.begin()) {
                std::cout << last_crash_time;
                return 0;
            }
            if (prev_right_wall == walls.end()) {
                std::cout << (now_time - ((0 - std::prev(prev_right_wall)->first) % ost)) % ost;
                return 0;
            }
            auto next_left_wall = std::prev(prev_right_wall);
            if (next_left_wall->second == prev_right_wall->second) {
                now_time += (((((prev_right_wall->first - next_left_wall->first) % ost) * 2) % ost) *
                             (prev_right_wall->second % ost)) % ost;
                last_crash_time = (now_time - (prev_right_wall->first % ost)) % ost;
                walls.erase(next_left_wall);
                walls.erase(prev_right_wall);
            } else if (prev_right_wall->second < next_left_wall->second) {
                now_time += ((((prev_right_wall->first - next_left_wall->first) % ost) * 2 * prev_right_wall->second) %
                             ost) +
                            2 * ((0 - next_left_wall->first) % ost);
                last_crash_time = (prev_right_wall->first - next_left_wall->first) * 2 * prev_right_wall->second +
                                  (0 - next_left_wall->first);
                now_ball_direct = true;
                if (next_left_wall->second - prev_right_wall->second == 1) walls.erase(next_left_wall);
                else next_left_wall->second -= prev_right_wall->second + 1;
                walls.erase(prev_right_wall);
            } else {
                now_time += (prev_right_wall->first - next_left_wall->first) * 2 * next_left_wall->second;
                last_crash_time = now_time - prev_right_wall->first;
                prev_right_wall->second -= next_left_wall->second;
                walls.erase(next_left_wall);
            }
        }
    }
    std::cout << last_crash_time;
    return 0;
}
