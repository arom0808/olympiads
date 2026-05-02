#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <random>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using TimePoint = chrono::time_point<chrono::steady_clock, chrono::steady_clock::duration>;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
random_device dev;
// uint32_t seed = dev();
uint32_t seed = 231524142;
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

const int32_t maxn = 2000;
int32_t n, m, k;
vector<int32_t> g[maxn];

struct MagSetProps {
    int32_t unbeaten_edges_cnt = maxn;

    [[nodiscard]] int32_t energy() const {
        return unbeaten_edges_cnt;
    }

    bool operator<(const MagSetProps &other) const { return unbeaten_edges_cnt < other.unbeaten_edges_cnt; }

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
    vector<int32_t> vs, beat_edge_cnt;
    ordered_set<int32_t> unused_verts;
    MagSetProps props;

    explicit MagSet(bool fill = false) {
        vs.resize(k), beat_edge_cnt.resize(m);
        if (fill) {
            for (int32_t i = 0; i < n; ++i) unused_verts.insert(i);
            for (int32_t i = 0; i < k; ++i) {
                vs[i] = *unused_verts.find_by_order(randint(0, n - i - 1));
                unused_verts.erase(vs[i]);
            }
        }
    }

    void init() {
        vs.resize(k), beat_edge_cnt.resize(m);
        iota(vs.begin(), vs.end(), 0);
    }

    void init_beats_props() {
        for (auto v: vs) for (auto u: g[v]) ++beat_edge_cnt[u];
        props.unbeaten_edges_cnt = 0;
        for (auto bc: beat_edge_cnt) if (!bc) ++props.unbeaten_edges_cnt;
    }

    void add_del_val(int32_t v, bool del = false) {
        for (auto u: g[v]) {
            if (!beat_edge_cnt[u]) --props.unbeaten_edges_cnt;
            beat_edge_cnt[u] += -2 * del + 1;
            if (!beat_edge_cnt[u]) ++props.unbeaten_edges_cnt;
        }
        if (del) unused_verts.insert(v);
        else unused_verts.erase(v);
    }

    void make_change(Change change, bool rev = false) {
        add_del_val(rev ? change.new_num : change.pre_num, true);
        vs[change.pos] = rev ? change.pre_num : change.new_num;
        add_del_val(rev ? change.pre_num : change.new_num);
    }
};

Change Change::gen_rand(const MagSet &mag_set) {
    int32_t pos = randint(0, k - 1), pre_num = mag_set.vs[pos], new_num =
            *mag_set.unused_verts.find_by_order(randint(0, n - k - 1));
    return {pos, pre_num, new_num};
}


MagSet best_set;

void Annealing(const function<int32_t()> &time_f,
               const function<double(int32_t)> &temp_on_time_f,
               const function<double(double, int32_t)> &prob_on_t_and_de_f) {
    MagSet cur_set(true);
    cur_set.init_beats_props();
    best_set = cur_set;
    auto cur_time = time_f();
    double t = temp_on_time_f(cur_time);
    while (cur_time < 1980 && best_set.props.energy()) {
        MagSetProps pre_props = cur_set.props;
        Change change = Change::gen_rand(cur_set);
        cur_set.make_change(change);
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
    cin >> n >> m >> k;
    start_t = get_current_time();
    for (int32_t i = 0, a, b; i < m; ++i) {
        cin >> a >> b, --a, --b;
        g[a].push_back(i), g[b].push_back(i);
    }
    auto time_f = []() {
        return chrono::duration_cast<chrono::milliseconds>(get_current_time() - start_t).count();
    };
    auto temp_on_time_f = [](int32_t t) {
        return std::exp(-static_cast<double>(t % 700) / 400);
    };
    auto prob_on_t_and_de_f = [](double t, int32_t de) {
        return std::exp(static_cast<double>(-de) / t);
    };
    Annealing(time_f, temp_on_time_f, prob_on_t_and_de_f);
    if (!best_set.props.energy()) {
        cout << "Yes\n";
        for (auto el: best_set.vs) cout << el + 1 << " ";
        return 0;
    }
    cout << "No\n";
    return 0;
}
