#include <iostream>
#include <string>

int main() {
    std::string blocs;
    std::cin >> blocs;
    for (std::uint32_t now_vertical_start_x = 0, now_horizontal_start_x = 0, i = 0; i < blocs.size(); ++i) {
        if (blocs[i] == '0') {
            std::cout << 1 << " " << ++now_vertical_start_x << '\n';
            if (now_vertical_start_x > 3) now_vertical_start_x = 0;
        } else {
            std::cout << 3 << " " << now_horizontal_start_x + 1 << '\n';
            if (now_horizontal_start_x == 0) now_horizontal_start_x += 2;
            else now_horizontal_start_x = 0;
        }
    }
    return 0;
}
