#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>
#include <iomanip>
#include <cstdint>

using namespace std;

using ld = long double;

template<typename Tv, typename Tr, typename Td>
class PV {
public:
    using TPV = PV<Tv, Tr, Td>;
    Tv x = 0, y = 0;

    PV() = default;

    template<typename Tvp, typename Trp, typename Tdp>
    explicit PV(const PV<Tvp, Trp, Tdp> &p) : x(p.x), y(p.y) {}

    explicit PV(Tv x, Tv y) : x(x), y(y) {}

    PV(const TPV &a, const TPV &b) : x(b.x - a.x), y(b.y - a.y) {}

    inline Tr sq_len() const {
        return static_cast<Tr>(x) * x + static_cast<Tr>(y) * y;
    }

    inline Td len() const {
        return std::sqrt(sq_len());
    }

    inline Tr sq_dist(const TPV &b) const {
        return static_cast<Tr>(b.x - x) * (b.x - x) + static_cast<Tr>(b.y - y) * (b.y - y);
    }

    inline Td dist(const TPV &b) const {
        return std::sqrt(sq_dist(b));
    }

    TPV operator-(const TPV &b) const {
        return TPV(b, (*this));
    }

    TPV operator+(const TPV &b) const {
        return TPV{x + b.x, y + b.y};
    }

    inline Tr operator*(const TPV &b) const {
        return static_cast<Tr>(x) * b.x + static_cast<Tr>(y) * b.y;
    }

    inline Tr operator^(const TPV &b) const {
        return static_cast<Tr>(x) * b.y - static_cast<Tr>(y) * b.x;
    }

    inline Td angle(const TPV &b) const {
        return std::atan2<Td, Td>((*this) ^ b, (*this) * b);
    }

    bool operator==(const TPV &b) const {
        return x == b.x && y == b.y;
    }

    bool half_plane() const {
        return y < 0 || (y == 0 && x < 0);
    }

    static bool cmp_y_x(const TPV &a, const TPV &b) {
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    }

    static bool cmp_polar_angle(const TPV &a, const TPV &b) {
        if (a.half_plane() != b.half_plane()) return a.half_plane() < b.half_plane();
        auto vmr = a ^ b;
        if (vmr) return vmr > 0;
        return a.sq_len() < b.sq_len();
    }

    TPV operator/(Tv v) const {
        return TPV{x / v, y / v};
    }

    TPV operator*(Tv v) const {
        return TPV{x * v, y * v};
    }

    TPV to_len(Tv _len) {
        return (*this) / len() * _len;
    }
};

using mPV = PV<int64_t, int64_t, ld>;
using dPV = PV<ld, ld, ld>;

template<typename T>
struct Line {
public:
    T a = 0, b = 0, c = 0;

    Line() = default;

    Line(T a, T b, T c) : a(a), b(b), c(c) {}

    static Line<T> from_p_and_dir(const dPV &v1, const dPV &dir) {
        return Line<T>{dir.y, -dir.x, dir.x * v1.y - dir.y * v1.x};
    }

    static Line<T> from_two_p(const dPV &p1, const dPV &p2) {
        return Line<T>(p2.y - p1.y, p1.x - p2.x, (p1.y - p2.y) * p1.x + (p2.x - p1.x) * p1.y);
    }

    template<typename Tvp, typename Trp, typename Tdp>
    Tvp val(PV<Tvp, Trp, Tdp> p) const { return a * p.x + b * p.y + c; }

    dPV intersect(const Line<T> &v) {
        ld d = b * v.a - v.b * a;
        return dPV{(c * v.b - v.c * b) / d, (a * v.c - c * v.a) / d};
    }
};

using mLine = Line<ld>;
const ld eps = 1e-15;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(10);
    mPV p0, p1;
    int64_t r;
    cin >> p0.x >> p0.y >> r >> p1.x >> p1.y;
    if (p0.sq_dist(p1) < r * r) {
        cout << "0\n";
        return 0;
    }
    if (p0.sq_dist(p1) == r * r) {
        cout << "1\n";
        cout << p1.x << " " << p1.y << "\n";
        return 0;
    }
    ld R = std::sqrt(static_cast<ld>(p0.sq_dist(p1) - r * r));
    dPV c1 = static_cast<dPV>(p0), c2 = static_cast<dPV>(p1);
    ld r1 = r, r2 = R;
    mLine l(2 * (c1.x - c2.x), 2 * (c1.y - c2.y),
            c2.x * c2.x + c2.y * c2.y - c1.x * c1.x - c1.y * c1.y + r1 * r1 - r2 * r2);
    ld h = static_cast<ld>(std::abs(l.val(c1))) / dPV(l.a, l.b).len();
    dPV H = static_cast<dPV>(c1) + dPV(l.a, l.b).to_len(h), tH = static_cast<dPV>(c1) - dPV(l.a, l.b).to_len(h);
    if (std::abs(l.val(tH)) < std::abs(l.val(H))) swap(H, tH);
    ld AH = std::sqrt(r1 * r1 - h * h);
    dPV A = H + dPV(-l.b, l.a).to_len(AH), B = H + dPV(l.b, -l.a).to_len(AH);
    dPV p3 = Line<ld>::from_two_p(c1, c2).intersect(l);
    cout << "2\n";
    cout << p3.x << " " << p3.y << "\n";
    cout << c2.dist(p3) << " " << p3.dist(A) << "\n";
    cout << A.x << " " << A.y << "\n";
    cout << B.x << " " << B.y << "\n";
    return 0;
}
