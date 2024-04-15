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
    int32_t x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    Vec ray(x2, y2, x3, y3), pv(x2, y2, x1, y1), mp1(x1, y1, x2, y2), mp2(x1, y1, x3, y3);
    if ((ray ^ pv) == 0) cout << "YES\n";
    else cout << "NO\n";
    if ((ray ^ pv) == 0 && (ray * pv) >= 0) cout << "YES\n";
    else cout << "NO\n";
    if ((ray ^ pv) == 0 && (mp1 * mp2) <= 0) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
