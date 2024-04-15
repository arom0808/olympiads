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

    Vec operator+(const Vec &other) const { return {x + other.x, y + other.y}; }

    T operator*(const Vec &other) const { return x * other.x + y * other.y; }

    T operator^(const Vec &other) const { return x * other.y - y * other.x; }
};

int main() {
    int32_t ax, ay, bx, by, cx, cy;
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    Vec bv(ax, ay, bx, by), cv(ax, ay, cx, cy);
    if ((bv ^ cv) < 0) cout << "RIGHT";
    else if ((bv ^ cv) == 0) cout << "BOTH";
    else cout << "LEFT";
    return 0;
}
