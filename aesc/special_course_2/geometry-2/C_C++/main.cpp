#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class PV {
public:
    T x = 0, y = 0;

    PV(T x1, T y1, T x2, T y2) : x(x2 - x1), y(y2 - y1) {}

    PV(T x, T y) : x(x), y(y) {}

    PV() = default;

    void assign(T x1, T y1, T x2, T y2) { x = x2 - x1, y = y2 - y1; }

    [[nodiscard]] PV normalized() const { return (*this) / len(); }

    [[nodiscard]] T len() const { return sqrt(x * x + y * y); }

    [[nodiscard]] T dist(const PV &other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }

    [[nodiscard]] T cos(const PV &other) const { return (*this) * other / len() / other.len(); }

    [[nodiscard]] T sin(const PV &other) const { return ((*this) ^ other) / len() / other.len(); }

    [[nodiscard]] T angle(const PV &other) const { return asin(sin(other)); }

    PV operator+(const PV &other) const { return {x + other.x, y + other.y}; }

    PV operator-(const PV &other) const { return {x - other.x, y - other.y}; }

    PV operator*(T v) const { return {x * v, y * v}; }

    PV operator/(T v) const { return {x / v, y / v}; }

    T operator*(const PV &other) const { return x * other.x + y * other.y; }

    T operator^(const PV &other) const { return x * other.y - y * other.x; }

    bool operator<(const PV &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const PV &other) const {
        return x == other.x && y == other.y;
    }
};

int main() {
    int32_t n;
    cin >> n;
    vector<PV<int64_t>> points(n);
    for (auto &p: points) cin >> p.x >> p.y;
    PV<int64_t> lbp = *min_element(points.begin(), points.end()), rtp = *max_element(points.begin(), points.end());
    vector<PV<int64_t>> top_points, bottom_points;
    top_points.reserve(n), bottom_points.reserve(n);
    for (const auto &p: points) {
        auto t = (p - lbp) ^ (rtp - lbp);
        if (t < 0) top_points.push_back(p);
        else if (t > 0) bottom_points.push_back(p);
    }
    top_points.push_back(lbp);
    top_points.push_back(rtp);
    bottom_points.push_back(lbp);
    bottom_points.push_back(rtp);
    sort(top_points.begin(), top_points.end());
    sort(bottom_points.begin(), bottom_points.end());

    return 0;
}
