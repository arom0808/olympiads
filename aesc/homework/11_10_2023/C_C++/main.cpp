#include <iostream>

inline std::int32_t my_abs(std::int32_t num) {
    return static_cast<std::int32_t>((1 - ((*reinterpret_cast<std::uint32_t *>(&num)) / 2147483648)) * 2 - 1) * num;
}

int main() {
//    std::int32_t k;
//    std::cin >> k;
//    std::cout << my_abs(k);
    std::int32_t aa = -222;
    return 0;
}
