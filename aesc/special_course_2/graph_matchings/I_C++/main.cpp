#include <iostream>
#include <vector>
#include <list>
#include <bitset>

using namespace std;

const int32_t inf = 2e9;

struct RM {
    int32_t time = -1, v = -1, d = -1;
};

int32_t gcd(int32_t a, int32_t b) {
    int32_t t;
    while (b) {
        t = a;
        a = b;
        b = t % b;
    }
    return a;
}

bool dfs(const vector<list<pair<int32_t, int32_t>>> &g, vector<RM> &rm, vector<int32_t> &used,
         int32_t timer, int32_t rm_timer, int32_t v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto [u, d]: g[v]) {
        if (rm[u].time != rm_timer) {
            rm[u] = {rm_timer, v, d};
            return true;
        }
    }
    for (auto [u, d]: g[v]) {
        if (dfs(g, rm, used, timer, rm_timer, rm[u].v)) {
            rm[u] = {rm_timer, v, d};
            return true;
        }
    }
    return false;
}

int32_t min_common_prime(const vector<int32_t> &dre, const vector<int32_t> &primes, int32_t num) {
    if (num < dre.size()) return dre[num];
    for (const auto prime: primes) {
        if (prime * prime > num) break;
        if (num % prime == 0) return prime;
    }
    return inf;
}

pair<int32_t, int32_t> max_common_div_pow(int32_t div, int32_t a, int32_t b) {
    int32_t res = 1, nd = div;
    while (a % (nd * div) == 0 && b % (nd * div) == 0) {
        ++res;
        nd *= div;
    }
    return {res, nd};
}

int main() {
    int16_t a = -274;
    bitset<16> bb(a);
    cout << bb.to_string();

    int32_t mmmaxxx = 1e5;
    vector<int32_t> primes;
    primes.reserve(mmmaxxx + 1);
    vector<int32_t> dre(mmmaxxx + 1, inf);
    for (int32_t i = 2; i <= mmmaxxx; ++i) {
        if (dre[i] == inf) {
            dre[i] = i;
            primes.push_back(i);
        }
        for (auto p: primes) {
            if (p > dre[i] || p * i > mmmaxxx) break;
            dre[i * p] = p;
        }
    }
    int32_t n, m;
    cin >> n >> m;
    vector<int32_t> nums(n);
    for (auto &num: nums) cin >> num;
    vector<list<pair<int32_t, int32_t>>> g(n);
    for (int32_t _ = 0, a, b; _ < m; ++_) {
        cin >> a >> b;
        --a;
        --b;
        if (a % 2 != 0) swap(a, b);
        auto mcp = min_common_prime(dre, primes, gcd(nums[a], nums[b]));
        if (mcp != inf) g[a].emplace_back(b, mcp);
    }
    vector<int32_t> used(n, -1);
    vector<RM> rm(n);
    int32_t ans = 0, timer = 0, rm_timer = 0;
    while (true) {
        int32_t there_ans = 0;
        for (int32_t v = 0; v < n; ++v) {
            if (dfs(g, rm, used, timer, rm_timer, v)) {
                ++there_ans;
                ++timer;
            }
        }
        ++timer;
        ++rm_timer;
        if (there_ans == 0) break;
        for (int32_t u = 0; u < n; ++u) {
            if (rm[u].v >= 0) {
                auto mcdp = max_common_div_pow(rm[u].d, nums[u], nums[rm[u].v]);
                nums[u] /= mcdp.second;
                nums[rm[u].v] /= mcdp.second;
                ans += mcdp.first;
            }
        }
        for (int32_t i = 0; i < n; ++i) {
            for (auto it = g[i].begin(); it != g[i].end();) {
                auto mcp = min_common_prime(dre, primes, gcd(nums[i], nums[it->first]));
                if (mcp == inf) it = g[i].erase(it);
                else it->second = mcp;
            }
        }
    }
    cout << ans;
    return 0;
}
