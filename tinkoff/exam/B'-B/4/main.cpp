#include <iostream>
#include <vector>

std::uint32_t
FastGcdOfMex(const std::vector<std::uint64_t> &numbers, const std::pair<std::uint32_t, std::uint32_t> &request) {
    if (request.first == request.second && numbers[request.first - 1] == 1) return 2;
    return 1;
}

std::vector<std::uint32_t> FastMethodResults(const std::vector<std::uint64_t> &numbers,
                                             const std::vector<std::pair<std::uint32_t, std::uint32_t>> &requests) {
    std::vector<std::uint32_t> results(requests.size());
    for (std::uint32_t i = 0; i < requests.size(); ++i) results[i] = FastGcdOfMex(numbers, requests[i]);
    return results;
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint64_t> numbers(n);
    for (auto &&number: numbers) std::cin >> number;
    std::uint32_t q;
    std::cin >> q;
    std::vector<std::pair<std::uint32_t, std::uint32_t>> requests(q);
    for (auto &&request: requests) std::cin >> request.first >> request.second;
    auto fast_method_results = FastMethodResults(numbers, requests);
    for (const auto &result: fast_method_results) std::cout << result << std::endl;
    return 0;
}