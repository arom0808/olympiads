#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <random>
#include <functional>

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

const int32_t maxn = 200;
int32_t n, k, ndk;

struct PathProps {
    int32_t dif_sum = maxn * maxn;

    [[nodiscard]] int32_t energy() const {
        return dif_sum;
    }

    bool operator<(const PathProps &other) const { return dif_sum < other.dif_sum; }

    bool operator>(const PathProps &other) const { return other < *this; }

    bool operator>=(const PathProps &other) const { return !(*this < other); }

    bool operator<=(const PathProps &other) const { return !(*this > other); }
};

struct Change {
    int32_t first, second;

    static Change gen_rand() {
        int32_t first = randint(0, n - 2), second = randint(first + 1, n - 1);
        return {first, second};
    }
};

struct Path {
    vector<int32_t> seq;
    PathProps props;

    explicit Path(bool fill = false) {
        seq.resize(n);
        if (fill) iota(seq.begin(), seq.end(), 1);
    }

    void init() {
        seq.resize(n);
        iota(seq.begin(), seq.end(), 1);
    }

    void upd_props() {
        props.dif_sum = 0;
        int32_t ref_val = n * (n + 1) / 2 / k;
        for (int32_t i = 0; i < n; i += ndk)
            props.dif_sum += std::abs(ref_val - accumulate(next(seq.begin(), i), next(seq.begin(), i + ndk), 0));
    }

    void make_change(Change change, bool rev = false) {
        std::swap(seq[change.first], seq[change.second]);
    }
};


Path best_path;

void Annealing(const function<int32_t()> &time_f,
               const function<double(int32_t)> &temp_on_time_f,
               const function<double(double, int32_t)> &prob_on_t_and_de_f) {
    Path cur_p(true);
    shuffle(cur_p.seq.begin(), cur_p.seq.end(), rng);
    cur_p.upd_props();
    best_path = cur_p;
    auto cur_time = time_f();
    double t = temp_on_time_f(cur_time);
    while (cur_time < 970) {
        PathProps pre_props = cur_p.props;
        Change change = Change::gen_rand();
        cur_p.make_change(change);
        cur_p.upd_props();
        if (cur_p.props > pre_props && !randbool(prob_on_t_and_de_f(t, cur_p.props.energy() - pre_props.energy()))) {
            cur_p.make_change(change, true);
            cur_p.props = pre_props;
        }
        if (cur_p.props < best_path.props) best_path = cur_p;
        cur_time = time_f();
        t = temp_on_time_f(cur_time);
    }
}


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    cin >> n >> k;
    ndk = n / k;
    if (n * (n + 1) / 2 % k != 0) {
        cout << "0\n";
        return 0;
    }
    start_t = get_current_time();
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
    if (best_path.props.energy()) cout << "0\n";
    else for (int32_t i = 0; i < n; ++i) cout << best_path.seq[i] << " " << ((i + 1) % ndk ? "" : "\n");
    // cout << "\n" << time_f();
    // cout << "\nseed:" << seed << "\n";
    return 0;
}
