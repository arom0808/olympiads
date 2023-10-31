#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include <algorithm>

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::pair<std::uint32_t, bool>> students;
    for (std::uint32_t i = 0, x, s; i < n; ++i) {
        std::cin >> x >> s;
        students.emplace_back(x, s);
    }
    std::sort(students.begin(), students.end(),
              [](const std::pair<std::uint32_t, bool> &a, const std::pair<std::uint32_t, bool> &b) {
                  return a.first < b.first;
              });
    std::uint32_t R = std::numeric_limits<std::uint32_t>::max();
    for (auto a = students.begin(), b = std::next(a); b != students.end(); ++a, ++b)
        if (a->second != b->second && b->first - a->first <= R)
            R = b->first - a->first - 1;
    std::uint32_t res = (students.front().second ? 1 : 0);
    for (auto a = students.begin(), b = std::next(a); b != students.end(); ++a, ++b)
        if ((!a->second && b->second) || (a->second && b->second && b->first - a->first > R)) ++res;
    std::cout << res;
    return 0;
}
