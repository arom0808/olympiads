#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>
#include <random>
#include <algorithm>

using namespace std;

random_device dev;
uint32_t seed = dev();
mt19937 rng(seed);

const int64_t inf = numeric_limits<int64_t>::max();

template<typename T>
class PV {
public:
    T x, y;

    PV<T> operator*(T k) const { return {x * k, y * k}; }

    PV<T> operator/(T k) const { return {x / k, y / k}; }

    PV<T> operator+(const PV<T> &other) const { return {x + other.x, y + other.y}; }

    PV<T> operator-(const PV<T> &other) const { return {x - other.x, y - other.y}; }

    PV<T> &operator=(const PV<T> &other) = default;

    template<typename K>
    PV<T> &operator=(const PV<K> &other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    [[nodiscard]] inline T sqlen() const { return x * x + y * y; }

    [[nodiscard]] inline T sqdist(const PV<T> &other) const {
        return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
    }

    bool operator<(const PV<T> &other) const { return x != other.x ? x < other.x : y < other.y; }

    PV(T x, T y) : x(x), y(y) {}

    PV() : PV(0, 0) {}

    template<typename K>
    PV(const PV<K> &other): x(other.x), y(other.y) {}
};

using PVi = PV<int64_t>;
using PVd = PV<long double>;

struct Circle {
    PVd center;
    long double sq_r = 0;

    [[nodiscard]] bool isin(const PVd &p) const { return center.sqdist(p) <= sq_r; }

    void build(const PVd &p1, const PVd &p2) {
        center = (p1 + p2) / 2;
        sq_r = center.sqdist(p1);
    }

    void build(const PVd &p1, const PVd &p2, const PVd &p3) {
        auto a = p2.x - p1.x, b = p2.y - p1.y, c = p3.x - p1.x, d = p3.y - p1.y;
        auto e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
        auto f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
        auto g = (a * (p3.y - p2.y) - b * (p3.x - p2.x)) * 2;
        if (g == 0) {
            auto d1 = p1.sqdist(p2), d2 = p2.sqdist(p3), d3 = p1.sqdist(p3);
            if (d1 >= d2 && d1 >= d3) build(p1, p2);
            else if (d2 >= d1 && d2 >= d3) build(p2, p3);
            else build(p1, p3);
        } else {
            center = {(d * e - b * f) / g, (a * f - c * e) / g};
            sq_r = center.sqdist(p1);
        }
    }

    Circle(const PVd &p1, const PVd &p2) { build(p1, p2); }

    Circle(const PVd &p1, const PVd &p2, const PVd &p3) { build(p1, p2, p3); }

    Circle(PVd center, long double sq_r) : center(center), sq_r(sq_r) {}

    Circle() : Circle(PVd(), 0) {}
};

void MinDisk2(vector<PVd>::iterator beg, vector<PVd>::iterator end, PVd q1, PVd q2, Circle &nc) {
    shuffle(beg, end, rng);
    if (beg == end) nc.build(q1, q2);
    else {
        nc.build(*beg, q1, q2);
        for (auto it = std::next(beg); it != end; ++it) if (!nc.isin(*it)) nc.build(*it, q1, q2);
    }
}

void MinDisk1(vector<PVd>::iterator beg, vector<PVd>::iterator end, PVd q1, Circle &nc) {
    shuffle(beg, end, rng);
    if (beg == end) nc.build(q1, q1);
    else {
        nc.build(*beg, q1);
        for (auto it = std::next(beg); it != end; ++it) if (!nc.isin(*it)) MinDisk2(beg, it, *it, q1, nc);
    }
}

void MinDisk(vector<PVd>::iterator beg, vector<PVd>::iterator end, Circle &nc) {
    shuffle(beg, end, rng);
    nc.build(*beg, *std::next(beg));
    for (auto it = std::next(beg, 2); it != end; ++it) if (!nc.isin(*it)) MinDisk1(beg, it, *it, nc);
}

Circle MultiMinDisk(vector<PVd>::iterator beg, vector<PVd>::iterator end) {
    Circle best, now;
    MinDisk(beg, end, best);
    for (std::uint32_t i = 0; i < 5; ++i) {
        MinDisk(beg, end, now);
        if (now.sq_r < best.sq_r) best = now;
    }
    return best;
}

struct Ship {
    PVi start, speed;

