#include <iostream>


inline std::int32_t my_abs(std::int32_t num) {
    return static_cast<std::int32_t>((1 - ((*reinterpret_cast<std::uint32_t *>(&num)) / 2147483648)) * 2 - 1) * num;
}

int main() {
    std::int32_t m, n;
    std::cin >> m >> n;
    std::cout << (m - n) - my_abs(m - n) + 1;
    return 0;
}
