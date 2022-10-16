#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

std::int32_t
FindCardNextUse(const std::vector<std::uint32_t> &requests, std::uint32_t current_request_id, std::uint32_t card) {
    for (std::uint32_t request_id = current_request_id + 1; request_id < requests.size(); ++request_id)
        if (requests[request_id] == card) return static_cast<std::int32_t>(request_id);
    return -1;
}

std::pair<std::list<std::uint32_t>::iterator, std::uint32_t>
MaxDistanceRequestCardId(const std::vector<std::uint32_t> &requests, std::uint32_t current_request_id,
                         std::uint32_t current_card_next_use_request_id, std::list<std::uint32_t> &cards) {
    auto max_result = cards.begin();
    std::uint32_t max_distance = 0;
    for (std::uint32_t request_id = current_request_id;
         request_id < current_card_next_use_request_id; ++request_id) {
        auto current_card_it = std::find_if(cards.begin(), cards.end(),
                                            [&requests, request_id](std::uint32_t current_card) {
                                                return requests[request_id] == current_card;
                                            });
        auto current_distance = std::distance(cards.begin(), current_card_it);
        if (current_distance > max_distance) {
            max_distance = current_distance;
            max_result = current_card_it;
        }
    }
    return {max_result, max_distance};
}


int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::uint32_t> results;
    results.reserve(1e5);
    std::vector<std::uint32_t> requests(m);
    for (auto &&request: requests) std::cin >> request;
    std::list<std::uint32_t> cards(n);
    for (auto &&card: cards) std::cin >> card;

    for (std::uint32_t current_request_id = 0; current_request_id < requests.size(); ++current_request_id) {
        while (*cards.begin() != requests[current_request_id]) {
            auto current_card_it = cards.begin();
            std::int32_t current_card_next_use_request_id =
                    FindCardNextUse(requests, current_request_id, *current_card_it);
            if (current_card_next_use_request_id == -1) {
                cards.splice(cards.end(), cards, current_card_it);
                results.push_back(n);
            } else {
                auto max_distance_request_card_id = MaxDistanceRequestCardId(requests, current_request_id,
                                                                             current_card_next_use_request_id, cards);
                cards.splice(std::next(max_distance_request_card_id.first), cards, current_card_it);
                results.push_back(max_distance_request_card_id.second + 1);
            }
        }
        auto current_card_it = cards.begin();
        std::int32_t current_card_next_use_request_id =
                FindCardNextUse(requests, current_request_id, *current_card_it);
        if (current_card_next_use_request_id == -1) {
            cards.splice(cards.end(), cards, current_card_it);
            results.push_back(n);
        } else {
            auto max_distance_request_card_id = MaxDistanceRequestCardId(requests, current_request_id,
                                                                         current_card_next_use_request_id, cards);
            cards.splice(std::next(max_distance_request_card_id.first), cards, current_card_it);
            results.push_back(max_distance_request_card_id.second + 1);
        }
    }
    std::cout << results.size() << std::endl;
    for (const auto &result: results) std::cout << result << " ";
    return 0;
}
