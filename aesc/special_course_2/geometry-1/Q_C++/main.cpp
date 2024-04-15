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
    long double ax, ay, bx, by, l;
    cin >> ax >> ay >> bx >> by >> l;
    PV v1(ax, ay, bx, by);
    long double a1 = by - ay, b1 = ax - bx, c1 = ax * ay + ay * bx - ay * ax - ax * by;
    PV v2(v1.y, -v1.x);
    long double a2 = v2.y, b2 = -v2.x, c2 = 0;
    PV nv2 = v2.normalized(), p1 = PV(ax, ay) + nv2 * l, p2 = PV(ax, ay) - nv2 * l;
    long double c3 = -a1 * p1.x - b1 * p1.y, c4 = -a1 * p2.x - b1 * p2.y;
    cout << fixed << setprecision(10);
    cout << v1.x << " " << v1.y << "\n";
    cout << a1 << " " << b1 << " " << c1 << "\n";
    cout << v2.x << " " << v2.y << "\n";
    cout << a2 << " " << b2 << " " << c2 << "\n";
    cout << a1 << " " << b1 << " " << c3 << "\n";
    cout << a1 << " " << b1 << " " << c4 << "\n";
    return 0;
}