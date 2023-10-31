#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

int main() {
    std::int32_t n, k;
    std::cin >> n >> k;
    std::vector<std::int32_t> balls(n);
    std::map<std::int32_t, std::vector<std::int32_t>> pos_on_ball;
    for (std::int32_t i = 0; i < n; ++i) {
        std::cin >> balls[i];
        auto it = pos_on_ball.find(balls[i]);
        if (it != pos_on_ball.end()) it->second.push_back(i);
        else pos_on_ball.emplace(balls[i], std::vector<std::int32_t>{i});
    }
    std::int32_t best_res = 0;
    for (std::int32_t last_ball = 0; last_ball < n; ++last_ball) {
        auto &positions = pos_on_ball[balls[last_ball]];
        std::int32_t last_ball_pos = std::distance(positions.begin(),
                                                   std::lower_bound(positions.begin(), positions.end(), last_ball));
        std::int32_t right = last_ball_pos;
        std::int32_t left = 0;
        while (left != right) {
            std::int32_t middle = (right + left) / 2;
            if (last_ball - positions[middle] - (last_ball_pos - middle) > k) left = middle + 1;
            else right = middle;
        }
        std::int32_t this_res = (last_ball_pos - left) + 1;
        if (this_res > best_res) best_res = this_res;
    }
    std::cout << best_res;
    return 0;
}
