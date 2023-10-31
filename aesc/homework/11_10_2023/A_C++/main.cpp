#include <iostream>

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::cout << (n + m - 2) % 7 + 1;
    return 0;
}
