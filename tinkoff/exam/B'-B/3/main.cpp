#include <iostream>
#include <vector>

void DecrementArray(std::vector<std::uint32_t> &numbers, std::uint32_t last_index, std::uint32_t number = 1) {
    std::uint32_t i = numbers.size();
    do {
        --i;
        numbers[i] -= number;
    } while (i > 0 && i > last_index);
}

bool IsSequence(const std::vector<std::uint32_t> &numbers) {
    std::uint32_t i = numbers.size();
    bool is_seq = false;
    do {
        --i;
        if (i == 0) {
            is_seq = true;
            break;
        } else if (numbers[i - 1] + 1 != numbers[i]) {
            break;
        }
    } while (true);
    return is_seq;
}

bool GetLooserIfSequence(std::uint32_t moves_count, bool player) {
    if (player) return !static_cast<bool>(moves_count % 2);
    else return static_cast<bool>(moves_count % 2);
}

bool GetLooser(std::vector<std::uint32_t> &numbers) {
    bool player = false;
    if (IsSequence(numbers))
        return GetLooserIfSequence(numbers[0], player);
    std::uint32_t i = numbers.size();
    do {
        --i;
        if (i == 0) {
            break;
        } else if (numbers[i - 1] + 1 != numbers[i]) {
            player = GetLooserIfSequence(numbers[i] - numbers[i - 1] - 1, player);
            DecrementArray(numbers, i, numbers[i] - numbers[i - 1] - 1);
        }
    } while (true);
    return GetLooserIfSequence(numbers[0], player);
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> numbers;
    numbers.reserve(n);
    for (std::uint32_t i = 0; i < n; ++i) {
        std::uint32_t temp;
        std::cin >> temp;
        numbers.push_back(temp);
    }
    auto looser = GetLooser(numbers);
    if (looser) std::cout << "Second";
    else std::cout << "First";
}
