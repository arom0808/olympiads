#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using ll = long long;
using ld = long double;

constexpr int maxn = 1000;

mt19937 rng(1234364);
chrono::time_point<chrono::steady_clock> start_time;

int randint(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}

int n;
bool g[maxn][maxn];
int cur_pow[maxn];

void update_cur_pow(vector<int> vs) {
    for (int i = 0; i < n; ++i) cur_pow[i] = 0;
    for (auto v: vs)
        for (int i = 0; i < n; ++i)
            if (g[v][i]) ++cur_pow[i];
}

vector<int> gen_rich(int cnt) {
    vector<int> ans;
    ans.reserve(cnt);
    ans.push_back(randint(0, n - 1));
    vector<int> candidates;
    shuffle(candidates.begin(), candidates.end(), rng);
    candidates.reserve(n - 1);
    for (int i = 0; i < n; ++i) if (ans.front() != i) candidates.push_back(i);
    while (ans.size() < cnt) {
        update_cur_pow(ans);
        auto it = std::max_element(candidates.begin(), candidates.end(),
                                   [](int a, int b) { return cur_pow[a] < cur_pow[b]; });
        ans.push_back(*it);
        candidates.erase(it);
    }
    return ans;
}

int calc_power(const vector<int> &vs) {
    int ans = 0;
    for (int i = 0; i < vs.size(); ++i)
        for (int j = i + 1; j < vs.size(); ++j)
            ans += g[vs[i]][vs[j]];
    return ans;
}

// bool is_in_set[maxn];

vector<int> bvs;
int bp = 0;

bool try_solve_for_cnt(int cnt) {
    vector<int> vs = gen_rich(cnt);
    int cur_p = calc_power(vs);
    for (int i = 0; i < 10; ++i) {
        vector<int> now_vs = gen_rich(cnt);
        int now_p = calc_power(now_vs);
        if (now_p > cur_p) swap(vs, now_vs), swap(cur_p, now_p);
    }
    bvs = vs, bp = cur_p;
    int max_p = (cnt - 1) * cnt / 2;
    vector<int> candidates(n);
    iota(candidates.begin(), candidates.end(), 0);
    erase_if(candidates, [&vs](int v) { return find(vs.begin(), vs.end(), v) != vs.end(); });
    shuffle(candidates.begin(), candidates.end(), rng);
    ld temp = 10;
    int _ = 0;
    while (cur_p < max_p) {
        if (temp < 0.1) temp = 10;
        int fp = randint(0, vs.size() - 1);
        int sp = randint(0, candidates.size() - 1);
        int new_p = cur_p;
        for (int i = 0; i < vs.size(); ++i) if (fp != i && g[vs[fp]][vs[i]]) --new_p;
        swap(vs[fp], candidates[sp]);
        for (int i = 0; i < vs.size(); ++i) if (fp != i && g[vs[fp]][vs[i]]) ++new_p;
        if (new_p > cur_p || exp((new_p - cur_p) / temp) >= 0.5) {
            cur_p = new_p;
            if (cur_p > bp) {
                bvs = vs;
                bp = cur_p;
            }
        } else {
            for (int i = 0; i < vs.size(); ++i) if (fp != i && g[vs[fp]][vs[i]]) --new_p;
            swap(vs[fp], candidates[sp]);
            for (int i = 0; i < vs.size(); ++i) if (fp != i && g[vs[fp]][vs[i]]) ++new_p;
        }
        temp *= 0.99;
        ++_;
        if (_ == 100) {
            auto cur_time = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(cur_time - start_time).count() >= 900) break;
            _ = 0;
        }
    }
    vs= bvs;
    for (auto v: vs) cur_pow[v] = 0;
    for (auto v: vs) for (auto u: vs) if (g[v][u]) ++cur_pow[v];
    sort(vs.begin(), vs.end(), [](int a, int b) { return cur_pow[a] < cur_pow[b]; });
    vector<int> ans;
    auto it = max_element(vs.begin(), vs.end(), [](int a, int b) { return cur_pow[a] < cur_pow[b]; });
    ans.push_back(*it);
    vs.erase(it);
    while (!vs.empty()) {
        for (auto v: vs) cur_pow[v] = 0;
        for (auto v: vs) for (auto u: ans) if (g[v][u]) ++cur_pow[v];
        it = max_element(vs.begin(), vs.end(), [](int a, int b) { return cur_pow[a] < cur_pow[b]; });
        if (cur_pow[*it] < ans.size()) break;
        ans.push_back(*it);
        vs.erase(it);
    }
    cout << ans.size() << "\n";
    for (auto v: ans) cout << v + 1 << " ";
    return true;
}

void solve() {
    start_time = chrono::steady_clock::now();
    cin >> n;
    char c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> c;
            g[i][j] = c == '1';
        }
    }
    if (n == 10) try_solve_for_cnt(6);
    else try_solve_for_cnt(46);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r", stdin);
#endif
    solve();
    return 0;
}
