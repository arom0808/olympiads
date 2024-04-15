#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

template<typename T>
class Vec {
public:
    T x = 0, y = 0;

    Vec(T x1, T y1, T x2, T y2) : x(x2 - x1), y(y2 - y1) {}

    Vec(T x, T y) : x(x), y(y) {}

    Vec() = default;

    void assign(T x1, T y1, T x2, T y2) { x = x2 - x1, y = y2 - y1; }

    [[nodiscard]] T len() const { return sqrt(x * x + y * y); }

    [[nodiscard]] T cos(const Vec &other) const { return (*this) * other / len() / other.len(); }

    [[nodiscard]] T angle(const Vec &other) const { return acos(cos(other)); }

    Vec operator+(const Vec &other) const { return {x + other.x, y + other.y}; }

    T operator*(const Vec &other) const { return x * other.x + y * other.y; }

    T operator^(const Vec &other) const { return x * other.y - y * other.x; }
};

int main() {
    int32_t x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    Vec<long double> v1(x1, y1), v2(x2, y2);
    cout << fixed << setprecision(10) << v1.angle(v2);
    return 0;
}