    [[nodiscard]] PVi coords(int64_t t) const { return start + speed * t; }
};

struct TimeSec {
    int64_t start, finish;

    TimeSec &intersect(TimeSec other) {
        if (start > other.start) swap(*this, other);
        if (other.start > finish) start = finish = inf;
        else if (other.finish > finish) start = other.start;
        else *this = other;
        return *this;
    }


    TimeSec(int64_t start, int64_t finish) : start(start), finish(finish) {}

    TimeSec() : TimeSec(inf, inf) {}
};

TimeSec time_ok_dist(const Ship &s1, const Ship &s2, int64_t R) {
    long double a = s1.start.x - s2.start.x, b = s1.speed.x - s2.speed.x, c = s1.start.y - s2.start.y,
            d = s1.speed.y - s2.speed.y;
    auto da = b * b + d * d, db = 2 * a * b + 2 * c * d, dc = a * a + c * c - R * R;
    auto D = db * db - 4 * da * dc;
    if (D < 0) return {};
    auto dt1 = (-db - sqrt(D)) / 2 / da, dt2 = (-db + sqrt(D)) / 2 / da;
    if (dt1 > dt2) swap(dt1, dt2);
    int64_t t1 = floor(dt1), t2 = ceil(dt2);
    if (s1.coords(t1).sqdist(s2.coords(t1)) > R * R) ++t1;
    if (s1.coords(t2).sqdist(s2.coords(t2)) > R * R) --t2;
    if (t1 > t2 || t2 < 0) return {};
    if (t1 < 0) t1 = 0;
    return {t1, t2};
}

struct Bomb {
    int64_t time = 0;
    PVd coords;
};

Bomb get_bomb(const vector<Ship> &ships, int32_t mask,
              const vector<vector<TimeSec>> &time_secs, int32_t R) {
    if (mask == 0) return {inf, PVd()};
    auto f = __lg(mask);
    if (mask == (1 << f)) return {0, ships[f].start};
    vector<int32_t> to_del;
    to_del.reserve(10);
    while (mask) {
        to_del.push_back(__lg(mask & (~mask + 1)));
        mask = mask & (mask - 1);
    }
    TimeSec ts = time_secs[to_del[0]][to_del[1]];
    for (uint32_t i = 0; i + 1 < to_del.size(); ++i)
        for (uint32_t j = i + 1; j < to_del.size(); ++j)
            ts.intersect(time_secs[to_del[i]][to_del[j]]);
    if (ts.start == inf || ts.finish == inf) return {inf, PVd()};
    vector<PVd> ps(to_del.size());
    for (auto t = ts.start; t <= ts.finish; ++t) {
        for (uint32_t i = 0; i < to_del.size(); ++i) ps[i] = ships[to_del[i]].coords(t);
        auto nc = MultiMinDisk(ps.begin(), ps.end());
        if (nc.sq_r <= R * R) return {t, nc.center};
    }
    return {inf, PVd()};
}

inline int32_t count_set_bits(int32_t n) {
    int32_t res = 0;
    while (n) {
        n = n & (n - 1);
        ++res;
    }
    return res;
}

int main() {
    int32_t N, R;
    cin >> N >> R;
    vector<Ship> ships(N);
    for (auto &ship: ships) cin >> ship.start.x >> ship.start.y >> ship.speed.x >> ship.speed.y;
    vector<vector<TimeSec>> time_secs(N, vector<TimeSec>(N));
    for (uint32_t i = 0; i + 1 < N; ++i)
        for (uint32_t j = i + 1; j < N; ++j)
            time_secs[i][j] = time_secs[j][i] = time_ok_dist(ships[i], ships[j], R * 2);
    vector<Bomb> oks(1 << N, Bomb(0, PVd()));
    for (int32_t len = 1; len <= N; ++len) {
        int32_t mask = (1 << len) - 1, x, y;
        while (mask < (1 << N)) {
            if (oks[mask].time != inf) {
                oks[mask] = get_bomb(ships, mask, time_secs, R);
                if (oks[mask].time == inf) {
                    auto fm = (~mask) & ((1 << N) - 1), m = fm;
                    while (m > 0) {
                        oks[m | mask].time = inf;
                        m = (m - 1) & fm;
                    }
                    oks[m | mask].time = inf;
                }
            }
            x = mask & (-mask);
            y = mask + x;
            mask = ((mask & ~y) / x >> 1) | y;
        }
    }
    vector<Bomb> bombs;
    int32_t deleted = 0;
    while (deleted < (1 << N) - 1) {
        int32_t to_del = 0;
        for (int32_t i = 1; i < (1 << N); ++i)
            if (oks[i].time != inf && count_set_bits(deleted | to_del) < count_set_bits(deleted | i))
                to_del = i;
        bombs.push_back(oks[to_del]);
        deleted |= to_del;
    }
    cout << fixed << setprecision(25);
    cout << bombs.size() << "\n";
    for (const auto &bomb: bombs)
        cout << bomb.time << " " << bomb.coords.x << " " << bomb.coords.y << "\n";
    return 0;
}





//namespace OldSolution {
//    const int64_t inf = 1e18;
//
//    struct PV {
//        int64_t x, y;
//
//        PV operator*(int64_t k) const { return PV(x * k, y * k); }
//
//        PV operator+(const PV &other) const { return PV(x + other.x, y + other.y); }
//
//        PV operator-(const PV &other) const { return PV(x - other.x, y - other.y); }
//
//        PV &operator=(const PV &other) = default;
//
//        [[nodiscard]] inline int64_t sqlen() const { return x * x + y * y; }
//
//        explicit PV(int64_t x = 0, int64_t y = 0) : x(x), y(y) {}
//    };
//
//    struct PVd {
//        long double x, y;
//
//        PVd operator*(long double k) const { return PVd(x * k, y * k); }
//
//        PVd operator/(long double k) const { return PVd(x / k, y / k); }
//
//        PVd operator+(const PVd &other) const { return PVd(x + other.x, y + other.y); }
//
//        PVd operator-(const PVd &other) const { return PVd(x - other.x, y - other.y); }
//
//        [[nodiscard]] inline long double sqlen() const { return x * x + y * y; }
//
//        explicit PVd(long double x = 0, long double y = 0) : x(x), y(y) {}
//
//        explicit PVd(const PV &other) : x(other.x), y(other.y) {}
//
//        PVd &operator=(const PV &other) {
//            x = other.x;
//            y = other.y;
//            return *this;
//        }
//    };
//
//    struct Circle {
//        PVd center;
//        long double sq_r = 0;
//
//        [[nodiscard]] bool isin(const PVd &p) const { return (p - center).sqlen() <= sq_r; }
//
//        void build(const PVd &p1, const PVd &p2) {
//            center = (p1 + p2) / 2;
//            sq_r = ((p1 - p2) / 2).sqlen();
//        }
//
//        void build(const PVd &p1, const PVd &p2, const PVd &p3) {
//            auto a = p2.x - p1.x, b = p2.y - p1.y, c = p3.x - p1.x, d = p3.y - p1.y;
//            auto e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
//            auto f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
//            auto g = (a * (p3.y - p2.y) - b * (p3.x - p2.x)) * 2;
//            if (g == 0) {
//                Circle c1(p1, p2), c2(p2, p3), c3(p1, p3);
//                if (c1.sq_r < c2.sq_r) std::swap(c1, c2);
//                if (c1.sq_r < c3.sq_r) std::swap(c1, c2);
//                center = c1.center;
//                sq_r = c1.sq_r;
//            } else {
//                center = PVd((d * e - b * f) / g, (a * f - c * e) / g);
//                sq_r = (center - p1).sqlen();
//            }
//        }
//
//        Circle(const PVd &p1, const PVd &p2) { build(p1, p2); }
//
//        Circle(const PVd &p1, const PVd &p2, const PVd &p3) { build(p1, p2, p3); }
//
//        explicit Circle(PVd center = PVd(0, 0), long double sq_r = 0) : center(center), sq_r(sq_r) {}
//    };
//
//    void MinDisk2(vector<PVd>::const_iterator beg, vector<PVd>::const_iterator end, PVd q1, PVd q2, Circle &nc) {
//        if (beg == end) nc.build(q1, q2);
//        else {
//            nc.build(*beg, q1, q2);
//            for (auto it = std::next(beg); it != end; ++it) if (!nc.isin(*it)) nc.build(*it, q1, q2);
//        }
//    }
//
//    void MinDisk1(vector<PVd>::const_iterator beg, vector<PVd>::const_iterator end, PVd q1, Circle &nc) {
//        if (beg == end) nc.build(q1, q1);
//        else {
//            nc.build(*beg, q1);
//            for (auto it = std::next(beg); it != end; ++it) if (!nc.isin(*it)) MinDisk2(beg, it, *it, q1, nc);
//        }
//    }
//
//    void MinDisk(vector<PVd>::const_iterator beg, vector<PVd>::const_iterator end, Circle &nc) {
//        nc.build(*beg, *std::next(beg));
//        for (auto it = std::next(beg, 2); it != end; ++it) if (!nc.isin(*it)) MinDisk1(beg, it, *it, nc);
//    }
//
//    struct Ship {
//        PV start, speed;
//
////    [[nodiscard]] Line line() const { return Line(speed.y, -speed.x, start.y * speed.x - start.x * speed.y); }
//
//        [[nodiscard]] PV coords(int64_t t) const { return start + speed * t; }
//    };
//
//    struct TimeSec {
//        int64_t start, finish;
//
//        TimeSec &intersect(TimeSec other) {
//            if (start > other.start) std::swap(*this, other);
//            if (other.start > finish) start = finish = inf;
//            else if (other.finish > finish) start = other.start;
//            else *this = other;
//            return *this;
//        }
//
//        explicit TimeSec(int64_t start = inf, int64_t finish = inf) : start(start), finish(finish) {}
//    };
//
//    TimeSec time_ok_dist(const Ship &s1, const Ship &s2, int64_t R) {
//        long double a = s1.start.x - s2.start.x, b = s1.speed.x - s2.speed.x, c = s1.start.y - s2.start.y,
//                d = s1.speed.y - s2.speed.y;
//        auto da = b * b + d * d, db = 2 * a * b + 2 * c * d, dc = a * a + c * c - R * R;
//        auto D = db * db - 4 * da * dc;
//        if (D < 0) return TimeSec{inf, inf};
//        auto dt1 = (-db - sqrt(D)) / 2 / da, dt2 = (-db + sqrt(D)) / 2 / da;
//        if (dt1 > dt2) swap(dt1, dt2);
//        int64_t t1 = floor(dt1), t2 = ceil(dt2);
//        if ((s1.coords(t1) - s2.coords(t1)).sqlen() > R * R) ++t1;
//        if ((s1.coords(t2) - s2.coords(t2)).sqlen() > R * R) --t2;
//        if (t1 > t2 || t2 < 0) return TimeSec{inf, inf};
//        if (t1 < 0) t1 = 0;
//        return TimeSec{t1, t2};
//    }
//
//    struct Bomb {
//        int64_t time;
//        PVd coords;
//    };
//
//    vector<Bomb> sol(int32_t N, int32_t R, vector<Ship> ships) {
//        vector<vector<TimeSec>> time_secs(N, vector<TimeSec>(N));
//        for (std::uint32_t i = 0; i + 1 < N; ++i)
//            for (std::uint32_t j = i + 1; j < N; ++j)
//                time_secs[i][j] = time_secs[j][i] = time_ok_dist(ships[i], ships[j], R * 2);
//        vector<Bomb> bombs;
//        while (!ships.empty()) {
//            vector<uint32_t> inds(ships.size());
//            std::set<uint32_t> to_del;
//            std::iota(inds.begin(), inds.end(), 0);
//            vector<PVd> ps(ships.size());
//            Circle nc;
//            bool deled = false;
//            for (std::uint32_t len = ships.size(); len > 1; --len) {
//                do {
//                    TimeSec ts = time_secs[inds[0]][inds[1]];
//                    for (std::uint32_t i = 0; i + 1 < len; ++i)
//                        for (std::uint32_t j = i + 1; j < len; ++j)
//                            ts.intersect(time_secs[inds[i]][inds[j]]);
//                    if (ts.start == inf || ts.finish == inf) continue;
//                    for (auto t = ts.start; t <= ts.finish; ++t) {
//                        for (std::uint32_t i = 0; i < len; ++i) ps[i] = ships[inds[i]].coords(t);
//                        MinDisk(ps.begin(), std::next(ps.begin(), len), nc);
//                        if (nc.sq_r < R * R) {
//                            to_del.clear();
//                            for (std::uint32_t i = 0; i < len; ++i) to_del.insert(inds[i]);
//                            bombs.emplace_back(t, nc.center);
//                            deled = true;
//                            break;
//                        }
//                    }
//                    if (deled) break;
//                } while (std::next_permutation(inds.begin(), inds.end()));
//                if (deled) break;
//            }
//            if (deled) {
//                vector<Ship> new_ships;
//                for (std::uint32_t i = 0; i < ships.size(); ++i)
//                    if (to_del.find(i) == to_del.end())
//                        new_ships.push_back(ships[i]);
//                ships = new_ships;
//            } else {
//                for (const auto &ship: ships) bombs.emplace_back(0, PVd(ship.start));
//                ships.clear();
//            }
//        }
//        return bombs;
//    }
//}
//
//
//namespace Test {
//    uint32_t seed = random_device()();
//    auto rng = mt19937(seed);
//
//    int32_t randint(int32_t a, int32_t b) { return uniform_int_distribution(a, b)(rng); }
//
//    struct Ins {
//        int32_t N, R;
//        vector<GoodSolution::Ship> good_ships;
//        vector<OldSolution::Ship> old_ships;
//    };
//
//    Ins gen() {
//        int32_t N = randint(1, 3), R = randint(1, 10);
//        vector<GoodSolution::Ship> ships(N);
//        set<GoodSolution::PVi> speeds;
//
//        for (auto &ship: ships) {
//            ship.start.x = randint(-10, 10);
//            ship.start.y = randint(-10, 10);
//            do {
//                ship.speed.x = randint(-10, 10);
//                ship.speed.y = randint(-10, 10);
//            } while (speeds.find(ship.speed) != speeds.end());
//            speeds.insert(ship.speed);
//        }
//        vector<OldSolution::Ship> old_ships;
//        for (const auto &ship: ships)
//            old_ships.emplace_back(OldSolution::PV(ship.start.x, ship.start.y),
//                                   OldSolution::PV(ship.speed.x, ship.speed.y));
//        return {N, R, ships, old_ships};
//    }
//
//    void print_ins(const Ins &ins) {
//        cout << ins.N << " " << ins.R << "\n";
//        for (const auto &ship: ins.good_ships)
//            cout << ship.start.x << " " << ship.start.y << " " << ship.speed.x << " " << ship.speed.y << "\n";
//    }
//
//    void print_res(const vector<GoodSolution::Bomb> &bombs) {
//        cout << bombs.size() << "\n";
//        for (const auto &bomb: bombs) cout << bomb.time << " " << bomb.coords.x << " " << bomb.coords.y << "\n";
//    }
//
//    void Test() {
//        while (true) {
//            auto ins = gen();
//            print_ins(ins);
//            cout << "\n";
//            auto a = GoodSolution::sol(ins.N, ins.R, ins.good_ships);
//            auto b = OldSolution::sol(ins.N, ins.R, ins.old_ships);
//            if (a.size() != b.size()) {
//                break;
//            }
//            cout << "\n\n";
//        }
//    }
//}




//    vector<Bomb> bombs;
//    while (!ships.empty()) {
//        vector<uint32_t> inds(ships.size());
//        set<uint32_t> to_del;
//        iota(inds.begin(), inds.end(), 0);
//        vector<PVd> ps(ships.size());
//        Circle nc;
//        bool deled = false;
//        for (uint32_t len = ships.size(); len > 1; --len) {
//            do {
//                TimeSec ts = time_secs[inds[0]][inds[1]];
//                for (uint32_t i = 0; i + 1 < len; ++i)
//                    for (uint32_t j = i + 1; j < len; ++j)
//                        ts.intersect(time_secs[inds[i]][inds[j]]);
//                if (ts.start == inf || ts.finish == inf) continue;
//                for (auto t = ts.start; t <= ts.finish; ++t) {
//                    for (uint32_t i = 0; i < len; ++i) ps[i] = ships[inds[i]].coords(t);
//                    MinDisk(ps.begin(), next(ps.begin(), len), nc);
//                    if (nc.sq_r < R * R) {
//                        to_del.clear();
//                        for (uint32_t i = 0; i < len; ++i) to_del.insert(inds[i]);
//                        bombs.emplace_back(t, nc.center);
//                        deled = true;
//                        break;
//                    }
//                }
//                if (deled) break;
//            } while (next_permutation(inds.begin(), inds.end()));
//            if (deled) break;
//        }
//        if (deled) {
//            vector<Ship> new_ships;
//            for (uint32_t i = 0; i < ships.size(); ++i)
//                if (to_del.find(i) == to_del.end())
//                    new_ships.push_back(ships[i]);
//            ships = new_ships;
//        } else {
//            for (const auto &ship: ships) bombs.emplace_back(0, PVd(ship.start));
//            ships.clear();
//        }
//    }
//    cout << fixed << setprecision(20);
//    cout << bombs.size() << "\n";
//    for (const auto &bomb: bombs)
//        cout << bomb.time << " " << bomb.coords.x << " " << bomb.coords.y << "\n";





//struct PVd {
//    long double x, y;
//
//    explicit PVd(long double x = 0, long double y = 0) : x(x), y(y) {}
//};

//struct Line {
//    int64_t a, b, center;
//
//    [[nodiscard]] PVd intersect(const Line &other) const {
//        return PVd(-static_cast<long double>(center * other.b - other.center * b) / (a * other.b - other.a * b),
//                   -static_cast<long double>(a * other.center - other.a * center) / (a * other.b - other.a * b));
//    }
//
//    explicit Line(int64_t a, int64_t b, int64_t center) : a(a), b(b), center(center) {}
//};

//long double time_min_dist(const Ship &s1, const Ship &s2) {
//    long double a = s1.start.x, b = s1.speed.x, center = s2.start.x, d = s2.speed.x, e = s1.start.y, f = s1.speed.y, g = s2.start.y, h = s2.speed.y;
//    long double k = -(2 * g - 2 * e) * h + 2 * f * g - 2 * e * f - (2 * center - 2 * a) * d + 2 * b * center - 2 * a * b;
//    long double l = 2 * h * h - 4 * f * h + 2 * f * f + 2 * d * d - 4 * b * d + 2 * b * b;
//    return k / l;
//}


//    auto tmd = time_min_dist(s1, s2);
//    int64_t mid_t = floor(tmd);
//    if (mid_t < 0) mid_t = 0;
//    if ((s1.coords(mid_t) - s2.coords(mid_t)).sqlen() > R * R) ++mid_t;
//    if ((s1.coords(mid_t) - s2.coords(mid_t)).sqlen() > R * R) return {inf, inf};
//    int64_t l = 0, r = mid_t;
//    while (l != r) {
//        int64_t m = (l + r) / 2;
//        if ((s1.coords(m) - s2.coords(m)).sqlen() > R * R) l = m + 1;
//        else r = m;
//    }
//    int64_t min_t = l;
//    l = mid_t;
//    r = 1e9;
//    while (l != r) {
//        int64_t m = (l + r) / 2 + (l + r) % 2;
//        if ((s1.coords(m) - s2.coords(m)).sqlen() > R * R) r = m - 1;
//        else l = m;
//    }
//    int64_t max_t = l;
//    return {min_t, max_t};

