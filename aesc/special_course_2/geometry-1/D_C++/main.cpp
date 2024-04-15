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

    Vec operator+(const Vec &other) const { return {x + other.x, y + other.y}; }

    T operator*(const Vec &other) const { return x * other.x + y * other.y; }

    T operator^(const Vec &other) const { return x * other.y - y * other.x; }
};

int main() {
    int32_t n;
    cin >> n;
    if (n < 3) {
        cout << 0;
        return 0;
    }
    int32_t res = 0;
    long double x0, y0, pre_x, pre_y, nx, ny;
    cin >> x0 >> y0 >> pre_x >> pre_y;
    Vec<long double> pre_v(x0, y0, pre_x, pre_y), nv;
    for (int32_t i = 2; i < n; ++i) {
        cin >> nx >> ny;
        nv.assign(pre_x, pre_y, nx, ny);
        if ((pre_v ^ nv) > 0) ++res;
        pre_x = nx, pre_y = ny, pre_v = nv;
    }
    cout << res;
    return 0;
}
