#include <iostream>
#include <vector>

void get_multipliers(std::uint64_t n, std::ostream &out) {
    out << n << "=";
    for (std::uint64_t i = 2; i * i <= n;) {
        if (n % i == 0) {
            out << i << "*";
            n /= i;
        } else ++i;
    }
    out << n;
}

int main() {
    std::uint64_t n;
    std::cin >> n;
    get_multipliers(n, std::cout);
    return 0;
}
