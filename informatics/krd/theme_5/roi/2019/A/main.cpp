#include <iostream>

int main() {
    std::uint32_t l, r, a;
    std::cin >> l >> r >> a;
    std::uint32_t main_length = r - l;
    std::uint32_t max_a_count = main_length / a;
    if (max_a_count == 0) {
        std::cout << 0;
        return 0;
    }
    std::uint32_t result = 0;
    for (std::uint32_t a_count = 1; a_count <= max_a_count; ++a_count)
        result += main_length - a_count * a + 1;
    std::cout << result;
    return 0;
}
