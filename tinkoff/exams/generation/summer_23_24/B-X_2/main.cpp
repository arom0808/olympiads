#include <iostream>
#include <list>
#include <map>

//namespace Rand {
//    std::random_device dev;
//    std::mt19937 rng(dev());
//
//    std::uint32_t igen(std::uint32_t min, std::uint32_t max) {
//        return std::uniform_int_distribution(min, max)(rng);
//    }
//
//    bool bgen() { return std::bernoulli_distribution(0.5)(rng); }
//}
//
//std::pair<std::uint32_t, std::uint32_t> GoodSol(const std::map<std::uint32_t, bool> &raw_points) {
//    std::list<std::pair<bool, bool>> points;
//    for (const auto &[x, c]: raw_points) points.emplace_back(c, false);
//    std::uint32_t iterations = 0;
//    while (true) {
//        for (auto it = points.begin(); it != points.end(); ++it) {
//            if (it != points.begin() && std::prev(it)->first != it->first) it->second = true;
//            if (std::next(it) != points.end() && std::next(it)->first != it->first) it->second = true;
//        }
//        bool deleted = false;
//        for (auto it = points.begin(); it != points.end();) {
//            if (it->second) {
//                points.erase(std::prev(++it));
//                deleted = true;
//            } else ++it;
//        }
//        if (deleted) ++iterations;
//        else break;
//    }
//    if (points.empty()) return {0, iterations};
//    else if (points.front().first) return {1, iterations};
//    else return {2, iterations};
//}

std::pair<std::uint32_t, std::uint32_t> MySol(const std::map<std::uint32_t, bool> &raw_points) {
    std::list<std::pair<bool, std::int32_t>> points;
    for (const auto &[x, c]: raw_points) {
        if (points.empty() || points.back().first != c) points.emplace_back(c, 1);
        else ++points.back().second;
    }
    std::uint32_t iterations = 0;
    while (true) {
        bool deleted = false;
        for (auto it = points.begin(); it != points.end(); ++it) {
            if (it != points.begin() && std::prev(it)->first != it->first) {
                --it->second;
                deleted = true;
            }
            if (std::next(it) != points.end() && std::next(it)->first != it->first) {
                --it->second;
                deleted = true;
            }
        }
        for (auto it = points.begin(); it != points.end();) {
            if (it->second <= 0) {
                points.erase(std::prev(++it));
                if (it != points.begin() && it != points.end() && it->second > 0 && std::prev(it)->first == it->first) {
                    it->second += std::prev(it)->second;
                    points.erase(std::prev(it));
                }
            } else ++it;
        }
        if (deleted) ++iterations;
        else break;
    }
    if (points.empty()) return {0, iterations};
    else if (points.front().first) return {1, iterations};
    else return {2, iterations};
}

//void GenerateInput(std::map<std::uint32_t, bool> &raw_points) {
//    raw_points.clear();
//    std::uint32_t len = Rand::igen(5, 100);
//    while (raw_points.size() != len)
//        raw_points.emplace(Rand::igen(0, 100000), Rand::bgen());
//}

void Input(std::map<std::uint32_t, bool> &raw_points) {
    raw_points.clear();
    std::uint32_t N, x;
    bool c;
    std::cin >> N;
    for (std::uint32_t i = 0; i < N; ++i) {
        std::cin >> x >> c;
        raw_points.emplace(x, c);
    }
}

int main() {
    std::map<std::uint32_t, bool> raw_points;
    Input(raw_points);
    auto sol = MySol(raw_points);
    if (sol.first == 0) std::cout << "Draw " << sol.second;
    else if (sol.first == 1) std::cout << "Black " << sol.second;
    else std::cout << "White " << sol.second;
    return 0;
}
