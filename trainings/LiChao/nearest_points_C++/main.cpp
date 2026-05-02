#include <iostream>
#include <cmath>
#include <cstdint>
#include <numeric>

using namespace std;

constexpr int64_t maxx = 2e5 + 1;
const int64_t inf = 1e9;

struct Fract {
    __int128 a, b;

    Fract() = default;

    Fract(__int128 a, __int128 b) : a(a), b(b) {
    }

    Fract operator-() const {
        return {-a, b};
    }

    Fract operator*(const Fract &other) const {
        return {a * other.a, b * other.b};
    }

    Fract operator*(const __int128 &val) const {
        return {a * val, b};
    }

    Fract operator/(const Fract &other) const {
        return {a * other.b, b * other.a};
    }

    Fract operator+(const Fract &other) const {
        return {a * other.b + other.a * b, b * other.b};
    }

    Fract operator+(const __int128 &val) const {
        return {a + (b * val), b};
    }

    Fract operator-(const Fract &other) const {
        return {a * other.b - other.a * b, b * other.b};
    }

    bool operator<(const Fract &other) const {
        return a * other.b < other.a * b;
    }

    bool operator>(const Fract &other) const {
        return a * other.b > other.a * b;
    }

    int64_t floor() const {
        if (a >= 0) return a / b;
        return -2;
        // return (a + b - 1) / b;
    }

    int64_t ceil() const {
        if (a >= 0) return (a + b - 1) / b;
        return -1;
        // return a / b;
    }
};

struct PV {
    int64_t x, y;
};

struct Line {
    Fract k, b;

    Fract get(int64_t x) const {
        return k * x + b;
    }

    static Line mid_perp(PV p1, PV p2) {
        auto x = Fract(p1.x + p2.x, 2), y = Fract(p1.y + p2.y, 2);
        auto a = Fract(p2.x - p1.x, 1), b = Fract(p2.y - p1.y, 1);
        Fract c = -a * x - b * y;
        return {(-a) / b, (-c) / b};
    }
};

namespace LiChaoTree {
    struct Node {
        Line top_line, bottom_line;

        void init() {
            top_line = Line(Fract(0, 1), Fract(inf, 1));
            bottom_line = Line(Fract(0, 1), Fract(0, 1));
        }
    };

    Node tree[maxx * 4];
    int64_t size;

    void _init(int64_t v, int64_t l, int64_t r) {
        if (l >= r) return;
        tree[v].init();
        if (r - l == 1) return;
        _init(v * 2, l, (l + r) / 2);
        _init(v * 2 + 1, (l + r) / 2, r);
    }

    void _add(int64_t v, int64_t l, int64_t r, Line cur, bool top) {
        if (l >= r) return;
        int64_t m = (l + r) / 2;
        bool a, b;
        if (top)
            a = cur.get(l) < tree[v].top_line.get(l),
                    b = cur.get(m) < tree[v].top_line.get(m);
        else
            a = cur.get(l) > tree[v].bottom_line.get(l),
                    b = cur.get(m) > tree[v].bottom_line.get(m);
        if (b) swap(cur, top ? tree[v].top_line : tree[v].bottom_line);
        if (r - l == 1) return;
        if (a != b) _add(v * 2, l, m, cur, top);
        else _add(v * 2 + 1, m, r, cur, top);
    }


    int64_t _get(int64_t v, int64_t l, int64_t r, int64_t x, bool top) {
        if (l >= r || l > x || x >= r) return inf;
        if (l == x && r == x + 1) {
            if (top) return tree[v].top_line.get(x).floor();
            return tree[v].bottom_line.get(x).ceil();
        }
        int64_t m = (l + r) / 2;
        if (top) {
            if (x < m) return std::min(tree[v].top_line.get(x).floor(), _get(v * 2, l, m, x, top));
            return std::min(tree[v].top_line.get(x).floor(), _get(v * 2 + 1, m, r, x, top));
        }
        if (x < m) return std::max(tree[v].bottom_line.get(x).ceil(), _get(v * 2, l, m, x, top));
        return std::max(tree[v].bottom_line.get(x).ceil(), _get(v * 2 + 1, m, r, x, top));
    }

    void init(int64_t _size) {
        size = _size;
        _init(1, 0, size);
    }

    void add(Line cur, bool top) {
        _add(1, 0, size, cur, top);
    }

    int64_t get(int64_t x, bool top) {
        return _get(1, 0, size, x, top);
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int64_t X, Y, k;
    cin >> X >> Y >> k;
    int64_t min_x = 0, max_x = X;
    LiChaoTree::init(X + 1);
    LiChaoTree::add(Line(Fract(0, 1), Fract(0, 1)), false);
    LiChaoTree::add(Line(Fract(0, 1), Fract(Y, 1)), true);
    PV p0, pi;
    cin >> p0.x >> p0.y;
    for (int64_t i = 1; i < k; ++i) {
        cin >> pi.x >> pi.y;
        if (p0.y == pi.y) {
            if (p0.x < pi.x) max_x = std::min<int64_t>(max_x, (p0.x + pi.x) / 2);
            else min_x = std::max<int64_t>(min_x, (p0.x + pi.x) / 2);
        } else {
            LiChaoTree::add(Line::mid_perp(p0, pi), p0.y < pi.y);
        }
    }
    int64_t ans = 0;
    for (int64_t x = min_x; x <= max_x; ++x) {
        ans += std::max<int64_t>(LiChaoTree::get(x, true) - LiChaoTree::get(x, false) + 1, 0);
    }
    cout << ans << "\n";
    return 0;
}
