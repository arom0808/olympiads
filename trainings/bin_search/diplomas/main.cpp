#include <iostream>

std::uint32_t GetSquareSideSize(std::uint32_t w, std::uint32_t h, std::uint32_t n) {
    if (w > h) std::swap(w, h);
    std::uint32_t l = 0, r = h * n, middle = (r + l) / 2;
    while (l != r) {
        if ((middle / h) * (middle / w) < n) l = middle + 1;
        else r = middle;
        middle = (l + r) / 2;
    }
    return l;
}

int main() {
    std::uint32_t w, h, n;
    std::cin >> w >> h >> n;
    std::cout << GetSquareSideSize(w, h, n);
    return 0;
}
