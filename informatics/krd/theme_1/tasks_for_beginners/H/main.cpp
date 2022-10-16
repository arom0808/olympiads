#include <iostream>

int main() {
    std::uint32_t k;
    std::cin >> k;
    if (k == 1 || k == 4 || (k + 4) % 4 == 0) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}
