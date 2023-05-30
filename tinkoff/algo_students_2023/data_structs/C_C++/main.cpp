#include <iostream>
#include <queue>
#include <stack>
#include <deque>

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::deque<std::pair<bool, std::uint32_t>> actions;
    std::queue<std::uint32_t> first_way;
    std::stack<std::uint32_t> middle;
    std::uint32_t next_to_second_way = 0;
    std::uint32_t input_cnt = 0;
    std::uint32_t temp;
    while (next_to_second_way < N) {
        if (!middle.empty() && middle.top() == next_to_second_way) {
            if (!actions.empty() && actions.back().first) ++actions.back().second;
            else actions.emplace_back(true, 1);
            ++next_to_second_way;
            middle.pop();
        } else {
            if (input_cnt < N) {
                std::cin >> temp;
                --temp;
                ++input_cnt;
                if (temp == next_to_second_way) {
                    if (!actions.empty() && !actions.back().first) ++actions.back().second;
                    else actions.emplace_back(false, 1);
                    actions.emplace_back(true, 1);
                    ++next_to_second_way;
                } else {
                    if (!actions.empty() && !actions.back().first) ++actions.back().second;
                    else actions.emplace_back(false, 1);
                    middle.push(temp);
                }
            } else {
                std::cout << 0;
                return 0;
            }
        }
    }
    std::cout << actions.size() << "\n";
    for (const auto &action: actions) std::cout << (action.first ? 2 : 1) << " " << action.second << "\n";
    return 0;
}
