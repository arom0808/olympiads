#include <iostream>
#include <fstream>

std::uint32_t el_compos(std::uint64_t n) {
    std::uint32_t res = n % 10;
    while (n / 10 != 0) {
        n /= 10;
        res *= n % 10;
    }
    return res;
}

int main() {
    std::ofstream result("result.txt");
    for (std::uint64_t i = 1; i < 100; ++i) {
        for (std::uint64_t j = 1; j < 100; ++j) {
            if (i * j == el_compos(i) * el_compos(j)) {
                result << i << " " << j << std::endl;
                std::cout << i << " " << j << std::endl;
            }
        }
    }
    return 0;
}
