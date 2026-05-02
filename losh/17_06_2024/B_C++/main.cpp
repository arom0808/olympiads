#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

using ld = long double;

struct Line {
    int32_t a, b, c;
    ld la, lb, lc, dist_div;

    void compute_dist_div() {
        dist_div = std::sqrt(la * la + lb * lb);
    }
};

template<typename T>
class PV {
public:
    T x = 0, y = 0;

    PV(T x1, T y1, T x2, T y2) : x(x2 - x1), y(y2 - y1) {}

    PV(T x, T y) : x(x), y(y) {}

    PV() = default;

    explicit PV(const Line &line) : x(line.a), y(line.b) {}

    PV(const Line &a, const Line &b) {
        T div = (a.la * b.lb - b.la * a.lb);
        x = (a.lb * b.lc - b.lb * a.lc) / div;
        y = (a.lc * b.la - b.lc * a.la) / div;
    }

    void assign(T x1, T y1, T x2, T y2) { x = x2 - x1, y = y2 - y1; }

    T len() const { return sqrt(x * x + y * y); }

    T cos(const PV &other) const { return (*this) * other / len() / other.len(); }

    T sin(const PV &other) const { return (*this) ^ other / len() / other.len(); }

    T angle(const PV &other) const { return atan2((*this) ^ other, (*this) * other); }

    T dist(const Line &line) const {
        return std::abs(line.la * x + line.lb * y + line.lc);
    }


    PV operator+(const PV &other) const { return {x + other.x, y + other.y}; }

    T operator*(const PV &other) const { return x * other.x + y * other.y; }

    T operator^(const PV &other) const { return x * other.y - y * other.x; }

    bool operator<(const PV &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

const int32_t maxn = 1e5, maxt = 20;
Line trains[maxn], routes[maxt];
int32_t n, t;
ld results[maxt];

//void process_train(int16_t u, int16_t v, int32_t w) {
//
//}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (auto &r: results) r = 1e300;
    cin >> n >> t;
    for (int32_t i = 0; i < n; ++i) {
        auto &[a, b, c, la, lb, lc, dist_div] = trains[i];
        cin >> a >> b >> c, la = a, lb = b, lc = c;
//        trains[i].compute_dist_div();
    }
    for (int32_t i = 0; i < t; ++i) {
        auto &[u, v, w, lu, lv, lw, dist_div] = routes[i];
        cin >> u >> v >> w, lu = u, lv = v, lw = w;
        routes[i].compute_dist_div();
    }
    vector<pair<PV<ld>, int32_t>> ins;
    for (int32_t i = 0; i < t; ++i) {
        ins.clear();
        for (int32_t j = 0; j < n; ++j) ins.emplace_back(PV<ld>(routes[i], trains[j]), j);
        sort(ins.begin(), ins.end());
        for (int32_t j = 0; j + 1 < n; ++j) {
            PV<ld> intersect_point(trains[ins[j].second], trains[ins[j + 1].second]);
            auto dist = intersect_point.dist(routes[i]);
            if (dist < results[i]) results[i] = dist;
        }
    }
//    for (int32_t i = 0; i < n; ++i) {
//        for (int32_t j = i + 1; j < n; ++j) {
//            if (trains[i].a * trains[j].b == trains[j].a * trains[i].b) continue;
////            auto &a = trains[i], &b = trains[j];
////            auto div = (a.la * b.lb - b.la * a.lb);
////            auto x = (a.lb * b.lc - b.lb * a.lc) / div;
////            auto y = (a.lc * b.la - b.lc * a.la) / div;
//            PV<double> intersect_point(trains[i], trains[j]);
//            for (int32_t route = 0; route < t; ++route) {
//                auto dist = intersect_point.dist(routes[route]);
////                auto dist = std::abs(routes[route].la * x + routes[route].lb * y + routes[route].lc);
//                if (dist < results[route]) results[route] = dist;
//            }
//        }
//    }
    for (int32_t i = 0; i < t; ++i) {
        cout << fixed << setprecision(20) << results[i] / routes[i].dist_div << "\n";
    }
    return 0;
}
