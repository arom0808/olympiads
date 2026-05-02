#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>
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
        return std::sqrt<Td>(sq_len());
    }

    inline Tr sq_dist(const TPV &b) const {
        return static_cast<Tr>(b.x - x) * (b.x - x) + static_cast<Tr>(b.y - y) * (b.y - y);
    }

    inline Td dist(const TPV &b) const {
        return std::sqrt<Td>(sq_dist(b));
    }

    TPV operator-(const TPV &b) const {
        return TPV(b, (*this));
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
};

using mPV = PV<int32_t, int64_t, ld>;
using dPV = PV<ld, ld, ld>;

template<typename Tv>
class Line {
public:
    Tv a = 0, b = 0, c = 0;

    Line() = default;

    Line(Tv a, Tv b, Tv c) : a(a), b(b), c(c) {}

    dPV get_point() const {
        if (a != 0) return dPV(-static_cast<ld>(c) / a, 0);
        return dPV(0, -static_cast<ld>(c) / b);
    }
};

using mLine = Line<int32_t>;

vector<mPV> gen_hull(vector<mPV> &points) {
    auto s_p = *std::min_element(points.begin(), points.end(), &mPV::cmp_y_x);
    std::sort(points.begin(), points.end(), [s_p](const mPV &a, const mPV &b) {
        if (a == b || b == s_p) return false;
        if (a == s_p) return true;
        auto vmr = (a - s_p) ^ (b - s_p);
        if (vmr != 0) return vmr > 0;
        return s_p.sq_dist(a) < s_p.sq_dist(b);
    });
    points.erase(std::unique(points.begin(), points.end()), points.end());
    vector<mPV> hull;
    for (auto p: points) {
        while (hull.size() >= 2) {
            if (((p - hull.back()) ^ (hull.back() - hull[hull.size() - 2])) >= 0) hull.pop_back();
            else break;
        }
        hull.push_back(p);
    }
    return hull;
}

const ld eps = 1e-15;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    freopen("highways.in", "r", stdin);
    freopen("highways.out", "w", stdout);
    int32_t n, m;
    cin >> n >> m;
    vector<mLine> ways(n);
    for (auto &[a, b, c]: ways) cin >> a >> b >> c;
    vector<mPV> points(m);
    for (auto &[x, y]: points) cin >> x >> y;
    auto hull = gen_hull(points); // min(y,x) - already first
    vector<mPV> edges(hull.size());
    for (int32_t i = 0; i < hull.size(); ++i) edges[i] = hull[(i + 1) % hull.size()] - hull[i];
    vector<int32_t> res;
    for (int32_t i = 0; i < n; ++i) {
        auto [a, b, c] = ways[i];
        array<mPV, 2> cv{mPV(-b, a), mPV(b, -a)};
        array<int32_t, 2> np{0, 0};
        for (int32_t j = 0; j < 2; ++j)
            np[j] = distance(edges.begin(), lower_bound(edges.begin(), edges.end(), cv[j], &mPV::cmp_polar_angle)) %
                    edges.size();
        dPV pt = ways[i].get_point();
        ld r1 = (static_cast<dPV>(hull[np[0]]) - pt) ^ static_cast<dPV>(cv[0]),
                r2 = (static_cast<dPV>(hull[np[1]]) - pt) ^ static_cast<dPV>(cv[0]);
        if (r1 <= eps && r2 >= -eps || r1 >= -eps && r2 <= eps) res.push_back(i);
    }
    cout << res.size() << "\n";
    for (auto v: res) cout << v + 1 << " ";
    return 0;
}
