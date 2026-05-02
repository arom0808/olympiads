#include <iostream>
#include <cmath>
#include <iomanip>
#include <numeric>

using namespace std;

constexpr long double eps = 1e-20;
using ld = long double;

template<typename T>
T my_gcd(T a, T b) {
    T t;
    while (b) t = b, b = a % b, a = t;
    return a;
}

template<typename T>
int32_t int_sign(T a) {
    if (a == 0) return 0;
    if (a > 0) return 1;
    return -1;
}

// template<typename T>
// int32_t double_sign(T a) {
// if (std::abs(a) <= eps) return 0;
// if (a > 0) return 1;
// return -1;
// }

template<typename Tv, typename Tl, typename Td>
struct PV {
    using MPV = PV<Tv, Tl, Td>;
    Tv x, y;

    PV() = default;

    template<typename pTv, typename pTl, typename pTd>
    PV(PV<pTv, pTl, pTd> other) : x(other.x), y(other.y) {
    }

    PV(Tv x, Tv y): x(x), y(y) {
    }

    bool operator==(const MPV &other) {
        return x == other.x && y == other.y;
    }

    [[nodiscard]] static Tl square_dist(MPV a, MPV b) {
        return static_cast<Tl>(a.x - b.x) * (a.x - b.x) + static_cast<Tl>(a.y - b.y) * (a.y - b.y);
    }

    Tl square_len() const {
        return static_cast<Tl>(x) * x + static_cast<Tl>(y) * y;
    }

    Td len() const {
        return std::sqrt(static_cast<Td>(square_len()));
    }

    [[nodiscard]] static long double dist(MPV a, MPV b) {
        return std::sqrt(static_cast<Td>(square_dist(a, b)));
    }

    Tl operator*(MPV other) const {
        return static_cast<Tl>(x) * other.x + static_cast<Tl>(y) * other.y;
    }

    Tl operator^(MPV other) const {
        return static_cast<Tl>(x) * other.y - static_cast<Tl>(y) * other.x;
    }

    MPV operator*(Tv coef) const {
        return {x * coef, y * coef};
    }

    MPV to_len(Td req_len) const {
        return (*this) * (req_len / len());
    }

    MPV operator-(MPV other) const {
        return {x - other.x, y - other.y};
    }

    MPV operator+(MPV other) const {
        return {x + other.x, y + other.y};
    }

    // static bool parallel(MPV a, MPV b) {
    // if (a.x == 0 || b.x == 0) return a.x == 0 && b.x == 0;
    // if (a.y == 0 || b.y == 0) return a.y == 0 && b.y == 0;
    // return static_cast<Tl>(a.y) * b.x == static_cast<Tl>(b.y) * a.x;
    // }

    friend istream &operator>>(istream &stream, MPV &v) {
        stream >> v.x >> v.y;
        return stream;
    }
};

using iPV = PV<int64_t, int64_t, long double>;
using dPV = PV<ld, ld, ld>;

struct Line {
    long double a, b, c;

    static Line from_two_points(dPV a, dPV b) {
        ld ra = (a.y - b.y), rb = (b.x - a.x);
        return Line(ra, rb, -ra * a.x - rb * a.y);
    }

    static Line perp_line(Line a, dPV point) {
        ld ra = -a.a, rb = a.b;
        return Line(ra, rb, -ra * point.x - rb * point.y);
    }

    dPV dir_vec() const {
        return {-a, b};
    }

    static ld dist(Line line, iPV point) {
        return std::abs(line.a * point.x + line.b * point.y + line.c) / std::sqrt(line.a * line.a + line.b * line.b);
    }
};

int main() {
    cout << fixed << setprecision(15);
    iPV o1, o2;
    int64_t r1, r2;
    cin >> o1 >> r1 >> o2 >> r2;
    if (o1 == o2) {
        if (r1 == r2) cout << "3\n";
        else cout << "0\n";
        return 0;
    }
    ld x = static_cast<ld>(iPV::square_dist(o1, o2) + r1 * r1 - r2 * r2) / 2 / iPV::dist(o1, o2);
    dPV p0 = dPV(o1) + dPV(o2 - o1).to_len(x);
    if (x > r1) {
        cout << "0\n";
        return 0;
    }
    ld d = std::sqrt(static_cast<ld>(r1 * r1) - dPV::square_dist(o1, p0));
    if (d <= eps) {
        cout << "1\n" << p0.x << " " << p0.y << "\n";
        return 0;
    }
    Line rad_axis = Line::perp_line(Line::from_two_points(o1, o2), p0);
    dPV dirv = rad_axis.dir_vec();
    dPV a = p0 + dirv.to_len(d), b = p0 - dirv.to_len(d);
    cout << "2\n";
    cout << a.x << " " << a.y << "\n";
    cout << b.x << " " << b.y << "\n";
    return 0;
}
