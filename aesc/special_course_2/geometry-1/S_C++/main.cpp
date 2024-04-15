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

    bool operator<(const PV &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const PV &other) const { return x == other.x && y == other.y; }
};

int main() {
    long double ax, ay, bx, by, cx, cy, dx, dy;
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
    PV ab(ax, ay, bx, by), ac(ax, ay, cx, cy), ad(ax, ay, dx, dy), cd(cx, cy, dx, dy), cb(cx, cy, bx, by),
            ca(cx, cy, ax, ay), bc(bx, by, cx, cy), bd(bx, by, dx, dy), da(dx, dy, ax, ay), db(dx, dy, bx, by),
            ba(bx, by, ax, ay);
    cout << fixed << setprecision(15);
    if ((ab ^ ac) * (ab ^ ad) > 0 || (cd ^ cb) * (cd ^ ca) > 0) {
        cout << "Empty";
        return 0;
    }
    if ((ab ^ cd) != 0) {
        auto a1 = by - ay, b1 = ax - bx, c1 = ax * ay + ay * bx - ay * ax - ax * by;
        auto a2 = dy - cy, b2 = cx - dx, c2 = cx * cy + cy * dx - cy * cx - cx * dy;
        auto x0 = -(c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
        auto y0 = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
        cout << x0 << "\n" << y0;
        return 0;
    }
    PV<long double> p1, p2;
    if (ac * ad >= 0 && bc * bd >= 0) {
        p1 = {cx, cy}, p2 = {dx, dy};
    } else if (ca * cb >= 0 && da * db >= 0) {
        p1 = {ax, ay}, p2 = {bx, by};
    } else if (ac * ad <= 0) {
        if (ab * ac >= 0) p1 = {ax, ay}, p2 = {cx, cy};
        else p1 = {ax, ay}, p2 = {dx, dy};
    } else if (bc * bd <= 0) {
        if (ba * bc >= 0) p1 = {bx, by}, p2 = {cx, cy};
        else p1 = {bx, by}, p2 = {dx, dy};
    }
    if (p2 < p1) swap(p1, p2);
    if (p1 == p2) cout << p1.x << "\n" << p1.y;
    else cout << p1.x << "\n" << p1.y << "\n" << p2.x << "\n" << p2.y;
    return 0;
}
