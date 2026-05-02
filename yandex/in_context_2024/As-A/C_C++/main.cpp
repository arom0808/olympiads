#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
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

    explicit PV(Tv x, Tv y) : x(x), y(y) {}

    PV(const TPV &a, const TPV &b) : x(b.x - a.x), y(b.y - a.y) {}

    template<typename vTv, typename vTr, typename vTd>
    explicit operator PV<vTv, vTr, vTd>() {
        return PV<vTv, vTr, vTd>(x, y);
    }

    inline Tr sq_len() const {
        return static_cast<Tr>(x) * x + static_cast<Tr>(y) * y;
    }

    inline Td len() const {
        return std::sqrt<Td>(sq_len());
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
        return TPV(x + b.x, y + b.y);
    }

    TPV operator/(Tv val) const {
        return TPV(x / val, y / val);
    }

    TPV operator*(Tv val) const {
        return TPV(x * val, y * val);
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
};

using mPV = PV<int32_t, int64_t, ld>;
using lPV = PV<ld, ld, ld>;

struct Line {
    ld a, b, c;

    explicit Line(ld a = 0, ld b = 0, ld c = 0) : a(a), b(b), c(c) {}

    ld dist(lPV point) const {
        return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
    }
};

const ld eps = 1e-10;

struct Seg {
    lPV a, b;

    Line to_line() const {
        Line line(b.y - a.y, a.x - b.x);
        line.c = -line.a * a.x - line.b * a.y;
        return line;
    }

    ld dist(lPV point) const {
        if ((a - b) * (point - b) >= -eps && (b - a) * (point - a) >= -eps) return to_line().dist(point);
        return std::min(a.dist(point), b.dist(point));
    }
};

int32_t n;
vector<Seg> segs;

template<typename T, typename TR>
T ternary_search(T l, T r, const std::function<TR(T)> &f) {
    while (r - l > eps) {
        T m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (f(m1) <= f(m2)) r = m2;
        else l = m1;
    }
    return (l + r) / 2;
}

ld min_dist_to_segs(lPV point) {
    ld res = 0;
    for (const auto &seg: segs) res = std::max(res, seg.dist(point));
    return res;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cout << fixed << setprecision(8);
//    cout << Seg(lPV(6, 9), lPV(8, 7)).dist(lPV(5, 5)) << "\n";
//    cout << Seg(lPV(9, 6), lPV(9, 4)).dist(lPV(5, 5)) << "\n";
//    cout << Seg(lPV(7, 2), lPV(6, 0)).dist(lPV(5, 5)) << "\n";
//    cout << Seg(lPV(7, 4), lPV(3, 0)).dist(lPV(5, 5)) << "\n";
    cin >> n;
    segs.resize(n);
    for (auto &[s1, s2]: segs) cin >> s1.x >> s1.y >> s2.x >> s2.y;
    ld best_x, best_y;
    best_x = ternary_search<ld, ld>(-500, 1500, [&best_y](ld x) {
        best_y = ternary_search<ld, ld>(-500, 1500, [x](ld y) {
            return min_dist_to_segs(lPV(x, y));
        });
        return min_dist_to_segs(lPV(x, best_y));
    });
    cout<< min_dist_to_segs(lPV(best_x, best_y));
    return 0;
}
