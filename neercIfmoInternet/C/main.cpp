#include <iostream>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::uint32_t x = n / 2, y = n / 2;
    std::uint8_t h, v;
    std::string tmp_input;
    std::uint32_t lh = 0, rh = n, lv = 0, rv = n;
    while (true) {
        x = (lh + rh) / 2;
        y = (lv + rv) / 2;
        std::cout << x << ' ' << y << std::endl;
        std::cout.flush();
        std::cin >> tmp_input;
        if (tmp_input == "OK")
            return 0;
        if (tmp_input.find_first_of('N') != -1) v = 'u';
        else if (tmp_input.find_first_of('S') != -1) v = 'd';
        else v = 'm';
        if (tmp_input.find_first_of('W') != -1) h = 'l';
        else if (tmp_input.find_first_of('E') != -1) h = 'r';
        else h = 'm';
        if (h == 'r') {
            lh = x + 1;
        } else if (h == 'l') {
            rh = x - 1;
        } else {
            lh = x;
            rh = x;
        }
        if (v == 'd') {
            lv = y + 1;
        } else if (v == 'u') {
            rv = y - 1;
        } else {
            lv = y;
            rv = y;
        }
    }
    return 0;
}
