#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

std::uint64_t ProgressiveSum(std::uint64_t n) {
    return (1 + n) * n / 2;
}

struct Solution {
    std::set<std::set<std::uint32_t>> groups;

    bool operator<(const Solution &other) const {
        return groups < other.groups;
    }
};

void MySolution(std::uint32_t n, Solution &solution) {
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
    solution.groups.clear();
    solution.groups.insert(_a);
    solution.groups.insert(_b);
    solution.groups.insert(_c);
}

int main() {
    std::uint32_t n;
    std::cin >> n;
    if (n <= 3) {
        std::cout << "-1";
        return 0;
    }
    std::uint64_t sum = ProgressiveSum(n);
    if (sum % 3 != 0) {
        std::cout << "-1";
        return 0;
    }
    Solution my_solution;
    MySolution(n, my_solution);
    for (const auto &group: my_solution.groups) {
        std::cout << group.size() << std::endl;
        for (const auto &a: group) std::cout << a << " ";
        std::cout << std::endl << std::endl;
    }
    return 0;
}