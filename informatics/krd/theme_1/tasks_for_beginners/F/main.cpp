#include <iostream>

int main() {
    std::uint32_t x_1, y_1, x_2, y_2;
    std::cin >> x_1 >> y_1 >> x_2 >> y_2;
    if (y_2 > y_1) y_2 = 2 * y_1 - y_2;
    if (x_2 < x_1) x_2 = 2 * x_1 - x_2;
    if ((x_2 - x_1 == 1 && y_1 - y_2 == 2) || (x_2 - x_1 == 2 && y_1 - y_2 == 1)) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}
