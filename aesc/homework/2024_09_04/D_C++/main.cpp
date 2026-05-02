#include <iostream>
#include <cstdint>

int64_t p;

int64_t pow(int64_t x, int64_t n) {
    if (n == 0) return 1 % p;
    return pow(x * x % p, n / 2) * (n % 2 == 0 ? 1 : x) % p;
}

int main() {
    int64_t x, n;
    std::cin >> x >> n >> p;
    std::cout << pow(x, n);
    return 0;
}
