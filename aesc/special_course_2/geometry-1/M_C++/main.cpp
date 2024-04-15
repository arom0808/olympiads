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

    [[nodiscard]] T len() const { return sqrt(x * x + y * y); }

    [[nodiscard]] T dist(const PV &other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }

    [[nodiscard]] T cos(const PV &other) const { return (*this) * other / len() / other.len(); }

    [[nodiscard]] T angle(const PV &other) const { return acos(cos(other)); }

    PV operator+(const PV &other) const { return {x + other.x, y + other.y}; }

    PV operator-(const PV &other) const { return {x - other.x, y - other.y}; }

    T operator*(const PV &other) const { return x * other.x + y * other.y; }

    T operator^(const PV &other) const { return x * other.y - y * other.x; }
};

template<typename T>
class Segment {
public:
    PV<T> a, b;

    Segment(const PV<T> &a, const PV<T> &b) : a(a), b(b) {}

    Segment(T ax, T ay, T bx, T by) : a(ax, ay), b(bx, by) {}

    [[nodiscard]] T dist(const PV<T> &p) const {
        PV ab = b - a, ap = p - a, bp = p - b, ba = a - b;
        if (ap * ab < 0) return a.dist(p);
        else if (bp * ba < 0) return b.dist(p);
        return abs(ab ^ ap) / ab.len();
    }

    [[nodiscard]] bool intersect(const Segment &ot) const {
        PV ab = b - a, ac = ot.a - a, ad = ot.b - a, cd = ot.b - ot.a, cb = ot.a - b, ca = ot.a - a;
        return (ab ^ ac) * (ab ^ ad) <= 0 && (cd ^ cb) * (cd ^ ca) <= 0;
    }

    [[nodiscard]] T dist(const Segment &ot) const {
        if (intersect(ot)) return 0;
        return min(dist(ot.a), min(dist(ot.b), min(ot.dist(a), ot.dist(b))));
    }
};

int main() {
    long double ax, ay, bx, by, cx, cy, dx, dy;
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
    Segment s1(ax, ay, bx, by), s2(cx, cy, dx, dy);
    cout << fixed << setprecision(10) << s1.dist(s2);
    return 0;
}