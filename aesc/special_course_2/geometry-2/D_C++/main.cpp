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

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    mPV a{1, 0}, b{2, 0};
//    cout << (a * b);
    int32_t n, m, k;
    cin >> n >> m >> k;
    vector<mPV> points(n);
    for (auto &[x, y]: points) cin >> x >> y;
    int32_t res = 0;
    for (int32_t i = 0; i < m; ++i) {
        mPV p;
        cin >> p.x >> p.y;
        int32_t l = 1, r = points.size() - 1;
        while (l != r) {
            auto mid = (l + r) / 2;
            auto mr = (points[mid] - points.front()) ^ (p - points.front());
            if (mr > 0) l = mid + 1;
            else if (mr < 0) r = mid;
            else l = r = mid;
        }
        if (((points[l] - points.front()) ^ (p - points.front())) == 0 && l == 1) ++l;
        if (l == 1) continue;
        auto r1 = (points[l] - p) ^ (points[l - 1] - p), r2 = (points[l - 1] - p) ^ (points.front() - p),
                r3 = (points.front() - p) ^ (points[l] - p);
        if (r1 <= 0 && r2 <= 0 && r3 <= 0) ++res;
    }
    cout << (res >= k ? "YES" : "NO");
    return 0;
}
