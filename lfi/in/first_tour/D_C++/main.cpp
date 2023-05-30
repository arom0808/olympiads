#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>
#include <list>
#include <set>
#include <cmath>
#include <unordered_set>

struct TwoDVector {
public:
    std::int16_t x, y;

    bool operator<(const TwoDVector &other) const {
        if (x < other.x) return true;
        if (x == other.x) if (y < other.y) return true;
        return false;
    }

    TwoDVector operator-(const TwoDVector &other) const {
        return {static_cast<int16_t>(x - other.x), static_cast<int16_t>(y - other.y)};
    }

    std::int16_t operator*(const TwoDVector &other) const {
        return x * other.x + y * other.y;
    }

    TwoDVector() : x(0), y(0) {}

    TwoDVector(std::int16_t x, std::int16_t y) : x(x), y(y) {}
};

void AddToRegionsMap(std::unordered_map<std::int16_t, std::unordered_set<std::int16_t>> &regions_map, std::int16_t x,
                     std::int16_t y) {
    auto it = regions_map.find(x);
    if (it == regions_map.end()) it = regions_map.emplace(x, std::unordered_set<std::int16_t>{}).first;
    it->second.insert(y);
}

void AddToRegionsExists(std::vector<std::vector<bool>> &regions_exists, std::int16_t x, std::int16_t y) {
    regions_exists[x + 100][y + 100] = true;
}

std::uint64_t HashOfSet(const std::set<TwoDVector> &s) {
    std::size_t seed = s.size();
    for (auto x_y: s) {
        std::uint32_t x = x_y.x;
        x <<= 16;
        x |= x_y.y;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

void EnumerationFirstThree(std::set<TwoDVector> &now_coords, const std::vector<TwoDVector> &all_coords,
                           std::unordered_set<std::uint64_t> &visited,
                           const std::function<void(const std::set<TwoDVector> &)> &callback) {
    if (now_coords.size() == 3) {
        auto hash = HashOfSet(now_coords);
        if (visited.find(hash) != visited.end()) return;
        visited.insert(hash);
        callback(now_coords);
    } else {
        for (auto &coord: all_coords) {
            if (now_coords.find(coord) != now_coords.end()) continue;
            now_coords.insert(coord);
            EnumerationFirstThree(now_coords, all_coords, visited, callback);
            now_coords.erase(coord);
        }
    }
}

class Geom {
public:
    static double GetDist(TwoDVector p1, TwoDVector p2) {
        return std::sqrt(static_cast<double>((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
    }
};

double approx_exp = 0.00001;

bool IsApproxEqual(double a, double b) {
    return (a - b) < approx_exp;
}

int main() {
    std::uint16_t n;
    std::cin >> n;
    std::vector<TwoDVector> all_coords(n);
    std::unordered_map<std::int16_t, std::unordered_set<std::int16_t>> regions_map;
    std::vector<std::vector<bool>> regions_exists(201, std::vector<bool>(201, false));
    std::int16_t temp_x, temp_y;
    for (std::uint16_t i = 0; i < n; ++i) {
        std::cin >> temp_x >> temp_y;
        AddToRegionsMap(regions_map, temp_x, temp_y);
        AddToRegionsExists(regions_exists, temp_x, temp_y);
        all_coords[i] = TwoDVector(temp_x, temp_y);
    }
    std::unordered_set<std::uint64_t> used_angles;
    auto CB = [](const std::set<TwoDVector> &now_coords) {
        std::vector<std::vector<TwoDVector>> angles_coords(1, std::vector<TwoDVector>(now_coords.begin(),
                                                                                      now_coords.end()));
        angles_coords.push_back(std::vector<TwoDVector>{angles_coords[0][1], angles_coords[0][0], angles_coords[0][2]});
        angles_coords.push_back(std::vector<TwoDVector>{angles_coords[0][1], angles_coords[0][2], angles_coords[0][0]});
        for (const auto &angle_coords: angles_coords) {
            const TwoDVector &A = angle_coords[0], &B = angle_coords[1], &C = angle_coords[2];
            auto side_size = Geom::GetDist(A, B);
            if (!IsApproxEqual(side_size, Geom::GetDist(B, C))) continue;
            TwoDVector BA = A - B, BC = C - B;
            auto scalar_multi = BA * BC;
            auto cos_abc = static_cast<double>(scalar_multi) / side_size / side_size;
            auto abc_angle = std::acos(cos_abc);
        }
    };
    std::set<TwoDVector> temp_n_c;
    std::unordered_set<std::uint64_t> visited;
    EnumerationFirstThree(temp_n_c, all_coords, visited, CB);
    return 0;
}
