#include <iostream>

int main() {
    std::uint64_t a, b, c, steps = 0;
    std::cin >> a >> b >> c;
    while (a < b) {
        a += 2;
        if (a % c == 0)
            --a;
        ++steps;
    }
    std::cout << steps;
    return 0;
}
