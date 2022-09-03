#include <iostream>

void CoutBin(const std::string &prev_str, std::uint16_t N) {
    if (N > 0) {
        CoutBin(prev_str + '0', N - 1);
        CoutBin(prev_str + '1', N - 1);
    } else std::cout << prev_str << std::endl;
}

int main() {
    std::uint16_t N;
    std::cin >> N;
    CoutBin("", N);
    return 0;
}
