#include <iostream>

int main() {
    std::uint64_t n, k, step = 0;
    std::cin >> n >> k;
    while (n >= k) {
        if (n % k == 0) {
            std::cout << step + 1;
            return 0;
        }
        n -= n / k;
        ++step;
    }
    std::cout << 0;
    return 0;
}
