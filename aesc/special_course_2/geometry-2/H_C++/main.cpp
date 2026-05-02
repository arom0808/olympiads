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
    T a = 0, b = 0, c = 0;

    Line() = default;

    Line(T a, T b, T c) : a(a), b(b), c(c) {}

    template<typename Tvp, typename Trp, typename Tdp>
    Tvp val(PV<Tvp, Trp, Tdp> p) const { return a * p.x + b * p.y + c; }
};

using mLine = Line<int64_t>;
const ld eps = 1e-15;

void sol_test() {
    mPV c1, c2;
    int64_t r1, r2;
    cin >> c1.x >> c1.y >> r1 >> c2.x >> c2.y >> r2;
//    if (c1.sq_dist(c2) > (r1 + r2) * (r1 + r2)) {
//        cout << "0\n";
//        return;
//    }
    if (c1 == c2) {
        if (r1 == r2) cout << "3\n";
        else cout << "0\n";
        return;
    }
//    if (c1.sq_dist(c2) == (r1 + r2) * (r1 + r2) || c1.sq_dist(c2) == (r1 - r2) * (r1 - r2)) {
//        if (r1 < r2) swap(c1, c2), swap(r1, r2);
//        cout << "1\n";
//        dPV p = static_cast<dPV>(c1) + static_cast<dPV>(c2 - c1).to_len(r1);
//        cout << p.x << " " << p.y << "\n";
//        return;
//    }
    mLine l(2 * (c1.x - c2.x), 2 * (c1.y - c2.y),
            c2.x * c2.x + c2.y * c2.y - c1.x * c1.x - c1.y * c1.y + r1 * r1 - r2 * r2);
    ld h = static_cast<ld>(std::abs(l.val(c1))) / mPV(l.a, l.b).len();
    if (h > r1) {
        cout << "0\n";
        return;
    }
    dPV H = static_cast<dPV>(c1) + dPV(l.a, l.b).to_len(h), tH = static_cast<dPV>(c1) - dPV(l.a, l.b).to_len(h);
    if (std::abs(l.val(tH)) < std::abs(l.val(H))) swap(H, tH);
    ld AH = std::sqrt(r1 * r1 - h * h);
    dPV A = H + dPV(-l.b, l.a).to_len(AH), B = H + dPV(l.b, -l.a).to_len(AH);
    if (AH <= eps) {
        cout << "1\n";
        cout << A.x << " " << A.y << "\n";
        return;
    }
    cout << "2\n";
    cout << H.x << " " << H.y << "\n";
    cout << h << " " << AH << "\n";
    cout << A.x << " " << A.y << "\n";
    cout << B.x << " " << B.y << "\n";
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(10);
    int32_t t;
    cin >> t;
    for (int32_t i = 0; i < t; ++i) {
        sol_test();
    }
    return 0;
}
