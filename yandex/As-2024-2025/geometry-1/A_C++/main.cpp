#include <iostream>
#include <cmath>
#include <iomanip>
#include <numeric>

using namespace std;

constexpr long double eps = 1e-15;
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

    [[nodiscard]] static Tl square_dist(MPV a, MPV b) {
        return static_cast<Tl>(a.x - b.x) * (a.x - b.x) + static_cast<Tl>(a.y - b.y) * (a.y - b.y);
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

using iPV = PV<int32_t, int64_t, long double>;
using dPV = PV<ld, ld, ld>;

struct Line {
    __int128 a, b, c;

    static Line from_two_points(iPV a, iPV b) {
        auto ab_gcd = my_gcd(a.y - b.y, b.x - a.x);
        __int128 ra = (a.y - b.y) / ab_gcd, rb = (b.x - a.x) / ab_gcd;
        return Line(ra, rb, -ra * a.x - rb * a.y);
    }

    static Line perp_line(Line a, iPV point) {
        auto ab_gcd = my_gcd(-a.a, a.b);
        __int128 ra = -a.a / ab_gcd, rb = a.b / ab_gcd;
        return Line(ra, rb, -ra * point.x - rb * point.y);
    }

    static bool equal(iPV a, iPV b, iPV c, iPV d) {
        return ((b - a) ^ (c - a)) == 0 && ((b - a) ^ (d - a)) == 0;
    }

    static bool parallel(iPV a, iPV b, iPV c, iPV d) {
        return ((b - a) ^ (d - c)) == 0;
    }

    static bool cross(iPV a, iPV b, iPV c, iPV d) {
        if (equal(a, b, c, d)) return true;
        return !parallel(a, b, c, d);
    }

    static long double dist(iPV a, iPV b, iPV c, iPV d) {
        if (cross(a, b, c, d)) return 0;
        return dist(from_two_points(a, b), c);
    }


    // static dPV cross_p(Line a, Line b) {
        // if (a.a == 0) swap(a, b);
        // ld a21 = static_cast<ld>(b.a) / static_cast<ld>(a.a);
        // ld y = (a21 * static_cast<ld>(a.c) - static_cast<ld>(b.c))
               // / (static_cast<ld>(b.b) - a21 * static_cast<ld>(a.b));
        // ld x = (static_cast<ld>(-a.b) * y - static_cast<ld>(a.c)) / static_cast<ld>(a.a);
        // return {x, y};
    // }

    // a, b - on line; c - point
    static ld dist(Line line, iPV point) {
        return std::abs(static_cast<ld>(line.a) * point.x + static_cast<ld>(line.b) * point.y + static_cast<ld>(line.c))
               / std::sqrt(static_cast<ld>(line.a) * static_cast<ld>(line.a) +
                           static_cast<ld>(line.b) * static_cast<ld>(line.b));
    }

    static pair<int32_t, int32_t> get_u_v_sign_of_cross(iPV _a, iPV _b, iPV _c, iPV _d) {
        __int128 a = _a.x, b = _a.y, c = _b.x, d = _b.y, e = _c.x, f = _c.y, g = _d.x, h = _d.y;
        __int128 u_nominator, u_denominator, v_nominator, v_denominator;
        if (e != g) {
            u_nominator = a * (f - h) + b * (g - e) + e * h - f * g;
            v_nominator = a * (f - d) + b * (c - e) - c * f + d * e;
            u_denominator = v_denominator = (a - c) * (f - h) + b * (g - e) + d * (e - g);
        } else {
            u_nominator = a - g;
            u_denominator = a - c;
            v_nominator = a * (f - d) + b * (c - g) - c * f + d * g;
            v_denominator = (a - c) * (f - h);
        }
        return {int_sign(u_nominator) * int_sign(u_denominator), int_sign(v_nominator) * int_sign(v_denominator)};
    }
};

struct Seg {
    iPV a, b;

    static ld dist(Seg seg, iPV c) {
        bool a_sharp = (seg.b - seg.a) * (c - seg.a) >= 0, b_sharp = (seg.a - seg.b) * (c - seg.b) >= 0;
        if (a_sharp && b_sharp) return Line::dist(Line::from_two_points(seg.a, seg.b), c);
        return std::min(iPV::dist(seg.a, c), iPV::dist(seg.b, c));
    }

    static bool inline_intersect(int32_t a, int32_t b, int32_t c, int32_t d) {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        return std::max(a, c) <= std::min(b, d);
    }

    static bool cross(Seg a, Seg b) {
        if (((a.b - a.a) ^ (b.a - a.a)) == 0 && ((a.b - a.a) ^ (b.b - a.a)) == 0)
            return inline_intersect(a.a.x, a.b.x, b.a.x, b.b.x) && inline_intersect(a.a.y, a.b.y, b.a.y, b.b.y);
        return int_sign((a.b - a.a) ^ (b.a - a.a)) * int_sign((a.b - a.a) ^ (b.b - a.a)) <= 0 &&
               int_sign((b.a - b.b) ^ (a.a - b.b)) * int_sign((b.a - b.b) ^ (a.b - b.b)) <= 0;
    }

    static ld dist(Seg a, Seg b) {
        if (cross(a, b)) return 0;
        return std::min(dist(a, b.a), std::min(dist(a, b.b), std::min(dist(b, a.a), dist(b, a.b))));
    }

    // a - seg; b, c - on line
    static bool cross_line(Seg a, iPV b, iPV c) {
        return int_sign((c - b) ^ (a.a - b)) * int_sign((c - b) ^ (a.b - b)) <= 0;
    }

    // a - seg; b, c - on line
    static ld dist_line(Seg a, iPV b, iPV c) {
        if (cross_line(a, b, c)) return 0;
        return std::min(Line::dist(Line::from_two_points(b, c), a.a), Line::dist(Line::from_two_points(b, c), a.b));
    }
};

bool point_in_angle(iPV a, iPV o, iPV b, iPV p) {
    iPV oa = a - o, op = p - o, ob = b - o;
    auto r1 = oa ^ ob, r2 = oa ^ op, r3 = op ^ ob;
    return (r1 <= 0 && r2 <= 0 && r3 <= 0) || (r1 >= 0 && r2 >= 0 && r3 >= 0);
}

struct Ray {
    iPV a, b;

    static long double dist(Ray ray, iPV c) {
        if ((ray.b - ray.a) * (c - ray.a) >= 0) return Line::dist(Line::from_two_points(ray.a, ray.b), c);
        return iPV::dist(ray.a, c);
    }

    // a, b - ray; c, d - seg;
    static bool inline_intersect(int32_t a, int32_t b, int32_t c, int32_t d) {
        return int_sign(b - a) * int_sign(c - a) >= 0 || int_sign(b - a) * int_sign(d - a) >= 0;
    }

    static bool cross(Ray a, Seg b) {
        if (((a.b - a.a) ^ (b.a - a.a)) == 0 && ((a.b - a.a) ^ (b.b - a.a)) == 0)
            return inline_intersect(a.a.x, a.b.x, b.a.x, b.b.x) && inline_intersect(a.a.y, a.b.y, b.a.y, b.b.y);
        return point_in_angle(b.a, a.a, b.b, a.b);
    }

    static long double dist(Ray a, Seg b) {
        if (cross(a, b)) return 0;
        return std::min(Seg::dist(b, a.a), std::min(dist(a, b.a), dist(a, b.b)));
    }

    // static bool includes_point(Ray _a, dPV c) {
    // dPV a = _a.a, b = _a.b;
    // return double_sign((b - a) ^ (c - a)) == 0 && double_sign((b - a) * (c - a)) >= 0;
    // }

    static bool cross(Ray _a, Ray _b) {
        if (((_a.b - _a.a) ^ (_b.b - _b.a)) == 0) {
            if (((_a.b - _a.a) ^ (_b.a - _a.a)) == 0 && ((_a.b - _a.a) ^ (_b.b - _a.a)) == 0)
                return (_a.b - _a.a) * (_b.b - _a.a) <= 0 || (_a.b - _b.a) * (_b.b - _b.a) <= 0;
            return false;
        }
        auto [u_sign, v_sign] = Line::get_u_v_sign_of_cross(_a.a, _a.b, _b.a, _b.b);
        return u_sign >= 0 && v_sign >= 0;
    }

    static long double dist(Ray a, Ray b) {
        if (cross(a, b)) return 0;
        return std::min(dist(a, b.a), dist(b, a.a));
    }

    // b, c - on line
    static bool cross(Ray a, iPV b, iPV c) {
        if (((a.b - a.a) ^ (c - b)) == 0) return ((a.b - a.a) ^ (b - a.a)) == 0;
        auto [u_sign, v_sign] = Line::get_u_v_sign_of_cross(a.a, a.b, b, c);
        return u_sign >= 0;
    }

    // b, c - on line
    static long double dist(Ray a, iPV b, iPV c) {
        if (cross(a, b, c)) return 0;
        return Line::dist(Line::from_two_points(b, c), a.a);
    }
};


int main() {
    iPV a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << fixed << setprecision(10);
    cout << iPV::dist(a, c) << "\n";
    cout << Seg::dist(Seg(c, d), a) << "\n";
    cout << Ray::dist(Ray(c, d), a) << "\n";
    cout << Line::dist(Line::from_two_points(c, d), a) << "\n";
    cout << Seg::dist(Seg(a, b), c) << "\n";
    cout << Seg::dist(Seg(a, b), Seg(c, d)) << "\n";
    cout << Ray::dist(Ray(c, d), Seg(a, b)) << "\n"; //
    cout << Seg::dist_line(Seg(a, b), c, d) << "\n"; //
    cout << Ray::dist(Ray(a, b), c) << "\n"; //
    cout << Ray::dist(Ray(a, b), Seg(c, d)) << "\n";
    cout << Ray::dist(Ray(a, b), Ray(c, d)) << "\n";
    cout << Ray::dist(Ray(a, b), c, d) << "\n";
    cout << Line::dist(Line::from_two_points(a, b), c) << "\n";
    cout << Seg::dist_line(Seg(c, d), a, b) << "\n";
    cout << Ray::dist(Ray(c, d), a, b) << "\n";
    cout << Line::dist(a, b, c, d) << "\n";
    return 0;
}
