#include <iostream>

int main() {
    std::uint32_t a, b;
    std::cin >> a >> b;
    for (std::uint32_t first_win = 0; first_win <= a / 10; ++first_win) {
        if ((a - (first_win * 10)) % 9 != 0) continue;
        if (b < first_win * 9) continue;
        if ((b - (first_win * 9)) % 10 != 0) continue;
        if ((a - (first_win * 10)) / 9 != (b - (first_win * 9)) / 10) continue;
        std::cout << first_win + (a - (first_win * 10)) / 9;
        return 0;
    }
    return 0;
}
