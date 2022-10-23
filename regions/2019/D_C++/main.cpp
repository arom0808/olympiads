#include <iostream>
#include <vector>

std::uint32_t NumberDigitsCount(std::uint64_t number) {
    std::uint32_t result = 0;
    while (number != 0) {
        ++result;
        number /= 2;
    }
    return result;
}

int main() {
    std::uint64_t n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::pair<std::uint32_t, std::uint32_t>> not_equals(m);
    for (auto &&not_equal: not_equals) std::cin >> not_equal.first >> not_equal.second;
    std::uint32_t digits_count = NumberDigitsCount(k);
    std::uint32_t last_ones_count = 0;
    return 0;
}
