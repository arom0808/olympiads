#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
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
};

using mPV = PV<int32_t, int64_t, ld>;

bool is_in(const vector<mPV> &points, mPV p) {
    int32_t l = 1, r = points.size() - 1;
    while (l != r) {
        auto mid = (l + r) / 2;
        auto mr = (points[mid] - points.front()) ^ (p - points.front());
        if (mr > 0) l = mid + 1;
        else if (mr < 0) r = mid;
        else l = r = mid;
    }
    if (((points[l] - points.front()) ^ (p - points.front())) == 0 && l == 1) ++l;
    if (l == 1) return false;
    auto r1 = (points[l] - p) ^ (points[l - 1] - p), r2 = (points[l - 1] - p) ^ (points.front() - p),
            r3 = (points.front() - p) ^ (points[l] - p);
    return r1 <= 0 && r2 <= 0 && r3 <= 0;
}

int64_t twice_sq(const vector<mPV> &points) {
    int64_t sq = 0;
    for (int32_t i = 1; i + 1 < points.size(); ++i)
        sq += (points[i] - points.front()) ^ (points[i + 1] - points.front());
    return sq;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m, k;
    cin >> n;
    vector<vector<mPV>> polygons(n);
    for (auto &points: polygons) {
        cin >> k;
        points.resize(k);
        for (auto &[x, y]: points) cin >> x >> y;
    }
    sort(polygons.begin(), polygons.end(), [](const vector<mPV> &pa, const vector<mPV> &pb) {
        return is_in(pa, pb.front()) && !is_in(pb, pa.front());
    });
    vector<int64_t> sqs(n);
    for (int32_t i = 0; i < n; ++i) sqs[i] = twice_sq(polygons[i]);
    for (int32_t i = 0; i + 1 < n; ++i) sqs[i] -= sqs[i + 1];
    vector<bool> used(n);
    cin >> m;
    for (int32_t i = 0; i < m; ++i) {
        mPV p;
        cin >> p.x >> p.y;
        if (!is_in(polygons.front(), p)) continue;
        int32_t l = 0, r = n - 1;
        while (l != r) {
            int32_t mid = (l + r) / 2 + (l + r) % 2;
            if (is_in(polygons[mid], p)) l = mid;
            else r = mid - 1;
        }
        used[l] = true;
    }
    ld res = 0;
    for (int32_t i = 0; i < n; ++i) if (used[i]) res += sqs[i];
    cout << fixed << setprecision(1) << res / 2 << "\n";
    return 0;
}
