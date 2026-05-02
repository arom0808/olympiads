#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

template<uint64_t M>
class Hash {
public:
    uint64_t value;

    explicit Hash(uint64_t value = 0) : value(value) {}

    Hash<M> &operator=(uint64_t v) {
        value = v;
        return *this;
    }

    Hash<M> operator+(Hash<M> other) const {
        if (value + other.value >= M) return Hash<M>(value + other.value - M);
        return Hash<M>(value + other.value);
    }

    Hash<M> operator+(uint64_t other) const {
        if (value + other >= M) return Hash<M>(value + other - M);
        return Hash<M>(value + other);
    }

    Hash<M> operator-(Hash<M> other) const {
        if (value < other.value) return Hash<M>(value + M - other.value);
        return Hash<M>(value - other.value);
    }

    Hash<M> operator-(uint64_t other) const {
        if (value < other) return Hash<M>(value + M - other);
        return Hash<M>(value - other);
    }

    Hash<M> operator*(Hash<M> other) const {
        if (M == 0) return Hash<M>(value * other.value);
        return Hash<M>(value * other.value % M);
    }

    Hash<M> operator*(uint64_t other) const {
        if (M == 0) return Hash<M>(value * other);
        return Hash<M>(value * other % M);
    }

    bool operator==(Hash<M> other) const {
        return value == other.value;
    }
};

template<uint64_t P, uint64_t M>
class StringHash {
public:
    vector<Hash<M>> ps, h;
    int32_t sz;

    explicit StringHash(const string &s) : sz(s.size()), h(s.size() + 1), ps(s.size() + 1) {
        ps[0] = 1;
        for (int32_t i = 1; i <= sz; ++i) ps[i] = ps[i - 1] * P;
        h[0] = 0;
        for (int32_t i = 0; i < sz; ++i) h[i + 1] = h[i] * P + (s[i] - 'a');
    }

    Hash<M> substr_hash(int32_t l, int32_t r) const {
        return h[r] - h[l] * ps[r - l];
    }
};

template<uint64_t P, uint64_t M1, uint64_t M2>
class PairStringHash {
public:
    StringHash<P, M1> sh1;
    StringHash<P, M2> sh2;

    explicit PairStringHash(const string &s) : sh1(s), sh2(s) {}

    pair<Hash<M1>, Hash<M2>> substr_hash(int32_t l, int32_t r) const {
        return {sh1.substr_hash(l, r), sh2.substr_hash(l, r)};
    }
};

template<uint64_t P, uint64_t M1, uint64_t M2>
int32_t
max_eq(int32_t s1, int32_t s2, int32_t n, const PairStringHash<P, M1, M2> &ph1, const PairStringHash<P, M1, M2> &ph2) {
    int32_t l = 0, r = min(n - s1 - 1, n - s2 - 1);
    while (l != r) {
        int32_t m = (l + r) / 2 + ((l + r) % 2);
        if (ph1.substr_hash(s1, s1 + m) == ph2.substr_hash(s2, s2 + m)) l = m;
        else r = m - 1;
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string s, rs;
    cin >> s;
    rs = s;
    std::reverse(rs.begin(), rs.end());
    int32_t n = s.size();
    const uint64_t m1 = 999999937, m2 = 0;
    PairStringHash<31, m1, m2> ph(s), rph(rs);
    vector<int32_t> forward_max(n, 0), backward_max(n, 0);
    for (int32_t i = 1; i + 1 < n; ++i) {
        forward_max[i] = max_eq(i, 0, n, ph, ph);
        backward_max[i] = max_eq(n - 1 - i, 0, n, rph, rph);
    }
    vector<int32_t> max_b_pos(n, -1);
    for (int32_t i = 0; i < n; ++i) {
        if (backward_max[i] != 0 && i > max_b_pos[i + 1 - backward_max[i]]) max_b_pos[i + 1 - backward_max[i]] = i;
    }
    int32_t ri = 0;
    int32_t bsize = 0, bpos = 0;
    for (int32_t i = 0; i < n; ++i) {
        if (max_b_pos[i] > ri) ri = max_b_pos[i];
        if (i != 0 && i + 1 < n && ri >= i) {
            int32_t cr = min(ri - i + 1, forward_max[i]);
            if (cr >= bsize) bsize = cr, bpos = i;
        }
    }
    if (bsize) cout << s.substr(bpos, bsize) << "\n";
    else cout << "Just a legend\n";
    return 0;
}