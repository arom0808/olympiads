#include <iostream>
#include <set>

std::uint32_t gcd(std::uint32_t a, std::uint32_t b) {
    while (b > 0) {
        std::uint32_t tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

void sort(std::uint32_t &a, std::uint32_t &b, std::uint32_t &c) {
    if (a > b) std::swap(a, b);
    if (b > c) std::swap(b, c);
    if (a > b) std::swap(a, b);
}


int main() {
    std::set<std::set<std::uint32_t>> cnts;
    for (std::uint32_t x = 1; x < 100; ++x) {
        for (std::uint32_t y = 0; y < 100; ++y) {
            for (std::uint32_t z = 0; z < 100; ++z) {
                std::uint32_t ss = gcd(gcd(x, y), z);
                auto x1 = x / ss, y1 = y / ss, z1 = z / ss;
                sort(x1, y1, z1);
                if (x1 * (x1 + y1 + z1) == y1 * z1) cnts.insert(std::set<std::uint32_t>{x1, y1, z1});
            }
        }
    }
    for (const auto &l: cnts) {
        for (auto s: l) std::cout << s << " ";
        std::cout << "\n";
    }
    return 0;
}
