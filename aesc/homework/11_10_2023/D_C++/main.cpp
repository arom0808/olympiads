#include <iostream>

int main() {
    std::int32_t k;
    std::cin >> k;
    std::cout << k / 1000 * 10 - k % 10 * 10 + k % 1000 / 100 - k % 100 / 10 + 1;
    return 0;
}
