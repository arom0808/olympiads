#include <iostream>
#include <vector>
#include <stack>

const std::uint32_t inf = 1e9 + 1;

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::int32_t> nums(N + 2);
    for (std::uint32_t i = 1; i <= N; ++i) std::cin >> nums[i];
    nums.front() = nums.back() = inf;
    std::vector<std::uint32_t> nearby_greater_or_eq(N + 2);
    std::stack<std::uint32_t> town_for_greater_or_eq_ids;
    town_for_greater_or_eq_ids.push(0);
    std::uint32_t cur_id = 1;
    while (town_for_greater_or_eq_ids.size() != 2 || nums[town_for_greater_or_eq_ids.top()] != inf) {
        while (!town_for_greater_or_eq_ids.empty() && nums[town_for_greater_or_eq_ids.top()] != inf &&
               nums[town_for_greater_or_eq_ids.top()] <= nums[cur_id]) {
            nearby_greater_or_eq[town_for_greater_or_eq_ids.top()] = cur_id;
            town_for_greater_or_eq_ids.pop();
        }
        town_for_greater_or_eq_ids.push(cur_id);
        ++cur_id;
    }
    nums.front() = nums.back() = -1;
    std::vector<std::uint32_t> nearby_smaller(N + 2);
    std::stack<std::uint32_t> towm_for_smaller_ids;
    towm_for_smaller_ids.push(0);
    cur_id = 1;
    while (towm_for_smaller_ids.size() != 2 || nums[towm_for_smaller_ids.top()] != -1) {
        while (!towm_for_smaller_ids.empty() && nums[towm_for_smaller_ids.top()] > nums[cur_id]) {
            nearby_smaller[towm_for_smaller_ids.top()] = cur_id;
            towm_for_smaller_ids.pop();
        }
        towm_for_smaller_ids.push(cur_id);
        ++cur_id;
    }
    std::uint32_t max_right = nearby_smaller[1] - 1, now_right = 1, res = 1;
    while (now_right != N + 1) {
        if (nearby_greater_or_eq[now_right] != N + 1 && max_right >= nearby_greater_or_eq[now_right]) {
            now_right = nearby_greater_or_eq[now_right];
        } else if (now_right == N) {
            break;
        } else {
            ++now_right;
            ++res;
            max_right = nearby_smaller[now_right] - 1;
        }
    }
    std::cout << res;
    return 0;
}