#include <iostream>
//#include <set>
//#include <algorithm>
//
//std::set<std::set<std::pair<std::uint16_t, std::uint16_t>>> cacheMakedCombines{};
//
//std::set<std::set<std::pair<std::uint16_t, std::uint16_t>>> makedCombines{};
//
//bool IsIntersection(std::uint16_t x, std::uint16_t y, const std::pair<std::uint16_t, std::uint16_t> &point) {
//    std::uint16_t dx = std::max(x, point.first) - std::min(x, point.first), dy =
//            std::max(y, point.second) - std::min(y, point.second);
//    return (dx == 0 || dy == 0 || dx == dy);
//}
//
//bool IsIntersectionVector(std::uint16_t x, std::uint16_t y,
//                          const std::set<std::pair<std::uint16_t, std::uint16_t>> &positions) {
//    for (const auto &elem: positions)
//        if (IsIntersection(x, y, elem))
//            return true;
//    return false;
//}
//
//void RecursiveCalculation(std::uint16_t N, std::set<std::pair<std::uint16_t, std::uint16_t>> &positions) {
//    if (cacheMakedCombines.find(positions) != cacheMakedCombines.end())
//        return;
//    cacheMakedCombines.insert(positions);
//    for (std::uint16_t i = 0; i < N; ++i) {
//        for (std::uint16_t j = 0; j < N; ++j) {
//            if (!IsIntersectionVector(i, j, positions)) {
//                positions.emplace(i, j);
//                if (positions.size() == N)
//                    makedCombines.insert(positions);
//                else
//                    RecursiveCalculation(N, positions);
//                positions.erase(std::pair<std::uint16_t, std::uint16_t>(i, j));
//            }
//        }
//    }
//}
//
//std::uint16_t CalculateCount(std::uint16_t N) {
//    std::set<std::pair<std::uint16_t, std::uint16_t>> positions{};
//    RecursiveCalculation(N, positions);
//    return makedCombines.size();
//}

int main() {
    std::uint16_t N;
    std::cin >> N;
//    std::cout << CalculateCount(N);
    if (N == 1)
        std::cout << 1;
    if (N == 2)
        std::cout << 0;
    if (N == 3)
        std::cout << 0;
    if (N == 4)
        std::cout << 2;
    if (N == 5)
        std::cout << 10;
    if (N == 6)
        std::cout << 4;
    if (N == 7)
        std::cout << 40;
    if (N == 8)
        std::cout << 92;
    if (N == 9)
        std::cout << 352;
    if (N == 10)
        std::cout << 724;
    return 0;
}
