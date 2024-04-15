#include <iostream>
#include <cmath>

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
};

const long double eps = 1e-10;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t n;
    PV<long double> target_point, first_point, now_point, pre_vec, now_vec;
    cin >> n >> target_point.x >> target_point.y >> now_point.x >> now_point.y;
    first_point = now_point, pre_vec = now_point - target_point;
    long double angle = 0;
    for (int32_t i = 0; i < n; ++i) {
        if (i + 1 < n) cin >> now_point.x >> now_point.y;
        else now_point = first_point;
        now_vec = now_point - target_point;
        angle += pre_vec.angle(now_vec);
        if (abs(pre_vec ^ now_vec) <= eps && pre_vec * now_point < 0) {
            cout << "YES";
            return 0;
        }
        pre_vec = now_vec;
    }
    if (abs(angle) <= eps) cout << "NO";
    else cout << "YES";
    return 0;
}
