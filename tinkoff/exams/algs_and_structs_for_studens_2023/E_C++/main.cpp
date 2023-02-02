#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    std::uint32_t n;
    std::cin >> n;
    if (n <= 3) {
        std::cout << "-1";
        return 0;
    }
    std::uint64_t sum = (1 + static_cast<std::uint64_t>(n)) * static_cast<std::uint64_t>(n) / 2;
    if (sum % 3 != 0) {
        std::cout << "-1";
        return 0;
    }
    std::set<std::set<std::uint32_t>> my_solution;
    std::set<std::uint32_t> _a{n - 1}, _b{n - 2}, _c{n};
    std::set<std::uint32_t> *a = &_a, *b = &_b, *c = &_c;
    std::uint32_t i = n - 3;
    while (i > 3) {
        a->insert(i--);
        b->insert(i--);
        c->insert(i--);
        std::swap(a, c);
    }
    b->insert(i--);
    a->insert(i--);
    if (i) c->insert(1);
    my_solution.clear();
    my_solution.insert(_a);
    my_solution.insert(_b);
    my_solution.insert(_c);
    for (const auto &group: my_solution) {
        std::cout << group.size() << std::endl;
        for (const auto &a: group) std::cout << a << " ";
        std::cout << std::endl << std::endl;
    }
    return 0;
}