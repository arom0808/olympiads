#include <iostream>

int main() {
    std::uint32_t n, m, k;
    std::cin >> n >> m >> k;
    if ((k % n == 0 || k % m == 0) && n * m >= k) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}
