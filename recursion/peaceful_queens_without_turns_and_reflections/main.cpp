#include <iostream>
#include <set>
#include <algorithm>

std::set<std::set<std::pair<std::uint16_t, std::uint16_t>>> cacheMakedCombines{};

std::set<std::set<std::pair<std::uint16_t, std::uint16_t>>> makedCombines{};

bool IsIntersection(std::uint16_t x, std::uint16_t y, const std::pair<std::uint16_t, std::uint16_t> &point) {
    std::uint16_t dx = std::max(x, point.first) - std::min(x, point.first), dy =
            std::max(y, point.second) - std::min(y, point.second);
    return (dx == 0 || dy == 0 || dx == dy);
}

bool IsIntersectionVector(std::uint16_t x, std::uint16_t y,
                          const std::set<std::pair<std::uint16_t, std::uint16_t>> &positions) {
    return std::any_of(positions.begin(), positions.end(),
                       [&x, &y](const std::pair<std::uint16_t, std::uint16_t> &elem) {
                           return IsIntersection(x, y, elem);
                       });
}

void RecursiveCalculation(std::uint16_t N, std::set<std::pair<std::uint16_t, std::uint16_t>> &positions) {
    if (cacheMakedCombines.find(positions) != cacheMakedCombines.end())
        return;
    cacheMakedCombines.insert(positions);
    for (std::uint16_t i = 0; i < N; ++i) {
        for (std::uint16_t j = 0; j < N; ++j) {
            if (!IsIntersectionVector(i, j, positions)) {
                positions.emplace(i, j);
                if (positions.size() == N)
                    makedCombines.insert(positions);
                else
                    RecursiveCalculation(N, positions);
                positions.erase(std::pair<std::uint16_t, std::uint16_t>(i, j));
            }
        }
    }
}

bool IsTurnOrReflection(const std::set<std::pair<std::uint16_t, std::uint16_t>> &map1,
                        const std::set<std::pair<std::uint16_t, std::uint16_t>> &map2) {
    return map1.size() % 2;
}

std::uint16_t CalculateCount(std::uint16_t N) {
    std::set<std::pair<std::uint16_t, std::uint16_t>> positions{};
    RecursiveCalculation(N, positions);
    for (auto iti = makedCombines.begin(); iti != makedCombines.end();) {
        if (std::next(iti) == makedCombines.end())
            continue;
        for (auto itj = std::next(iti); itj != makedCombines.end();) {
            if (IsTurnOrReflection(*iti, *itj)) {
                makedCombines.erase(itj);
                iti = makedCombines.begin();
                continue;
            }
        }
        ++iti;
    }
    return makedCombines.size();
}

int main() {
    std::uint16_t N;
    std::cin >> N;
    std::cout << CalculateCount(N);
    return 0;
}
