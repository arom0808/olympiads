#include <iostream>
#include <vector>

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::uint32_t> chars_counts(26);
    std::string str;
    std::cin >> str;
    for (const auto &c: str) ++chars_counts[c - 'A'];
    for (std::uint32_t i = 0; i < 26; ++i)
        for (std::uint32_t j = 0; j < chars_counts[i] / 2; ++j)
            std::cout << static_cast<char>(static_cast<std::uint32_t>('A') + i);
    for (std::uint32_t i = 0; i < 26; ++i) {
        if (chars_counts[i] % 2 != 0) {
            std::cout << static_cast<char>(static_cast<std::uint32_t>('A') + i);
            break;
        }
    }
    for (std::int32_t i = 25; i >= 0; --i)
        for (std::uint32_t j = 0; j < chars_counts[i] / 2; ++j)
            std::cout << static_cast<char>(static_cast<std::uint32_t>('A') + i);
    return 0;
}
