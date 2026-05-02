#include <iostream>
#include <array>
#include <vector>

using namespace std;

template<typename T, typename MultT, T... P>
struct HV {
    constexpr static int mods_cnt = sizeof...(P);
    constexpr static array<T, mods_cnt> mods = {P...};
    array<T, mods_cnt> vals;

    HV(T val = 0) { vals.fill(val); }

    HV &operator+=(const HV &rhs) {
        for (int i = 0; i < mods_cnt; ++i) {
            vals[i] += rhs.vals[i];
            if (vals[i] >= mods[i]) vals[i] -= mods[i];
        }
        return *this;
    }

    HV operator+(const HV &rhs) const {
        HV res = *this;
        return res += rhs;
    }

    HV &operator-=(const HV &rhs) {
        for (int i = 0; i < mods_cnt; ++i) {
            if (vals[i] < rhs.vals[i]) vals[i] = vals[i] + mods[i] - rhs.vals[i];
            else vals[i] -= rhs.vals[i];
        }
        return *this;
    }

    HV operator-(const HV &rhs) const {
        HV res = *this;
        return res -= rhs;
    }

    HV &operator*=(const HV &rhs) {
        for (int i = 0; i < mods_cnt; ++i) {
            if (mods[i]) vals[i] = static_cast<MultT>(vals[i]) * rhs.vals[i] % mods[i];
            else vals[i] *= rhs.vals[i];
        }
        return *this;
    }

    HV operator*(const HV &rhs) const {
        HV res = *this;
        return res *= rhs;
    }

    bool operator==(const HV &rhs) const {
        for (int i = 0; i < mods_cnt; ++i) if (vals[i] != rhs.vals[i]) return false;
        return true;
    }
};

constexpr int mod1 = 1e9 + 7, mod2 = 0;
using MH = HV<int, int64_t, mod1, mod2>;

constexpr int maxn = 1e5, p = 31;
MH ps[maxn + 1];

void calc_p() {
    ps[0] = 1;
    for (int i = 1; i <= maxn; ++i) ps[i] = ps[i - 1] * p;
}

struct StrHash {
    vector<MH> hashes;

    void assign(const string &str) {
        hashes.resize(str.size() + 1);
        hashes[0] = 0;
        for (int i = 1; i < hashes.size(); ++i) hashes[i] = hashes[i - 1] + MH(str[i - 1]) * ps[i];
    }

    StrHash() = default;

    explicit StrHash(const string &str) { assign(str); }

    MH substr_hash(int from, int to) const {
        return (hashes[to] - hashes[from]) * ps[maxn - to];
    }
};

void solve() {
    calc_p();
    string a, b;
    cin >> a >> b;
    for (auto &el: a) el -= 'a';
    for (auto &el: b) el -= 'a';
    StrHash ah(a), bh(b);
    for (int i = 0; i + b.size() <= a.size(); ++i)
        if (ah.substr_hash(i, i + b.size()) == bh.substr_hash(0, b.size()))
            cout << i << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--) solve();
#else
    solve();
#endif
    return 0;
}
