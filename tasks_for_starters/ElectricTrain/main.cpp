#include <iostream>

int main() {
    std::uint16_t i, j;
    std::cin >> i >> j;
    if (i == j)
        std::cout << 0;
    else
        std::cout << i + j - 1;
    return 0;
}
