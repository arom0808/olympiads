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
    int32_t n;
    cin >> n;
    vector<mPV> points(n);
    for (auto &[x, y]: points) cin >> x >> y;
    auto s_p = *std::min_element(points.begin(), points.end(), [](const mPV &a, const mPV &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    std::sort(points.begin(), points.end(), [s_p](const mPV &a, const mPV &b) {
        if (a == b) return false;
        if (b == s_p) return false;
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
    ld sq = 0;
    for (int32_t i = 1; i + 1 < hull.size(); ++i) sq += (hull[i] - s_p) ^ (hull[i + 1] - s_p);
    cout << hull.size() << "\n";
    for (auto [x, y]: hull) cout << x << " " << y << "\n";
    cout << fixed << setprecision(1) << sq / 2 << "\n";
    return 0;
}
