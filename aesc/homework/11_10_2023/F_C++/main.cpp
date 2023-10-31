#include <iostream>

int main() {
    std::int32_t m, n;
    std::cin >> m >> n;
    std::cout << (m % n) * (n % m) + 1;
    return 0;
}
