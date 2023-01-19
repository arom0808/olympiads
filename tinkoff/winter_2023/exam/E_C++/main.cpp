#include <iostream>
#include <vector>

std::uint32_t GetAnswer(const std::vector<std::int32_t> &numbers) {
    std::vector<std::uint32_t> jokes_start_here_count(numbers.size(), 0);
    for (auto i = static_cast<std::int32_t>(numbers.size()) - 1; i >= 0; --i) {
        if (numbers[i] < 1) continue;
        std::uint32_t right_elements_count = numbers.size() - 1 - i;
        if (right_elements_count >= numbers[i]) {

        }
    }
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::int32_t> numbers(n);
    for (auto &&x: numbers) std::cin >> x;
    std::cout << GetAnswer(numbers);
    return 0;
}
