#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_set>

using namespace std;

//template<uint64_t M>
//class Hash {
//public:
//    uint64_t value;
//
//    explicit Hash(uint64_t value = 0) : value(value) {}
//
//    Hash<M> &operator=(uint64_t v) {
//        value = v;
//        return *this;
//    }
//
//    Hash<M> operator+(Hash<M> other) const {
//        if (M == 0) return value + other.value;
//        if (value + other.value >= M) return value + other.value - M;
//        return value + other.value;
//    }
//
//    Hash<M> operator+(uint64_t other) const {
//        if (M == 0) return Hash<M>(value + other);
//        if (value + other >= M) return Hash<M>(value + other - M);
//        return Hash<M>(value + other);
//    }
//
//    Hash<M> operator-(Hash<M> other) const {
//        if (M == 0) return Hash<M>(value - other.value);
//        if (value < other.value) return Hash<M>(value + M - other.value);
//        return Hash<M>(value - other.value);
//    }
//
//    Hash<M> operator*(Hash<M> other) const {
//        if (M == 0) return Hash<M>(value * other.value);
//        return Hash<M>(value * other.value % M);
//    }
//
//    Hash<M> operator*(uint64_t other) const {
//        if (M == 0) return Hash<M>(value * other);
//        return Hash<M>(value * other % M);
//    }
//};

class StringHash {
public:
    vector<uint64_t> ps, h;
    uint64_t P = 0, sz = 0;

    StringHash() = default;

    explicit StringHash(const string &s, uint64_t _P) {
        assign(s, _P);
    }

    void assign(const string &s, uint64_t _P) {
        P = _P;
        sz = s.size();
        h.resize(sz + 1), ps.resize(sz + 1);
        ps[0] = 1;
        for (uint64_t i = 1; i <= sz; ++i) ps[i] = ps[i - 1] * P;
        h[0] = 0;
        for (uint64_t i = 0; i < sz; ++i) h[i + 1] = h[i] * P + (s[i] - 'a');
    }

    void assign(uint64_t size, uint64_t _P) {
        P = _P;
        sz = size;
        h.resize(sz + 1), ps.resize(sz + 1);
        ps[0] = 1;
        for (uint64_t i = 1; i <= sz; ++i) ps[i] = ps[i - 1] * P;
        h[0] = 0;
    }

    void update_symbol(uint64_t pos, uint64_t val) {
        h[pos + 1] = h[pos] * P + val;
    }

    uint64_t substr_hash(uint64_t l, uint64_t r) const {
        return h[r] - h[l] * ps[r - l];
    }
};

//struct custom_hash {
//    static uint64_t splitmix64(uint64_t x) {
//        // http://xorshift.di.unimi.it/splitmix64.c
//        x += 0x9e3779b97f4a7c15;
//        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//        return x ^ (x >> 31);
//    }
//
//    size_t operator()(const pair<uint64_t, uint64_t> &x) const {
//        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//        return splitmix64(x.first ^ FIXED_RANDOM + x.second);
//    }
//};

const uint64_t m1 = 1e9 + 7, m2 = 0;
int32_t n, k;
unordered_set<uint64_t> hashes;
int32_t res_size;
//StringHash<p, m1> gh1;
StringHash gh2;
vector<uint64_t> res;


bool rec_sol(int32_t level = 0) {
    if (level == res_size) {
        return hashes.find(gh2.h.back()) == hashes.end();
    }
    if (level == 0) {
//        gh1.assign(res_size),
        gh2.assign(res_size, k), res.resize(res_size);
    }
    for (res[level] = 0; res[level] < k; ++res[level]) {
//        gh1.update_symbol(level, res[level]);
        gh2.update_symbol(level, res[level]);
        if (rec_sol(level + 1)) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    freopen("g.in", "r", stdin), freopen("g.out", "w", stdout);
    cin >> n >> k;
    string str;
    cin >> str;
    if (k == 1) {
        str += str.back();
        cout << str << "\n";
        return 0;
    }
    uint64_t eee = 1, cc = k;
    while (cc <= str.size()) ++eee, cc *= k;
    eee = min<uint64_t>(str.size() + 1, eee);
    vector<uint64_t> k_p(eee + 1);
    k_p[0] = 1;
    for (int32_t i = 1; i < k_p.size(); ++i) k_p[i] = k_p[i - 1] * k;
//    StringHash<p, m1> sh1(str);
    StringHash sh2(str, k);
//    for (res_size = 1; res_size <= 100; ++res_size) {
//        hashes.clear();
//        for (int32_t i = 0; i + res_size <= str.size(); ++i)
//            hashes.emplace(sh1.substr_hash(i, i + res_size), sh2.substr_hash(i, i + res_size));
//        if (rec_sol()) break;
//    }
    int32_t l = 1, r = eee;
    while (l != r) {
        int32_t m = (l + r) / 2;
        hashes.clear();
        for (int32_t i = 0; i + m <= str.size(); ++i)
            hashes.emplace(sh2.substr_hash(i, i + m));
        if (hashes.size() >= k_p[m]) l = m + 1;
        else r = m;
    }
    hashes.clear();
    for (int32_t i = 0; i + l <= str.size(); ++i)
        hashes.emplace(sh2.substr_hash(i, i + l));
    res_size = l;
    rec_sol();
    string res_str(res_size, '0');
    for (int32_t i = 0; i < res_size; ++i) res_str[i] = 'a' + static_cast<char>(res[i]);
    cout << res_str << "\n";
    return 0;
}
