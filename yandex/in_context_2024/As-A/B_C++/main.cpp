#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
#include <random>
#include <map>
#include <deque>

using namespace std;

const int32_t maxn = 2e5 + 1;
const uint64_t mod1 = 1000000000000000009ull, mod2 = 0, mod3 = 1000000000000002449ull, mod4 = 2315478218572185ull;
const uint32_t d = 201491;
int32_t n, m, k;
vector<uint32_t> t, a, b;

mt19937 rng(2364723);

template<typename T>
inline T randint(T n1, T n2) {
    return uniform_int_distribution(n1, n2)(rng);
}

template<uint64_t mod>
struct HV {
public:
    uint64_t val;

    explicit HV(uint64_t val = 0) : val(val) {}

    HV<mod> operator+(HV<mod> other) const {
        auto res = val + other.val;
        return HV<mod>(res >= mod ? res - mod : res);
    }

    HV<mod> operator+(uint64_t other) const {
        auto res = val + other;
        return HV<mod>(res >= mod ? res - mod : res);
    }

    HV<mod> operator-(HV<mod> other) const {
        if (val < other.val) return HV<mod>(val + mod - other.val);
        return HV<mod>(val - other.val);
    }

    HV<mod> operator-(uint64_t other) const {
        if (val < other) return HV<mod>(val + mod - other);
        return HV<mod>(val - other);
    }

    HV<mod> operator*(HV<mod> other) const {
        if (mod == 0) return HV<mod>(val * other.val);
        return HV<mod>((static_cast<__int128_t>(val) * other.val) % mod);
    }

    HV<mod> operator*(uint64_t other) const {
        if (mod == 0) return HV<mod>(val * other);
        return HV<mod>((static_cast<__int128_t>(val) * other) % mod);
    }

    void operator*=(uint64_t other) {
        if (mod == 0) val *= other;
        else val = (static_cast<__int128_t>(val) * other) % mod;
    }

    bool operator<(HV<mod> hash) const {
        return val < hash.val;
    }
};

template<uint64_t mod>
class ArrHash {
public:
    vector<HV<mod>> dms, hvs;

    ArrHash() = default;

    template<typename T>
    explicit ArrHash(const vector<T> &arr) : hvs(arr.size() + 1), dms(maxn + 1) {
        init(arr);
    }

    template<typename T>
    void assign(const vector<T> &arr) {
        hvs.clear(), dms.clear();
        hvs.resize(arr.size() + 1), dms.resize(maxn + 1);
        init(arr);
    }

    template<typename T>
    void init(const vector<T> &arr) {
        dms.front().val = 1, hvs.front().val = 0;
        for (int32_t i = 1; i <= maxn; ++i) dms[i] = dms[i - 1] * d;
        for (int32_t i = 0; i < arr.size(); ++i) hvs[i + 1] = hvs[i] + dms[i] * arr[i];
    }

    uint64_t hash_substr(int32_t l, int32_t r) const {
        return ((hvs[r] - hvs[l]) * dms[maxn - r]).val;
    }
};

using CAHT = tuple<uint64_t, uint64_t, uint64_t, uint64_t>;

class CompArrHash {
public:
    ArrHash<mod1> h1;
    ArrHash<mod2> h2;
    ArrHash<mod3> h3;
    ArrHash<mod4> h4;

    CompArrHash() = default;

    template<typename T>
    explicit CompArrHash(const vector<T> &arr) : h1(arr), h2(arr), h3(arr), h4(arr) {}

    template<typename T>
    void assign(const vector<T> &arr) {
        h1.assign(arr), h2.assign(arr), h3.assign(arr), h4.assign(arr);
    }

    CAHT hash_substr(int32_t l, int32_t r) const {
        return {h1.hash_substr(l, r), h2.hash_substr(l, r), h3.hash_substr(l, r), h4.hash_substr(l, r)};
    }
};

CompArrHash th, ah, bh;

bool have_intersect(int32_t len) {
    map<CAHT, int32_t> fhs;
    for (int32_t i = 0; i + len - 1 < m; ++i) fhs.emplace(ah.hash_substr(i, i + len), i);
    for (int32_t i = 0; i + len - 1 < k; ++i) {
        auto it = fhs.find(bh.hash_substr(i, i + len));
        if (it == fhs.end()) continue;
        bool ok = true;
        for (int32_t j = 0; j < 10 && ok; ++j) {
            int32_t pos = randint(0, len - 1);
            if (a[it->second + pos] != b[i + pos]) ok = false;
        }
        if (ok) return true;
    }
    return false;
}

int32_t sol1() {
    int32_t l = 0, r = std::min(a.size(), b.size());
    while (l != r) {
        int32_t mid = (l + r) / 2 + (l + r) % 2;
        if (have_intersect(mid)) l = mid;
        else r = mid - 1;
    }
    if (l == 0) return -1;
    return m + k - 2 * l;
}

set<uint32_t> g[maxn];
bool bps[maxn];
bool used[maxn];

int32_t sol2() {
    for (int32_t i = 0; i + 1 < n; ++i) {
        g[t[i]].insert(t[i + 1]);
        g[t[i + 1]].insert(t[i]);
    }
    deque<pair<uint32_t, uint32_t>> deq;
    for (auto val: a) deq.emplace_back(val, 0);
    for (auto val: b) bps[val] = true;
    while (true) {
        auto [v, depth] = deq.front();
        deq.pop_front();
        if (used[v]) continue;
        used[v] = true;
        if (bps[v]) return m - 1 + 2 * depth + k - 1;
        for (auto u: g[v]) deq.emplace_back(u, depth + 1);
    }
}

int main() {
//    vector<uint32_t> aa{0, 1, 2};
//    vector<uint32_t> bb{2};
//    ArrHash<mod1> ahh(aa), bhh(bb);
//    cout << ahh.hash_substr(2, 3) << " " << bhh.hash_substr(0, 1);
    set<HV<mod1>> ass;
    ass.emplace(213123);

    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    t.resize(n);
    for (auto &val: t) cin >> val;
    cin >> m;
    a.resize(m);
    for (auto &val: a) cin >> val;
    cin >> k;
    b.resize(k);
    for (auto &val: b) cin >> val;
    th.assign(t), ah.assign(a), bh.assign(b);
    int32_t r1 = sol1();
    if (r1 != -1) cout << r1 << "\n";
    else cout << sol2() << "\n";
    return 0;
}
