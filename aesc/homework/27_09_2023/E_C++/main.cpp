#include <iostream>

int main() {
    std::uint64_t n;
    std::cin >> n;
    std::uint64_t res = 1;
    for (std::uint64_t i = 1; i <= n; ++i) {
        res *= i;
        while (res % 10 == 0) res /= 10;
        res %= 1000000;
        // By the way, I understand that normally I need to cycle through the numbers, find the first one from the end of 1, 3, 7 or 9 and save all the numbers after it, and it itself.
        // But the way I wrote it also works)
    }
    std::cout << res % 10;
    return 0;
}
