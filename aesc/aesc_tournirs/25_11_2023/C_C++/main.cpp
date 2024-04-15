#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

class Frac {
public:
    int64_t a, b;

    void simplify() {
        auto d = gcd(std::abs(a), std::abs(b));
        a /= d;
        b /= d;
    }

    Frac operator*(const Frac &other) const { return {a * other.a, b * other.b}; }

    Frac operator/(const Frac &other) const { return {a * other.b, b * other.a}; }

    Frac operator+(const Frac &other) const { return {a * other.b + other.a * b, b * other.b}; }

    Frac operator-(const Frac &other) const { return {a * other.b - other.a * b, b * other.b}; }

    Frac operator*(int64_t num) const { return {a * num, b}; }

    Frac operator/(int64_t num) const { return {a, b * num}; }

    Frac operator+(int64_t num) const { return {a + num * b, b}; }

    Frac operator-(int64_t num) const { return {a - num * b, b}; }

    bool operator==(int64_t num) const { return a == num * b; }

    bool operator<(int64_t num) const { return a < num * b; }

    bool operator<=(int64_t num) const { return a <= num * b; }

    bool operator>(int64_t num) const { return a > num * b; }

    bool operator>=(int64_t num) const { return a >= num * b; }

    bool operator<(const Frac &other) const { return a * other.b < other.a * b; }

    bool operator<=(const Frac &other) const { return a * other.b <= other.a * b; }

    bool operator>(const Frac &other) const { return a * other.b > other.a * b; }

    bool operator>=(const Frac &other) const { return a * other.b >= other.a * b; }

    bool operator!=(const Frac &other) const { return a * other.b != other.a * b; }

    Frac(int64_t a, int64_t b) : a(a), b(b) { simplify(); }

    Frac() : Frac(0, 1) {}
};

struct AlphaAct {
    Frac alpha;
    bool type;

    bool operator<(const AlphaAct &other) const {
        if (alpha != other.alpha) return alpha > other.alpha;
        if (type && !other.type) return true;
        return false;
    }
};

struct House {
    int64_t xl, yb, xr, yt;
};

int main() {
    int64_t p, n;
    cin >> p >> n;
    vector<House> houses(n);
    for (auto &[xl, yb, xr, yt]: houses) cin >> xl >> yb >> xr >> yt;
    sort(houses.begin(), houses.end(), [](const auto &h1, const auto &h2) {
        return h1.xl * h1.xl + h1.yb * h1.yb < h2.xl * h2.xl + h2.yb * h2.yb;
    });
    vector<char> status(n, 'n');
    for (int64_t i = 0; i < n; ++i) {
        if (status[i] == 'h') continue;
        Frac ta(houses[i].yt, houses[i].xl), ba(houses[i].yb, houses[i].xr);
        for (int64_t j = 0; j < n; ++j)
            if ((houses[j].xl >= houses[i].xr || houses[j].yb >= houses[i].yt) &&
                ta * houses[j].xl >= houses[j].yt && ba * houses[j].xr <= houses[j].yb)
                status[j] = 'h';
        multiset<AlphaAct> alphas;
        for (int64_t j = 0; j < n; ++j) {
            bool add = false;
            Frac ita1(houses[j].yt, houses[j].xl), ita2(houses[j].yb, houses[j].xr);
            if (houses[j].xl <= houses[i].xr && houses[j].yt <= houses[i].yt && ita1 < ta && ita1 > ba) add = true;
            if (houses[j].xr <= houses[i].xr && houses[j].yb <= houses[i].yt && ita2 < ta && ita2 > ba) add = true;
            if (add) {
                alphas.emplace(ita1, true);
                alphas.emplace(ita2, false);
            }
        }
        if (alphas.empty()) status[i] = 'v';
        else {
            status[i] = 'h';
            int64_t cc = 0;
            for (const auto &[alpha, type]: alphas) {
                if (alpha < ta && alpha > ba && cc == 0) status[i] = 'p';
                if (type) ++cc;
                else --cc;
                if (alpha < ta && alpha > ba && cc == 0) status[i] = 'p';
            }
        }
    }
    auto full = count(status.begin(), status.end(), 'v'), part = count(status.begin(), status.end(), 'p');
    if (p == 1) cout << full;
    else cout << full + part;
    return 0;
}
