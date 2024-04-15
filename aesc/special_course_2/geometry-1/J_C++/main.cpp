#include <iostream>
#include <cmath>

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

bool intersect(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy) {
    Vec fv(ax, ay, bx, by), sv(cx, cy, dx, dy);
    if ((fv ^ sv) == 0) {
        Vec acv(ax, ay, cx, cy);
        if ((acv ^ fv) != 0) return false;
        if (fv * sv >= 0) return true;
        return fv * acv >= 0;
    }
    double a1 = by - ay, b1 = ax - bx, c1 = ax * ay + ay * bx - ay * ax - ax * by;
    double a2 = dy - cy, b2 = cx - dx, c2 = cx * cy + cy * dx - cy * cx - cx * dy;
    double x0 = -(c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
    double y0 = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    return fv * Vec(ax, ay, x0, y0) >= 0 && sv * Vec(cx, cy, x0, y0) >= 0;
}

int main() {
    int32_t ax, ay, bx, by, cx, cy, dx, dy;
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
    if (intersect(ax, ay, bx, by, cx, cy, dx, dy)) cout << "YES";
    else cout << "NO";
    return 0;
}