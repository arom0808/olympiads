#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <random>
#include <functional>

using namespace std;
using ld = long double;
using TimePoint = chrono::time_point<chrono::steady_clock, chrono::steady_clock::duration>;
double d_inf = numeric_limits<double>::infinity();
random_device dev;
auto seed = dev();
mt19937 rng(seed);
TimePoint start_t;

TimePoint get_current_time() {
    return chrono::steady_clock::now();
}

template<typename T>
inline T randint(T a, T b) {
    return uniform_int_distribution<T>(a, b)(rng);
}

inline bool randbool(double prob) {
    return bernoulli_distribution(prob)(rng);
}

struct PV {
    int32_t x = 0, y = 0;

    explicit PV(int32_t x = 0, int32_t y = 0) : x(x), y(y) {
    }

    [[nodiscard]] double dist(PV other) const {
        return std::sqrt(
            static_cast<double>(1ll * (x - other.x) * (x - other.x) + 1ll * (y - other.y) * (y - other.y)));
    }

    PV operator-(const PV &other) const { return PV{x - other.x, y - other.y}; }

    PV operator-() const { return PV(-x, -y); }

    int64_t operator*(const PV &other) const { return 1ll * x * other.x + 1ll * y * other.y; }

    int64_t operator^(const PV &other) const { return 1ll * x * other.y - 1ll * y * other.x; }
};

const int32_t maxn = 5e3;
double g[maxn][maxn];
PV raw_points[maxn];
int32_t n;

bool in_line_intersect(int32_t a, int32_t b, int32_t c, int32_t d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

bool is_intersect(int32_t ai, int32_t bi, int32_t ci, int32_t di) {
    PV a = raw_points[ai], b = raw_points[bi], c = raw_points[ci], d = raw_points[di];
    PV ab = b - a, ac = c - a, ad = d - a, cd = d - c;
    if ((ab ^ ac) == 0 && (ab ^ ad) == 0)
        return in_line_intersect(a.x, b.x, c.x, d.x) && in_line_intersect(a.y, b.y, c.y, d.y);
    return (ab ^ ac) * (ab ^ ad) <= 0 && (cd ^ -ac) * (cd ^ b - c) <= 0;
}

struct PathProps {
    double len = d_inf;
    int32_t intersect_cnt = maxn * maxn;

    bool operator<(const PathProps &other) const {
        if (intersect_cnt != other.intersect_cnt) return intersect_cnt < other.intersect_cnt;
        return len < other.len;
    }

    bool operator>(const PathProps &other) const {
        return other < *this;
    }

    bool operator>=(const PathProps &other) const {
        return !(*this < other);
    }

    bool operator<=(const PathProps &other) const {
        return !(*this > other);
    }
};

struct AnnealingChange {
    int32_t from, to;

    static AnnealingChange gen_rand() {
        int32_t from = randint(0, n - 2), to = randint(from + 2, n);
        return {from, to};
    }
};

struct Path {
    vector<int32_t> seq;
    PathProps props;

    explicit Path(bool fill = false) {
        seq.resize(n);
        if (fill) iota(seq.begin(), seq.end(), 0);
    }

    void upd_props() {
        props.len = 0, props.intersect_cnt = 0;
        for (int32_t i = 1; i < n; ++i) props.len += g[seq[i]][seq[i - 1]];
        for (int32_t i = 0; i + 1 < n; ++i)
            for (int32_t j = i + 2; j + 1 < n; ++j)
                props.intersect_cnt += is_intersect(seq[i], seq[i + 1], seq[j], seq[j + 1]);
    }

    void make_change(AnnealingChange change, bool rev = false) {
        std::reverse(next(seq.begin(), change.from), next(seq.begin(), change.to));
    }
};


Path best_path;

void Annealing(const function<pair<int32_t, bool>()> &time_check_f,
               const function<long double(int32_t)> &temp_on_time_f) {
    Path cur_p(true);
    shuffle(cur_p.seq.begin(), cur_p.seq.end(), rng);
    cur_p.upd_props();
    best_path = cur_p;
    auto [cur_time, can_continue] = time_check_f();
    long double t = temp_on_time_f(cur_time);
    while (can_continue) {
        PathProps pre_props = cur_p.props;
        AnnealingChange change = AnnealingChange::gen_rand();
        cur_p.make_change(change);
        cur_p.upd_props();
        if (cur_p.props < pre_props && !randbool(t)) {
            cur_p.make_change(change, true);
            cur_p.props = pre_props;
        }
        if (cur_p.props > best_path.props) best_path = cur_p;
        auto [_cur_time, _can_continue] = time_check_f();
        cur_time = _cur_time, can_continue = _can_continue;
        t = temp_on_time_f(cur_time);
    }
}

bool branch_and_boundary_time_check() {
    return chrono::duration_cast<chrono::milliseconds>(get_current_time() - start_t).count() < 4800;
}

bool used_rows[maxn], used_cols[maxn];
bool banned[maxn][maxn];


void branch_and_boundary_method(int32_t used_cnt = 0, long double len = 0) {
    if (used_cnt == n - 1) {
        if (len < best_path.props.len) {
        }
        return;
    }
}

int main() {
    start_t = get_current_time();
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int32_t i = 0; i < n; ++i) cin >> raw_points[i].x >> raw_points[i].y;
    for (int32_t i = 0; i < n; ++i)
        for (int32_t j = i + 1; j < n; ++j)
            g[i][j] = g[j][i] = raw_points[i].dist(raw_points[j]);
    auto annealing_time_check_f = []() {
        int32_t ms_time = chrono::duration_cast<chrono::milliseconds>(get_current_time() - start_t).count();
        return pair<int32_t, bool>{ms_time, ms_time < 2400};
    };
    auto temp_on_time_f = [](int32_t t) {
        return static_cast<long double>(t) / 2400;
    };
    Annealing(annealing_time_check_f, temp_on_time_f);
    for (int32_t i = 0; i < n; ++i) {
        cout << best_path.seq[i] + 1 << " ";
    }

    return 0;
}
