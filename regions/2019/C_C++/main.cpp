#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

std::vector<std::list<std::uint32_t>> card_out_id_on_value(3e5);

std::int32_t
FindNextCardOutId(std::uint32_t current_card_out_value) {
    card_out_id_on_value[current_card_out_value].pop_front();
    if (card_out_id_on_value[current_card_out_value].empty()) return -1;
    return static_cast<std::int32_t>(card_out_id_on_value[current_card_out_value].front());
}

std::vector<bool> is_number_exists(3e5, false);

std::uint32_t UniqueValuesCount(const std::vector<std::uint32_t> &cards_out_sequence, std::uint32_t first_card_out_id,
                                std::uint32_t last_card_out_id) {
    for (std::uint32_t i = first_card_out_id; i < last_card_out_id; ++i) is_number_exists[cards_out_sequence[i]] = true;
    std::uint32_t result = std::count_if(is_number_exists.begin(), is_number_exists.end(), [](bool a) { return a; });
    for (std::uint32_t i = first_card_out_id; i < last_card_out_id; ++i)
        is_number_exists[cards_out_sequence[i]] = false;
    return result;
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::uint32_t> results;
    results.reserve(6e5);
    std::vector<std::uint32_t> requests(m);
    for (auto &&request: requests) {
        std::cin >> request;
        --request;
    }
    std::list<std::uint32_t> cards(n);
    for (auto &&card: cards) {
        std::cin >> card;
        --card;
    }

    std::vector<std::uint32_t> cards_out_sequence;
    cards_out_sequence.reserve(6e5);
    std::vector<bool> is_cards_used(n);
    for (const auto &request: requests) {
        if (!is_cards_used[request]) {
            while (true) {
                std::uint32_t first_card = cards.front();
                cards_out_sequence.push_back(first_card);
                is_cards_used[first_card] = true;
                cards.pop_front();
                if (first_card == request) break;
            }
        } else {
            cards_out_sequence.push_back(request);
        }
    }
    for (std::uint32_t card_out_id = 0; card_out_id < cards_out_sequence.size(); ++card_out_id) {
        card_out_id_on_value[cards_out_sequence[card_out_id]].push_back(card_out_id);
    }
    for (std::uint32_t card_out_id = 0; card_out_id < cards_out_sequence.size(); ++card_out_id) {
        std::int32_t next_card_out_id = FindNextCardOutId(cards_out_sequence[card_out_id]);
        if (next_card_out_id == -1) results.push_back(n);
        else results.push_back(UniqueValuesCount(cards_out_sequence, card_out_id, next_card_out_id));
    }

    std::cout << results.size() << std::endl;
    for (const auto &result: results) std::cout << result << " ";
    return 0;
}
