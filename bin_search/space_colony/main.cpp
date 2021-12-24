#include <iostream>


static std::int64_t n, a, b, w, h;

std::int16_t func(const std::uint64_t &d) {
    std::uint64_t wa = w / (a + 2 * d), wb = w / (b + 2 * d), ha = h / (a + 2 * d), hb = h / (b + 2 * d);
    std::uint64_t max_c = std::max(wa * hb, ha * wb);
    if (max_c < n) {
        return -1;
    }
    std::uint64_t wa1 = w / (a + 2 * (d + 1)), wb1 = w / (b + 2 * (d + 1)), ha1 = h / (a + 2 * (d + 1)),
            hb1 = h / (b + 2 * (d + 1));
    std::uint64_t max_c1 = std::max(wa1 * hb1, ha1 * wb1);
    if (max_c1 < n) {
        return 0;
    }
    return 1;
}

int main() {
    std::cin >> n >> a >> b >> w >> h;
    std::uint64_t l = 0, r = 1e18, d = (l + r) / 2;
    while (l != r) {
        std::int16_t val = func(d);
        if (val > 0) {
            l = d + 1;
        } else if (val < 0) {
            r = d - 1;
        } else {
            l = d;
            r = d;
        }
        d = (l + r) / 2;
    }
    std::cout << d;
    return 0;
}
