#include <iostream>
#include <vector>

std::pair<std::uint32_t, std::uint32_t>
GetLeftAndRightNumber(const std::vector<std::uint32_t> &numbers, std::uint32_t request) {
    std::uint32_t l = 0, r = numbers.size() - 1, middle = (l + r) / 2;
    while (l != r) {
        if (numbers[middle] < request) l = middle + 1;
        else r = middle;
        middle = (l + r) / 2;
    }
    std::uint32_t left = (numbers[l] == request ? l + 1 : 0);
    l = 0;
    r = numbers.size() - 1;
    middle = (l + r) / 2;
    while (l != r) {
        if (numbers[middle] > request) r = middle - 1;
        else l = middle;
        middle = (l + r) / 2 + ((l + r) % 2);
    }
    std::uint32_t right = (numbers[l] == request ? l + 1 : 0);
    return {left, right};
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::uint32_t> numbers(N);
    for (auto &&number: numbers) std::cin >> number;
    std::uint32_t M;
    std::cin >> M;
    std::vector<std::uint32_t> requests(M);
    for (auto &&request: requests) std::cin >> request;
    for (const auto &request: requests) {
        auto result = GetLeftAndRightNumber(numbers, request);
        std::cout << result.first << " " << result.second << "\n";
    }
    return 0;
}
