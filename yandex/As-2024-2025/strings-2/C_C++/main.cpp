#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

constexpr uint32_t mod1 = 1e9 + 7, mod2 = 0;

template<uint32_t M>
struct HV {
    uint32_t val = 0;

    HV() = default;

    constexpr HV(uint32_t v) : val(v) {
    }

    HV operator+(const HV &rhs) const {
        if (val + rhs.val >= M) return val + rhs.val - M;
        return val + rhs.val;
    }

    HV operator-(const HV &rhs) const {
        if (val < rhs.val) return val + M - rhs.val;
        return val - rhs.val;
    }

    HV operator*(const HV &rhs) const {
        if (M) return 1ull * val * rhs.val % M;
        return val * rhs.val;
    }

    bool operator==(const HV<M> &rhs) const {
        return val == rhs.val;
    }

    bool operator!=(const HV<M> &rhs) const {
        return val != rhs.val;
    }

    bool operator<(const HV<M> &rhs) const {
        return val < rhs.val;
    }
};

struct pHV {
    HV<mod1> v1;
    HV<mod2> v2;

    pHV() = default;

    pHV(const HV<mod1> &v1, const HV<mod2> &v2): v1(v1), v2(v2) {
    }

    constexpr pHV(uint32_t v): v1(v), v2(v) {
    }

    pHV operator+(const pHV &rhs) const {
        return {v1 + rhs.v1, v2 + rhs.v2};
    }

    pHV operator-(const pHV &rhs) const {
        return {v1 - rhs.v1, v2 - rhs.v2};
    }

    pHV operator*(const pHV &rhs) const {
        return {v1 * rhs.v1, v2 * rhs.v2};
    }

    bool operator<(const pHV &rhs) const {
        if (v1 != rhs.v1) return v1 < rhs.v1;
        return v2 < rhs.v2;
    }
};

constexpr int maxn = 10, maxlen = 10002;
constexpr pHV p = 31;
pHV ps[maxlen];
string sts[maxn];
pHV hashes[maxn][maxlen];

pHV hash_substr(const pHV cur_hashes[maxlen], int l, int r) {
    return (cur_hashes[r] - cur_hashes[l]) * ps[maxlen - r];
}

struct MySubstr {
    pHV hv;
    int sid, start_pos;

    bool operator<(const MySubstr &rhs) const {
        return hv < rhs.hv;
    }
};

int n;

pair<int, int> check_len(int len) {
    set<MySubstr> g_subs;
    for (int i = 0; i < n; ++i) {
        set<MySubstr> cur_subs;
        for (int j = 0; j + len <= sts[i].size(); ++j) {
            cur_subs.insert(MySubstr(hash_substr(hashes[i], j, j + len), i, j));
        }
        if (i == 0) g_subs = cur_subs;
        else {
            set<MySubstr> temp;
            set_intersection(g_subs.begin(), g_subs.end(), cur_subs.begin(), cur_subs.end(),
                             inserter(temp, temp.begin()));
            swap(temp, g_subs);
        }
    }
    if (g_subs.empty()) return {-1, -1};
    auto [hv, sid, start_pos] = *g_subs.begin();
    return {sid, start_pos};
}

void solve() {
    ps[0] = 1;
    for (int i = 1; i < maxlen; ++i) ps[i] = ps[i - 1] * p;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> sts[i];
    for (int i = 0; i < n; ++i) {
        hashes[i][0] = 0;
        for (int j = 0; j < sts[i].size(); ++j) hashes[i][j + 1] = hashes[i][j] + ps[j] * (sts[i][j] - 'a');
    }
    int l = 0, r = 10001;
    while (r - l != 1) {
        int m = (l + r) / 2;
        auto [sid, start_pos] = check_len(m);
        if (sid != -1) l = m;
        else r = m;
    }
    auto [sid, start_pos] = check_len(l);
    cout << sts[sid].substr(start_pos, l) << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
