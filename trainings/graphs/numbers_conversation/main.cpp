#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>

struct Point {
    std::uint32_t path;
    std::int32_t nearest_number_to_beginning;
};

std::vector<std::uint32_t> MinimumActionConversation(std::uint32_t a, std::uint32_t b) {
    std::map<std::uint32_t, Point> numbers_map;
    std::set<std::uint32_t> visited_numbers;
    std::queue<std::uint32_t> numbers_queue;
    numbers_queue.push(a);
    numbers_map.insert({a, Point{0, -1}});
    while (!numbers_queue.empty()) {
        std::uint32_t cur_number = numbers_queue.front();
        numbers_queue.pop();
        if (visited_numbers.contains(cur_number)) continue;
        visited_numbers.insert(cur_number);
        if (cur_number == b) break;
        std::uint32_t first_conversation = (cur_number / 1000 < 9 ? cur_number + 1000 : 0);
        std::uint32_t second_conversation = (cur_number % 10 > 1 ? cur_number - 1 : 0);
        std::uint32_t third_conversation = (cur_number % 1000) * 10 + (cur_number / 1000);
        std::uint32_t fourth_conversation = (cur_number / 10) + (cur_number % 10) * 1000;
        auto this_it = numbers_map.find(cur_number);
        auto it_first_conversation = (first_conversation == 0 ? numbers_map.begin() : numbers_map.find(
                first_conversation));
        auto it_second_conversation = (second_conversation == 0 ? numbers_map.begin() : numbers_map.find(
                second_conversation));
        auto it_third_conversation = numbers_map.find(third_conversation);
        auto it_fourth_conversation = numbers_map.find(fourth_conversation);
        if (first_conversation != 0) {
            if (it_first_conversation == numbers_map.end() ||
                it_first_conversation->second.path > this_it->second.path + 1) {
                numbers_map.insert_or_assign(first_conversation,
                                             Point{this_it->second.path + 1, static_cast<std::int32_t>(cur_number)});
            }
        }
        if (second_conversation != 0) {
            if (it_second_conversation == numbers_map.end() ||
                it_second_conversation->second.path > this_it->second.path + 1) {
                numbers_map.insert_or_assign(second_conversation,
                                             Point{this_it->second.path + 1, static_cast<std::int32_t>(cur_number)});
            }
        }
        if (it_third_conversation == numbers_map.end() ||
            it_third_conversation->second.path > this_it->second.path + 1) {
            numbers_map.insert_or_assign(third_conversation,
                                         Point{this_it->second.path + 1, static_cast<std::int32_t>(cur_number)});
        }
        if (it_fourth_conversation == numbers_map.end() ||
            it_fourth_conversation->second.path > this_it->second.path + 1) {
            numbers_map.insert_or_assign(fourth_conversation,
                                         Point{this_it->second.path + 1, static_cast<std::int32_t>(cur_number)});
        }
        if (first_conversation != 0) numbers_queue.push(first_conversation);
        if (second_conversation != 0) numbers_queue.push(second_conversation);
        numbers_queue.push(third_conversation);
        numbers_queue.push(fourth_conversation);
    }
    std::vector<std::uint32_t> result;
    result.reserve(1000);
    auto number_it = numbers_map.find(b);
    while (number_it->second.nearest_number_to_beginning != -1) {
        result.push_back(number_it->first);
        number_it = numbers_map.find(number_it->second.nearest_number_to_beginning);
    }
    result.push_back(a);
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::uint32_t a, b;
    std::cin >> a >> b;
    auto result = MinimumActionConversation(a, b);
    for (const auto &res: result) std::cout << res << "\n";
    return 0;
}
