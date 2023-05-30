#include <iostream>
#include <vector>
#include <deque>

struct Sost {
    std::uint32_t x, y, m;

    explicit Sost(std::uint32_t x, std::uint32_t y, std::uint32_t m) : x(x), y(y), m(m) {}
};

std::uint32_t GetRes(std::uint32_t a, std::uint32_t b) {
    std::deque<Sost> _sost1, _sost2;
    std::deque<Sost> &sost_now = _sost1, &sost_new = _sost2;
    std::uint32_t act_num = 0;
    sost_now.emplace_back(0, 0, 1);
    while (true) {
        for (const auto &s: sost_now) {
            if (s.x == a && s.y == b) return act_num;
            if (s.x + s.m <= a) sost_new.emplace_back(s.x + s.m, s.y, s.m);
            if (s.y + s.m <= b) sost_new.emplace_back(s.x, s.y + s.m, s.m);
            if ((s.x + s.m + 1 <= a || s.x == a) && (s.y + s.m + 1 <= b || s.y == b))
                sost_new.emplace_back(s.x, s.y, s.m + 1);
        }
        sost_now.clear();
        std::swap(sost_now, sost_new);
        ++act_num;
    }
}

int main() {
    std::uint32_t t;
    std::cin >> t;
    std::vector<std::uint32_t> results(t);
    std::uint32_t a, b;
    for (auto &&res: results) {
        std::cin >> a >> b;
        res = GetRes(a, b);
    }
    for (const auto &res: results) std::cout << res << "\n";
    return 0;
}
