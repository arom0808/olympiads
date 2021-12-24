#include <iostream>

std::uint64_t BinSearchProcess(std::uint64_t N, std::uint64_t x, std::uint64_t y) {
    if (x > y)
        std::swap(x, y);
    std::uint64_t l = 0, r = x * N;
    while (l != r) {
        std::uint64_t m = l + (r - l) / 2;
        std::uint64_t cp_cnt = m / x + (m - x) / y;
        if (cp_cnt < N)
            l = m + 1;
        else if (cp_cnt > N)
            r = m;
        else
            l = r = m;
    }
    return l;
}

int main() {
    std::uint64_t N, x, y;
    std::cin >> N >> x >> y;
    std::cout << BinSearchProcess(N, x, y);
    return 0;
}
