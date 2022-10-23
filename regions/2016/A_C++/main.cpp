#include <iostream>
#include <vector>

int main() {
    std::uint64_t n;
    std::cin >> n;
    std::vector<std::uint64_t> numbers(n);
    for (std::uint64_t i = 0; i < n; ++i) std::cin >> numbers[i];
    std::uint64_t max_number = std::max(numbers[0], numbers[1]);
    std::uint64_t pre_max_number = std::min(numbers[0], numbers[1]);
    for (std::uint64_t i = 1; i < n; ++i) {
        if (numbers[i] > max_number) {
            pre_max_number = max_number;
            max_number = numbers[i];
        } else if (numbers[i] == max_number) {
            pre_max_number = max_number;
        }
        std::cout << pre_max_number << ' ';
    }
    return 0;
}
