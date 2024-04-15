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
    PV v1(ax, ay, bx, by), v2 = v1.normalized(), v3 = v2 * l, v4(v1.y, -v1.x), v5(-v1.y, v1.x);
    cout << fixed << setprecision(10);
    cout << v1.x << " " << v1.y << "\n";
    cout << v2.x << " " << v2.y << "\n";
    cout << v3.x << " " << v3.y << "\n";
    cout << v4.x << " " << v4.y << "\n";
    cout << v5.x << " " << v5.y << "\n";
    return 0;
}