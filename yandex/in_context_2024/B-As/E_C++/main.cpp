#include <iostream>
#include <cmath>
#include <vector>
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
int32_t n;
vector<mPV> points;

bool fpc(int32_t id) {
    return (mPV(1, 0) ^ (points[(id - 1 + n) % n] - points[id])) >= 0 &&
           (mPV(1, 0) ^ (points[(id + 1) % n] - points[id])) >= 0;
}

bool spc(int32_t id) {
    return ((points[id] - points[(id - 1 + n) % n]) ^ (points[(id + 1) % n] - points[id])) >= 0;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    points.resize(n);
    for (auto &[x, y]: points) cin >> x >> y;
    for (int32_t i = 0; i < points.size(); ++i) {
        while (i < points.size() && ((points[i] - points[(i - 1 + points.size()) % points.size()]) ^
                                     (points[(i + 1) % points.size()] - points[i])) == 0) {
            points.erase(next(points.begin(), i));
        }
    }
    n = points.size();
    if (points.front().y == points.back().y && points.front().x > points.back().x) {
        points.insert(points.begin(), points.back());
        points.pop_back();
    }
    int32_t ans = 0;
    for (int32_t i = 0; i < n; ++i) {
        if (points[i].y == points[(i + 1) % n].y) {
            if (fpc(i) && spc(i) && fpc((i + 1) % n) && spc((i + 1) % n)) ++ans;
            ++i;
            continue;
        }
        if (fpc(i) && spc(i)) ++ans;
    }
    cout << ans;
    return 0;
}
