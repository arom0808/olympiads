#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using ld = long double;

struct Mirror {
    int64_t v = 0;
    ld a = 0, b = 0;

    bool operator<(const Mirror &other) const {
//        return a < other.a;
        if (a != other.a) return a < other.a;
        return b < other.b;
    }
};


template<typename T>
class PV;

template<typename T>
struct Line {
    ld a = 0, b = 0, c = 0;

    Line() = default;

    Line(const PV<T> &p1, const PV<T> &p2);
};

template<typename T>
class PV {
public:
    T x = 0, y = 0;

    PV(T x1, T y1, T x2, T y2) : x(x2 - x1), y(y2 - y1) {}

    PV(T x, T y) : x(x), y(y) {}

    PV() = default;

    explicit PV(const Line<T> &line) : x(line.a), y(line.b) {}

    PV(const Line<T> &a, const Line<T> &b) {
        T div = (a.a * b.b - b.a * a.b);
        x = (a.b * b.c - b.b * a.c) / div;
        y = (a.c * b.a - b.c * a.a) / div;
    }

    void assign(T x1, T y1, T x2, T y2) { x = x2 - x1, y = y2 - y1; }

    T len() const { return sqrt(x * x + y * y); }

    T cos(const PV &other) const { return (*this) * other / len() / other.len(); }

    T sin(const PV &other) const { return (*this) ^ other / len() / other.len(); }

    T angle(const PV &other) const { return atan2((*this) ^ other, (*this) * other); }

    T dist(const Line<T> &line) const {
        return std::abs(line.a * x + line.b * y + line.c);
    }


    PV operator+(const PV &other) const { return {x + other.x, y + other.y}; }

    T operator*(const PV &other) const { return x * other.x + y * other.y; }

    T operator^(const PV &other) const { return x * other.y - y * other.x; }

    bool operator<(const PV &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

template<typename T>
Line<T>::Line(const PV<T> &p1, const PV<T> &p2) {
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = p2.x * p1.y - p1.x * p2.y;
}


int main() {
//    freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    const int64_t bl = 1e5, bh = 100;
    int64_t hl, hr, n;
    cin >> hl >> hr >> n;
    vector<Mirror> mirrs[2]; // 0 - bottom, 1 - top
    char c;
    for (int64_t i = 0, v, a, b; i < n; ++i) {
        cin >> v >> c >> a >> b;
        if (c == 'T') mirrs[1].emplace_back(v, a, b);
        else mirrs[0].emplace_back(v, a, b);
    }
    sort(mirrs[0].begin(), mirrs[0].end());
    sort(mirrs[1].begin(), mirrs[1].end());
    int64_t best_res = 0;
    vector<bool> used[2];
    used[0].resize(100);
    used[1].resize(100);
    for (int64_t i = -n; i <= n; ++i) {
        if (i == 0) continue;
        std::fill(used[0].begin(), used[0].end(), false);
        std::fill(used[1].begin(), used[1].end(), false);
        int64_t ry = hr;
        if (i < 0) ry = (i + 1) * bh + ((((i % 2) + 2) % 2 == 1) ? (-hr) : (hr - bh));
        else if (i > 0) ry = (i) * bh + ((i % 2 == 1) ? (bh - hr) : (hr));
        bool ok = true;
        int64_t now_res = 0;
        Line<ld> nl(PV<ld>(0, hl), PV<ld>(bl, ry));
        for (int64_t j = (i < 0 ? i + 1 : 1); j <= (i < 0 ? 0 : i); ++j) {
            Line<ld> sl(PV<ld>(0, bh * j), PV<ld>(bl, bh * j));
            PV insp(nl, sl);
            int64_t layer_id = ((j % 2) + 2) % 2;
//            int64_t m_id = distance(mirrs[layer_id].begin(), upper_bound(mirrs[layer_id].begin(), mirrs[layer_id].end(),
//                                                                         Mirror(0, insp.x, insp.x)));
            bool tok = false;
            for (int64_t id = 0; id < mirrs[layer_id].size(); ++id) {
                if (mirrs[layer_id][id].a <= insp.x &&
                    insp.x <= mirrs[layer_id][id].b && !used[layer_id][id]) {
                    now_res += mirrs[layer_id][id].v;
                    used[layer_id][id] = true;
                    tok = true;
                    break;
                }
            }
            if (!tok) {
                ok = false;
                break;
            }
        }
        if (ok && now_res > best_res) best_res = now_res;
    }
    cout << best_res;
    return 0;
}
