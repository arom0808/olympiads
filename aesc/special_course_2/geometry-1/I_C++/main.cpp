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

int main() {
    int32_t ax, ay, ox, oy, bx, by, px, py;
    cin >> ax >> ay >> ox >> oy >> bx >> by >> px >> py;
    Vec s1(ox, oy, ax, ay), s2(ox, oy, bx, by), p(ox, oy, px, py);
    auto r1 = s1 ^ s2, r2 = s1 ^ p, r3 = p ^ s2;
    if ((r1 <= 0 && r2 <= 0 && r3 <= 0) || (r1 >= 0 && r2 >= 0 && r3 >= 0)) cout << "YES";
    else cout << "NO";
    return 0;
}
