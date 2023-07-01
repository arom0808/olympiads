#include <iostream>
#include <vector>
#include <stack>

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::int32_t> towns(N + 2);
    towns.front() = towns.back() = -1;
    for (std::uint32_t i = 1; i <= N; ++i) std::cin >> towns[i];
    std::vector<std::int32_t> ans(N + 2);
    std::stack<std::uint32_t> town_ids;
    town_ids.push(0);
    std::uint32_t cur_id = 1;
    while (town_ids.size() != 2 || towns[town_ids.top()] != -1) {
        while (!town_ids.empty() && towns[town_ids.top()] > towns[cur_id]) {
            ans[town_ids.top()] = cur_id;
            town_ids.pop();
        }
        town_ids.push(cur_id);
        ++cur_id;
    }
    for (std::uint32_t i = 1; i <= N; ++i) std::cout << (ans[i] == N + 1 ? (-1) : ans[i] - 1) << " ";
    return 0;
}
