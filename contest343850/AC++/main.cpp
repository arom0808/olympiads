#include <iostream>
#include <vector>
#include <algorithm>

bool cmp(const std::pair<std::uint32_t, std::uint32_t> &a, const std::pair<std::uint32_t, std::uint32_t> &b) {
    return a.first < b.first;
}

int main() {
    std::vector<std::pair<std::vector<std::vector<std::uint32_t>>, std::int64_t>> input_data_sets;
    std::uint64_t temp_input;
    std::cin >> temp_input;
    input_data_sets.resize(temp_input);
    for (auto &input_data_set: input_data_sets) {
        input_data_set.second = -1;
        std::cin >> temp_input;
        input_data_set.first.resize(temp_input);
        for (auto &cave: input_data_set.first) {
            std::cin >> temp_input;
            cave.resize(temp_input);
            for (auto &monster: cave) {
                std::cin >> monster;
            }
        }
    }

    for (auto &input_data_set: input_data_sets) {
        std::vector<std::pair<std::uint32_t, std::uint32_t>> weights(input_data_set.first.size(),
                                                                     std::pair<std::uint32_t, std::uint32_t>(0, 0));
        for (std::size_t i = 0; i < weights.size(); ++i) {
            for (std::size_t j = 0; j < input_data_set.first[i].size(); ++j) {
                if (weights[i].first + j <= input_data_set.first[i][j]) {
                    weights[i].first += input_data_set.first[i][j] - (weights[i].first + j) + 1;
                }
            }
            weights[i].second = input_data_set.first[i].size();
        }
        std::sort(weights.begin(), weights.end(), cmp);
        std::uint32_t start_health = 0, getted_health = 0;
        for (auto &weight: weights) {
            if (start_health + getted_health <= weight.first) {
                start_health = weight.first - getted_health;
            }
            getted_health += weight.second;
        }
        input_data_set.second = start_health;
    }

    std::cout << input_data_sets[0].second;
    for (std::size_t i = 1; i < input_data_sets.size(); ++i)
        std::cout << std::endl << input_data_sets[i].second;
    return 0;
}
