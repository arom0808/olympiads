#include <iostream>

void pereclast(std::uint16_t count, std::uint16_t from, std::uint16_t to, std::uint16_t buf) {
    if (count == 0)
        return;
    pereclast(count - 1, from, buf, to);
    std::cout << from << " " << to << std::endl;
    pereclast(count - 1, buf, to, from);
}

int main() {
    std::uint16_t N;
    std::cin >> N;
    pereclast(N, 1, 2, 3);
    return 0;
}
