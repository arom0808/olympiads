#include <iostream>
#include <set>
#include <vector>

struct Pair {
    std::uint32_t a, b;

    bool operator==(const Pair &other) const { return a == other.a; }

    bool operator>(const Pair &other) const { return a > other.a; }

    bool operator<(const Pair &other) const { return a < other.a; }

    Pair(std::uint32_t a, std::uint32_t b) : a(a), b(b) {}
};

int main() {
    std::set<Pair> pairs;
    std::uint32_t n;
    std::cin >> n;
    std::vector<bool> is_first(n, true);
    for (std::uint32_t i = 0; i < n - 1; ++i) {
        std::uint32_t cur_a, cur_b;
        std::cin >> cur_a >> cur_b;
        pairs.emplace(cur_a - 1, cur_b - 1);
        is_first[cur_b - 1] = false;
    }
    std::uint32_t first_num;
    for (std::uint32_t i = 0; i < n; ++i) {
        if (is_first[i]) {
            first_num = i;
            break;
        }
    }
    std::uint32_t cur_num = first_num;
    std::cout << cur_num + 1 << " ";
    for (std::uint32_t printed = 1; printed < n; ++printed) {
        auto it = pairs.find(Pair(cur_num, 0));
        std::cout << (it->b + 1) << " ";
        cur_num = it->b;
    }
    return 0;
}
