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
    long double ax, ay, bx, by, cx, cy;
    cin >> cx >> cy >> ax >> ay >> bx >> by;
    Vec ab(ax, ay, bx, by), ac(ax, ay, cx, cy), ba(bx, by, ax, ay), bc(bx, by, cx, cy);
    long double d1 = abs(ab ^ ac) / ab.len(), d2, d3;
    if (ab * ac >= 0) d2 = d1;
    else d2 = ac.len();
    if (ac * ab < 0) d3 = ac.len();
    else if (bc * ba < 0) d3 = bc.len();
    else d3 = d1;
    cout << fixed << setprecision(15) << d1 << "\n" << d2 << "\n" << d3;
    return 0;
}