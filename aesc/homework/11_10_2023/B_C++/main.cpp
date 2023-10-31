#include <iostream>

int main() {
    std::uint32_t k, n;
    std::cin >> k >> n;
    std::cout << (n - 1) / k + 1 << " " << (n - 1) % k + 1;
    return 0;
}
