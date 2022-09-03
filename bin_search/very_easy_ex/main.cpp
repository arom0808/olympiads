#include<iostream>

std::uint32_t CopiesCount(std::uint32_t seconds, std::uint32_t x, std::uint32_t y) {
    std::uint32_t cnt = 0;
    if (seconds >= y) {
        seconds -= y;
        cnt += 1;
    }
    return cnt + seconds / x + seconds / y;
}

int main() {
    std::uint32_t N, x, y;
    std::cin >> N >> x >> y;
    if (x < y)
        std::swap(x, y);
    std::uint32_t min = 0, max = N * y;
    while (max - min > 1) {
        auto middle = (min + max) / 2;
        auto value = CopiesCount(middle, x, y);
        if (value < N)
            min = middle;
        else if (value >= N)
            max = middle;
    }
    std::cout << max;
    return 0;
}