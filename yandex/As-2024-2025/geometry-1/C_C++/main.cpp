#include <array>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <numeric>

using namespace std;

using ld = long double;
using ll = long long;

constexpr ld eps = 1e-15;

class PV {
public:
    ld x, y;

    PV() = default;

    PV(ld x, ld y): x(x), y(y) {
    }

    PV operator-(const PV &rhs) const {
        return {x - rhs.x, y - rhs.y};
    }

    PV operator+(const PV &rhs) const {
        return {x + rhs.x, y + rhs.y};
    }

    PV operator*(const ld &coef) const {
        return {x * coef, y * coef};
    }

    PV normal() const {
        return {-y, x};
    }

    ld square_len() const {
        return x * x + y * y;
    }

    ld len() const {
        return std::sqrt(square_len());
    }

    PV to_len(ld req_len) const {
        auto k = req_len / len();
        return {x * k, y * k};
    }

    ld square_dist(const PV &rhs) const {
        return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
    }

    ld dist(const PV &rhs) const {
        return std::sqrt(1.l * square_dist(rhs));
    }

    ld operator*(const PV &rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    ld operator^(const PV &rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    friend istream &operator>>(istream &is, PV &v) {
        return is >> v.x >> v.y;
    }

    friend ostream &operator<<(ostream &os, const PV &v) {
        return os << v.x << " " << v.y;
    }
};

class Line {
public:
    PV point_on_line;
    PV dir, normal;
    ll a, b, c;

    ld dist(PV p) {
        return std::abs(1.l * a * p.x + 1.l * b * p.y + c) / std::sqrt(1.l * a * a + 1.l * b * b);
    }

    PV projection(PV p) {
        auto t = -(a * p.x + b * p.y + c) / normal.square_len();
        return p + normal * t;
    }

    static Line from_two_points(PV a, PV b) {
        Line res;
        res.point_on_line = a;
        res.dir = b - a;
        res.normal = res.dir.normal();
        res.a = a.y - b.y;
        res.b = b.x - a.x;
        res.c = -res.a * a.x - res.b * a.y;
        return res;
    }

    static Line from_coefs(ld a, ld b, ld c) {
        Line res;
        res.a = a, res.b = b, res.c = c;
        res.normal = {a, b};
        res.dir = res.normal.normal();
        res.point_on_line = res.projection({0, 0});
        return res;
    }
};

class Segment {
public:
    PV a, b;
    Line line;

    ld dist(PV p) {
        if ((b - a) * (p - a) <= eps) return a.dist(p);
        if ((a - b) * (p - b) <= eps) return b.dist(p);
        return line.dist(p);
    }

    static Segment from_two_points(PV a, PV b) {
        Segment res;
        res.line = Line::from_two_points(a, b);
        res.a = a, res.b = b;
        return res;
    }
};

class Circle {
public:
    PV c;
    ld r;

    friend istream &operator>>(istream &is, Circle &c) {
        return is >> c.c >> c.r;
    }
};

array<PV, 2> cross_circle_line(Circle c, Line l) {
    auto h = l.dist(c.c);
    auto d = std::sqrt(c.r * c.r - h * h);
    auto m = l.projection(c.c);
    auto dv = l.dir.to_len(d);
    return {m + dv, m - dv};
}

array<PV, 2> cross_circle_circle(Circle c1, Circle c2) {
    auto a = 2 * (c1.c.x - c2.c.x), b = 2 * (c1.c.y - c2.c.y),
            c = c2.c.x * c2.c.x + c2.c.y * c2.c.y - c2.r * c2.r - c1.c.x * c1.c.x - c1.c.y * c1.c.y + c1.r * c1.r;
    Line line = Line::from_coefs(a, b, c);
    return cross_circle_line(c1, line);
}

array<PV, 2> get_tangent_points(PV p, Circle c) {
    auto d = c.c.dist(p);
    auto g = std::sqrt(d * d - 1.l * c.r * c.r);
    return cross_circle_circle({p, g}, c);
}

void solve() {
    PV a, b;
    Circle c;
    cin >> a >> b >> c;
    auto seg = Segment::from_two_points(a, b);
    auto h = seg.dist(c.c);
    if (1.l * c.r - h <= eps) {
        cout << a.dist(b) << "\n";
        return;
    }
    ld ans = 1e9;
    auto p_tans1 = get_tangent_points(a, c), p_tans2 = get_tangent_points(b, c);
    for (auto t1: p_tans1) {
        for (auto t2: p_tans2) {
            auto v1 = (t1 - c.c), v2 = t2 - c.c;
            auto alpha = std::abs(std::atan2(v1 ^ v2, v1 * v2));
            ans = std::min(ans, a.dist(t1) + b.dist(t2) + alpha * c.r);
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cout << fixed << setprecision(10);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
