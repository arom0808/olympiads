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
        return std::sqrt<Td>(sq_len());
    }

    inline Tr sq_dist(const TPV &b) const {
        return static_cast<Tr>(b.x - x) * (b.x - x) + static_cast<Tr>(b.y - y) * (b.y - y);
    }

    inline Td dist(const TPV &b) const {
        return sqrtl(sq_dist(b));
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
const ld eps = 1e-15;


namespace IntersectCheck {
    vector<mPV> polygon;
    mPV main_point;

    bool cmp(const mPV &a, const mPV &b) {
        return ((a - main_point) ^ (b - main_point)) > 0;
    }

    void init(const vector<mPV> &_polygon, int32_t k) {
        polygon = _polygon;
        main_point = polygon[k];
        polygon.erase(next(polygon.begin(), k));
        sort(polygon.begin(), polygon.end(), &cmp);
    }

    bool is_direct_free(mPV point) {
        auto it = lower_bound(polygon.begin(), polygon.end(), point, &cmp);
        return it == polygon.begin() || it == polygon.end();
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, k;
    cin >> n >> k, --k;
    vector<mPV> polygon(n);
    for (auto &[x, y]: polygon) cin >> x >> y;
    IntersectCheck::init(polygon, k);
    vector<ld> per_dist(n, -1);
    per_dist[k] = 0;
    ld nd = 0;
    for (int32_t i = k, tp = i % n, np = (i + 1) % n; i < k + n; ++i, tp = i % n, np = (i + 1) % n) {
        nd += polygon[tp].dist(polygon[np]);
        if (per_dist[np] < -eps || per_dist[np] > nd) per_dist[np] = nd;
    }
    nd = 0;
    for (int32_t i = k, tp = (i + n) % n, np = (i - 1 + n) % n;
         i > k - n; --i, tp = (i + n) % n, np = (i - 1 + n) % n) {
        nd += polygon[tp].dist(polygon[np]);
        if (per_dist[np] < -eps || per_dist[np] > nd) per_dist[np] = nd;
    }
    int32_t l = __lg(n) + 1;
    int32_t m;
    cin >> m;
    cout << fixed << setprecision(10);
    for (int32_t _ = 0; _ < m; ++_) {
        mPV p;
        cin >> p.x >> p.y;
        if (IntersectCheck::is_direct_free(p)) {
            cout << p.dist(polygon[k]) << "\n";
            continue;
        }
        auto my_cmp = [&polygon, p](int32_t a, int32_t b) {
            return ((polygon[a] - p) ^ (polygon[b] - p)) > 0;
        };
        int32_t i1 = 0, i2 = 0;
        array<int32_t, 3> cs1{}, cs2{};
        for (int32_t c = l - 1; c >= 0; --c) {
            cs1 = {(i1 - (1 << c) + n) % n, i1, (i1 + (1 << c)) % n};
            cs2 = {(i2 - (1 << c) + n) % n, i2, (i2 + (1 << c)) % n};
            i1 = *min_element(cs1.begin(), cs1.end(), my_cmp), i2 = *max_element(cs2.begin(), cs2.end(), my_cmp);
        }
        cout << std::min(p.dist(polygon[i1]) + per_dist[i1], p.dist(polygon[i2]) + per_dist[i2]) << "\n";
    }
    return 0;
}
