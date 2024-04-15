#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

template<typename T>
class Vec {
public:
    T x, y;

    Vec(T x1, T y1, T x2, T y2) : x(x2 - x1), y(y2 - y1) {}

    Vec(T x, T y) : x(x), y(y) {}

    [[nodiscard]] T len() const { return sqrt(x * x + y * y); }

    Vec operator+(const Vec &other) const { return {x + other.x, y + other.y}; }

    T operator*(const Vec &other) const { return x * other.x + y * other.y; }

    T operator^(const Vec &other) const { return x * other.y - y * other.x; }
};

int main() {
    long double fx1, fy1, fx2, fy2, sx1, sy1, sx2, sy2;
    cin >> fx1 >> fy1 >> fx2 >> fy2 >> sx1 >> sy1 >> sx2 >> sy2;
    Vec v1(fx1, fy1, fx2, fy2), v2(sx1, sy1, sx2, sy2);
    cout << fixed << setprecision(15);
    cout << v1.len() << " " << v2.len() << "\n";
    auto s = v1 + v2;
    cout << s.x << " " << s.y << "\n";
    cout << v1 * v2 << " " << (v1 ^ v2) << "\n";
    cout << abs(v1 ^ v2) / 2;
    return 0;
}
