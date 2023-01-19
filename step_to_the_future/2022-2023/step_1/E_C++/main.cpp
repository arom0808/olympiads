#include <iostream>
#include <string>

int main() {
    std::uint32_t n, height = 2;
    std::uint64_t speed = 2;
    std::string buf_str;
    std::cin >> n;
    for (std::uint32_t i = 0; i < n; ++i) {
        std::cin >> buf_str;
        std::uint32_t str_digits_sum = 0;
        for (const auto &c: buf_str) {
            if (c >= '0' && c <= '9') str_digits_sum += c - '0';
            else str_digits_sum += c - 'A' + 10;
        }
        std::uint32_t cmd = str_digits_sum % 5;
        if (cmd == 1) speed *= 2;
        else if (cmd == 2) { if (speed > 1) speed /= 2; }
        else if (cmd == 3) { if (height < 4) ++height; }
        else if (cmd == 4) { if (height > 0) --height; }
    }
    std::cout << speed << " " << height;
    return 0;
}
