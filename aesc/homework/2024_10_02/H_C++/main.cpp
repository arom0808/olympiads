#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <random>
#include <functional>
#include <set>

using namespace std;
using TimePoint = chrono::time_point<chrono::steady_clock, chrono::steady_clock::duration>;
random_device dev;
// uint32_t seed = dev();
uint32_t seed = 4193433022;
mt19937 rng(seed);
TimePoint start_t;

inline TimePoint get_current_time() {
    return chrono::steady_clock::now();
}

template<typename T>
inline T randint(T a, T b) {
    return uniform_int_distribution<T>(a, b)(rng);
}

inline bool randbool(double prob) {
    return bernoulli_distribution(prob)(rng);
}

const int32_t maxn = 256;
int32_t n, k, ndk;
vector<int32_t> g[maxn];

struct MagSetProps {
    int32_t unbeaten_cnt = maxn;

    [[nodiscard]] int32_t energy() const {
        return unbeaten_cnt;
    }

    bool operator<(const MagSetProps &other) const { return unbeaten_cnt < other.unbeaten_cnt; }

    bool operator>(const MagSetProps &other) const { return other < *this; }

    bool operator>=(const MagSetProps &other) const { return !(*this < other); }

    bool operator<=(const MagSetProps &other) const { return !(*this > other); }
};

struct MagSet;

struct Change {
    int32_t pos, pre_num, new_num;

    static Change gen_rand(const MagSet &mag_set);
};

struct MagSet {
    vector<int32_t> vs, beat_cnt;
    set<int32_t> unused_vals;
    MagSetProps props;

    explicit MagSet(bool fill = false) {
        vs.resize(k), beat_cnt.resize(n);
        if (fill) iota(vs.begin(), vs.end(), 0);
    }

    void init() {
        vs.resize(k), beat_cnt.resize(n);
        iota(vs.begin(), vs.end(), 0);
    }

    void init_beats_and_unused_vals() {
        for (auto v: vs) {
            ++beat_cnt[v];
            for (auto u: g[v]) ++beat_cnt[u];
        }
        for (int32_t i = 0; i < n; ++i) unused_vals.insert(i);
        for (auto v: vs) unused_vals.erase(v);
    }

    void upd_props() {
        props.unbeaten_cnt = 0;
        for (auto bc: beat_cnt) if (!bc) ++props.unbeaten_cnt;
    }

    void add_del_val(int32_t v, bool del = false) {
        beat_cnt[v] += -2 * del + 1;
        for (auto u: g[v]) beat_cnt[u] += -2 * del + 1;
        if (del) unused_vals.insert(v);
        else unused_vals.erase(v);
    }

    void make_change(Change change, bool rev = false) {
        add_del_val(rev ? change.new_num : change.pre_num, true);
        vs[change.pos] = rev ? change.pre_num : change.new_num;
        add_del_val(rev ? change.pre_num : change.new_num);
    }
};

Change Change::gen_rand(const MagSet &mag_set) {
    int32_t pos = randint(0, k - 1), pre_num = mag_set.vs[pos], new_num =
            *next(mag_set.unused_vals.begin(), randint(0, n - k - 1));
    return {pos, pre_num, new_num};
}


MagSet best_set;

void Annealing(const function<int32_t()> &time_f,
               const function<double(int32_t)> &temp_on_time_f,
               const function<double(double, int32_t)> &prob_on_t_and_de_f) {
    MagSet cur_set(true);
    cur_set.init_beats_and_unused_vals();
    cur_set.upd_props();
    best_set = cur_set;
    auto cur_time = time_f();
    double t = temp_on_time_f(cur_time);
    while (cur_time < 970 && best_set.props.energy()) {
        MagSetProps pre_props = cur_set.props;
        Change change = Change::gen_rand(cur_set);
        cur_set.make_change(change);
        cur_set.upd_props();
        if (cur_set.props > pre_props && !
            randbool(prob_on_t_and_de_f(t, cur_set.props.energy() - pre_props.energy()))) {
            cur_set.make_change(change, true);
            cur_set.props = pre_props;
        }
        if (cur_set.props < best_set.props) best_set = cur_set;
        cur_time = time_f();
        t = temp_on_time_f(cur_time);
    }
}


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // freopen("input.txt", "r",stdin);
    cin >> n >> k;
    start_t = get_current_time();
    vector<int32_t> g1[maxn], g2[maxn];
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0, c; j < n; ++j) {
            cin >> c;
            if (c == 1) g1[i].push_back(j);
            else if (c == 2) g2[i].push_back(j);
        }
    }
    for (int32_t i = 0; i < n; ++i) g[i] = g1[i];
    auto time_f = []() {
        return chrono::duration_cast<chrono::milliseconds>(get_current_time() - start_t).count();
    };
    auto temp_on_time_f = [](int32_t t) {
        return std::exp(-static_cast<double>(t) / 400);
    };
    auto prob_on_t_and_de_f = [](double t, int32_t de) {
        return std::exp(static_cast<double>(-de) / t);
    };
    Annealing(time_f, temp_on_time_f, prob_on_t_and_de_f);
    if (!best_set.props.energy()) {
        cout << 1 << "\n" << k << "\n";
        for (auto el: best_set.vs) cout << el + 1 << " ";
        return 0;
    }
    start_t = get_current_time();
    for (int32_t i = 0; i < n; ++i) g[i] = g2[i];
    Annealing(time_f, temp_on_time_f, prob_on_t_and_de_f);
    if (!best_set.props.energy()) {
        cout << 2 << "\n" << k << "\n";
        for (auto el: best_set.vs) cout << el + 1 << " ";
        return 0;
    }
    cout << "0\n";
    return 0;
}
