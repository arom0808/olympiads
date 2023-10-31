#include <iostream>
#include <vector>
#include <algorithm>

struct Migrant {
    std::uint64_t a, b;

    explicit Migrant(std::uint64_t a = 0, std::uint64_t b = 0) : a(a), b(b) {}

    std::uint64_t dif() const { return (a >= b) ? (a - b) : (b - a); }
};

int main() {
    std::uint64_t t;
    std::cin >> t;
    for (std::uint64_t i = 0; i < t; ++i) {
        std::uint64_t n, m;
        std::cin >> n >> m;
        std::uint64_t free = m - n, sum = 0;
        std::vector<Migrant> as, bs;
        as.reserve(n);
        bs.reserve(n);
        for (std::uint64_t j = 0, a, b; j < n; ++j) {
            std::cin >> a >> b;
            if (a >= b) as.emplace_back(a, b);
            else bs.emplace_back(a, b);
        }
        auto min_dif_b = std::min_element(bs.begin(), bs.end(), [](const Migrant &a, const Migrant &b) {
            return a.dif() < b.dif();
        });
        if (as.size() > 1) for (const auto &aa: as) sum += aa.a;
        else if (!as.empty() && !bs.empty() && as.front().dif() > min_dif_b->dif()) {
            sum += as.front().a + min_dif_b->a;
            bs.erase(min_dif_b);
        } else for (const auto &aa: as) sum += aa.b;
        std::sort(bs.begin(), bs.end(), [](const Migrant &a, const Migrant &b) {
            return a.dif() < b.dif();
//            return a.b < b.b;
        });
        auto bit = bs.rbegin();
        for (std::uint64_t j = 0; j < free && bit != bs.rend(); ++j, ++bit) sum += bit->b;
        for (; bit != bs.rend(); ++bit) sum += bit->a;
        std::cout << sum << "\n";
    }
    return 0;
}
