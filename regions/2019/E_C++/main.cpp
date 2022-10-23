#include <iostream>

int main() {
    std::uint64_t a, b, c, steps = 0;
    std::cin >> a >> b >> c;
    std::uint64_t nearest_c = a / c * c + c;
    if (nearest_c < b) {
        steps += (nearest_c - a) / 2 + 1;
        a = nearest_c + 1;
    }
    std::uint64_t nearest_c_to_b = b / c * c;
    if (nearest_c_to_b > a - 1) {
        steps += ((c - 1) / 2 + 1) * ((nearest_c_to_b - a + 1) / c);
        a = nearest_c_to_b + 1;
    }
    steps += (b - a) / 2;
    if ((b - a) % 2 != 0) ++steps;
    std::cout << steps;
    return 0;
}
