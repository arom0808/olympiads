#include <iostream>
#include <cmath>
#include <iomanip>

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

    [[nodiscard]] T angle(const PV &other) const { return acos(cos(other)); }

    PV operator+(const PV &other) const { return {x + other.x, y + other.y}; }

    PV operator-(const PV &other) const { return {x - other.x, y - other.y}; }

    PV operator*(T v) const { return {x * v, y * v}; }

    PV operator/(T v) const { return {x / v, y / v}; }

    T operator*(const PV &other) const { return x * other.x + y * other.y; }

    T operator^(const PV &other) const { return x * other.y - y * other.x; }
};

int main() {
    PV<int64_t> pre_point, first_point, second_point, pre_vec, now_point, now_vec;
    int32_t n;
    cin >> n >> pre_point.x >> pre_point.y >> now_point.x >> now_point.y;
    first_point = pre_point, second_point = now_point;
    pre_vec = now_point - pre_point;
    pre_point = now_point;
    bool was_left = false, was_right = false;
    for (int32_t i = 0; i < n; ++i) {
        if (i + 2 < n) cin >> now_point.x >> now_point.y;
        else if (i + 2 == n) now_point = first_point;
        else now_point = second_point;
        now_vec = now_point - pre_point;
        if ((pre_vec ^ now_vec) > 0) was_left = true;
        else if ((pre_vec ^ now_vec) < 0) was_right = true;
        pre_point = now_point, pre_vec = now_vec;
    }
    if (was_left ^ was_right) cout << "YES";
    else cout << "NO";
    return 0;
}