#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <fstream>
#include <list>
#include <map>

namespace Random {
    std::random_device dev;
    std::uint32_t seed = dev();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<std::uint16_t> dist_all_points(0, 311);

    std::uint16_t GetOneOfAll() { return dist_all_points(rng); }
}

struct OneSol {
    std::vector<std::uint16_t> order_of_points;
    std::uint32_t distance;

    friend void swap(OneSol &a, OneSol &b) {
        using std::swap;
        swap(a.order_of_points, b.order_of_points);
        swap(a.distance, b.distance);
    }

    bool operator<(const OneSol &other) const { return distance < other.distance; }

    OneSol(const OneSol &other) = default;

    OneSol &operator=(const OneSol &other) {
        order_of_points.resize(other.order_of_points.size());
        std::copy(other.order_of_points.begin(), other.order_of_points.end(), order_of_points.begin());
        distance = other.distance;
        return *this;
    }

    OneSol(OneSol &&other) noexcept: order_of_points(std::move(other.order_of_points)),
                                     distance(other.distance) {}

    OneSol(std::uint32_t N, const std::vector<std::vector<std::uint16_t>> &lengths) : order_of_points(N), distance(0) {
        std::iota(order_of_points.begin(), order_of_points.end(), 0);
        for (auto it = order_of_points.begin(); std::next(it) != order_of_points.end(); ++it)
            distance += lengths[*it][*std::next(it)];
    }
};

void MiniChange(OneSol &sol, const std::vector<std::vector<std::uint16_t>> &lengths) {
    std::uint32_t first = Random::GetOneOfAll(), second = Random::GetOneOfAll();
    while (first == second) {
        first = Random::GetOneOfAll();
        second = Random::GetOneOfAll();
    }
    if (first > second) std::swap(first, second);
    if (first != 0) sol.distance -= lengths[sol.order_of_points[first - 1]][sol.order_of_points[first]];
    sol.distance -= lengths[sol.order_of_points[first]][sol.order_of_points[first + 1]];
    if (second != lengths.size() - 1)
        sol.distance -= lengths[sol.order_of_points[second]][sol.order_of_points[second + 1]];
    sol.distance -= lengths[sol.order_of_points[second - 1]][sol.order_of_points[second]];
    std::swap(sol.order_of_points[first], sol.order_of_points[second]);
    if (first != 0) sol.distance += lengths[sol.order_of_points[first - 1]][sol.order_of_points[first]];
    sol.distance += lengths[sol.order_of_points[first]][sol.order_of_points[first + 1]];
    if (second != lengths.size() - 1)
        sol.distance += lengths[sol.order_of_points[second]][sol.order_of_points[second + 1]];
    sol.distance += lengths[sol.order_of_points[second - 1]][sol.order_of_points[second]];
}

std::pair<std::vector<std::uint16_t>, std::uint32_t> GetResult() {
    std::vector<std::vector<std::uint16_t>> lengths(312, std::vector<std::uint16_t>(312));
    std::ifstream in_file("usca312_dist.txt");
    for (auto &&row: lengths) for (auto &&length: row) in_file >> length;
    in_file.close();
    std::vector<OneSol> solutions(165, OneSol(312, lengths));
    for (std::uint32_t ops = 0; ops < 1000000; ++ops) {
        std::cout << ops << "\n";
        for (std::uint32_t i = 0; i < 15; ++i) {
            for (std::uint32_t j = 15 + i * 10; j < 15 + (i + 1) * 10; ++j) {
                solutions[j] = solutions[i];
                MiniChange(solutions[j], lengths);
            }
        }
        std::nth_element(solutions.begin(), std::next(solutions.begin(), 15), solutions.end());
    }
    std::sort(solutions.begin(), std::next(solutions.begin(), 15));
    return {solutions.front().order_of_points, solutions.front().distance};
}

int main() {
//    auto res = GetResult();
//    std::ofstream out_f("out.txt");
//    for (const auto &r: res.first) out_f << r << " ";
//    out_f << "\n" << res.second << "\n";
    std::vector<std::uint16_t> rr{78, 269, 91, 166, 69, 89, 7, 182, 4, 58, 105, 189, 71, 51, 302, 144, 206, 204, 14,
                                  284, 250, 258, 62, 133, 132, 280, 235, 73, 56, 106, 117, 43, 32, 202, 257, 107, 196,
                                  23, 136, 288, 271, 222, 281, 226, 181, 40, 5, 197, 216, 128, 140, 115, 200, 266, 296,
                                  139, 31, 195, 123, 48, 223, 275, 153, 34, 174, 121, 29, 125, 68, 96, 187, 286, 94,
                                  194, 274, 233, 246, 295, 163, 242, 135, 291, 0, 83, 310, 239, 152, 192, 47, 218, 186,
                                  236, 210, 104, 61, 211, 101, 198, 285, 245, 6, 84, 263, 72, 50, 287, 88, 191, 67, 142,
                                  237, 15, 155, 3, 92, 238, 243, 118, 119, 147, 76, 299, 161, 99, 11, 249, 126, 100,
                                  273, 261, 294, 165, 232, 221, 77, 157, 164, 213, 134, 57, 103, 231, 150, 276, 255, 19,
                                  179, 111, 27, 167, 55, 138, 303, 75, 113, 59, 146, 9, 109, 259, 53, 305, 12, 176, 193,
                                  298, 265, 38, 306, 154, 158, 66, 37, 2, 201, 262, 116, 177, 162, 28, 41, 277, 304, 35,
                                  44, 251, 272, 307, 292, 256, 188, 230, 129, 159, 120, 102, 203, 22, 175, 169, 64, 156,
                                  13, 63, 214, 207, 183, 79, 108, 220, 52, 10, 279, 8, 124, 141, 20, 131, 95, 148, 1,
                                  46, 309, 18, 97, 168, 54, 112, 228, 283, 278, 160, 145, 260, 87, 224, 267, 25, 185,
                                  240, 241, 244, 98, 16, 143, 149, 74, 300, 178, 209, 45, 33, 39, 90, 49, 180, 127, 82,
                                  282, 301, 17, 293, 219, 85, 114, 110, 137, 36, 151, 60, 311, 65, 264, 70, 122, 173,
                                  93, 268, 184, 171, 253, 170, 42, 190, 21, 225, 252, 80, 30, 24, 289, 290, 205, 234,
                                  86, 208, 130, 297, 308, 81, 247, 217, 172, 26, 254, 215, 199, 227, 248, 212, 270,
                                  229};
    for (auto &&r: rr) std::cout << r + 1 << " ";
    return 0;
}
