#include <iostream>

int main() {
    std::uint64_t l, r, a;
    std::cin >> l >> r >> a;
    std::uint64_t res = 0;
    std::uint64_t i = l;
    if (r - i > a && (r - i) % a != 0) {
        res += ((r - i) % a) * ((r - i) / a);
        i += (r - i) % a;
    }
    while (r - i >= a) {
        res += r - i - a + 1;
        i += a;
    }
    if (r - i > 0) res += ((r - i) % a) * ((r - i) / a);
    std::cout << res;
    return 0;
}
