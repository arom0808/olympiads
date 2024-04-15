#include <iostream>

int main() {
    std::uint64_t n, a, b;
    std::cin >> n >> a >> b;
    std::cout << a * b / n + (a * b % n != 0);
    return 0;
}
