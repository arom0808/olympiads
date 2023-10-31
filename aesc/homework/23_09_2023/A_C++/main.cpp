#include <iostream>

std::uint64_t pow_mod(std::uint64_t x, std::uint64_t n, std::uint64_t p) {
    std::uint64_t res = 1 % p;
    for (std::uint64_t t_p = x % p; n != 0; n /= 2, t_p = (t_p * t_p) % p)
        if (n % 2 == 1)
            res = (res * t_p) % p;
    return res;
}

int main() {
    std::uint64_t x, n, p;
    std::cin >> x >> n >> p;
    std::cout << pow_mod(x, n, p);
    return 0;
}