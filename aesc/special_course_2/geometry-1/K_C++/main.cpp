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

int64_t sign(int64_t v) {
    if (v < 0) return -1;
    else if (v == 0) return 0;
    return 1;
}

int main() {
    int64_t ax, ay, bx, by, cx, cy, dx, dy;
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
    Vec ab(ax, ay, bx, by), ac(ax, ay, cx, cy), ad(ax, ay, dx, dy), cd(cx, cy, dx, dy), cb(cx, cy, bx, by),
            ca(cx, cy, ax, ay);
    if (((ab ^ ac) < 0 && (ab ^ ad) < 0) || ((ab ^ ac) > 0 && (ab ^ ad) > 0)) {
        cout << "NO";
        return 0;
    }
    if (((cd ^ cb) < 0 && (cd ^ ca) < 0) || ((cd ^ cb) > 0 && (cd ^ ca) > 0)) {
        cout << "NO";
        return 0;
    }
    cout << "YES";
    return 0;
}