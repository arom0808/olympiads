#include <iostream>
#include <vector>
#include <cstdint>
#include <set>
#include <unordered_map>
#include <random>
#include <unordered_set>

using namespace std;


namespace CleverSol {
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
            if (M == 0) return value + other.value;
            if (value + other.value >= M) return value + other.value - M;
            return value + other.value;
        }

        Hash<M> operator+(uint64_t other) const {
            if (M == 0) return Hash<M>(value + other);
            if (value + other >= M) return Hash<M>(value + other - M);
            return Hash<M>(value + other);
        }

        Hash<M> operator-(Hash<M> other) const {
            if (M == 0) return Hash<M>(value - other.value);
            if (value < other.value) return Hash<M>(value + M - other.value);
            return Hash<M>(value - other.value);
        }

        Hash<M> operator*(Hash<M> other) const {
            if (M == 0) return Hash<M>(value * other.value);
            return Hash<M>(value * other.value % M);
        }

        Hash<M> operator*(uint64_t other) const {
            if (M == 0) return Hash<M>(value * other);
            return Hash<M>(value * other % M);
        }
    };

    template<int64_t P, int64_t M>
    class StringHash {
    public:
        vector<Hash<M>> ps, h;
        uint64_t sz = 0;

        StringHash() = default;

        explicit StringHash(const string &s) {
            assign(s);
        }

        void assign(const string &s) {
            sz = s.size();
            h.resize(sz + 1), ps.resize(sz + 1);
            ps[0] = 1;
            for (uint64_t i = 1; i <= sz; ++i) ps[i] = ps[i - 1] * P;
            h[0] = 0;
            for (uint64_t i = 0; i < sz; ++i) h[i + 1] = h[i] * P + (s[i] - 'a');
        }

        uint64_t substr_hash(uint64_t l, uint64_t r) const {
            return (h[r] - h[l] * ps[r - l]).value;
        }
    };

    struct HashPair {
        uint64_t h1, h2, p1;

        explicit HashPair(uint64_t h1 = 0, uint64_t h2 = 0, uint64_t p1 = 0) : h1(h1), h2(h2), p1(p1) {}

        bool operator<(const HashPair &other) const {
            if (h1 != other.h1) return h1 < other.h1;
            return h2 < other.h2;
        }
    };

    string Sol(const vector<string> &strs) {
        int32_t k = strs.size();
        int32_t min_size = 1e9;
        for (auto &s: strs) min_size = min<int32_t>(min_size, s.size());
        if (k == 1) {
            return strs[0];
        }
        const uint64_t p = 31, m1 = 479001599, m2 = 0;
        vector<StringHash<p, m1>> hashes1(k);
        vector<StringHash<p, m2>> hashes2(k);
        for (int32_t i = 0; i < k; ++i) hashes1[i].assign(strs[i]), hashes2[i].assign(strs[i]);
        int32_t l = 0, r = min_size, start;
        while (l != r) {
            int32_t m = (l + r) / 2 + (l + r) % 2;
            set<HashPair> hash_pairs1;
            for (int32_t i = 0; i + m <= hashes1[0].sz; ++i) {
                hash_pairs1.emplace(hashes1[0].substr_hash(i, i + m), hashes2[0].substr_hash(i, i + m), i);
            }
            for (int32_t s_id = 1; s_id < k; ++s_id) {
                set<HashPair> hash_pairs2;
                for (int32_t i = 0; i + m <= hashes1[s_id].sz; ++i)
                    hash_pairs2.emplace(hashes1[s_id].substr_hash(i, i + m), hashes2[s_id].substr_hash(i, i + m), i);
                set<HashPair> res;
                for (auto hp: hash_pairs1) if (hash_pairs2.find(hp) != hash_pairs2.end()) res.insert(hp);
                hash_pairs1.swap(res);
            }
            if (hash_pairs1.empty()) r = m - 1;
            else l = m, start = hash_pairs1.begin()->p1;
        }
        if (l != 0) return strs[0].substr(start, l);
        return "";
    }
}

namespace StupidSol {
    const uint64_t k = 31, mod = 1e9 + 7;
    vector<uint64_t> p;

    uint64_t hash_substr(uint32_t l, uint32_t r, const vector<uint64_t> &h) {
        return (mod + h[r + 1] - h[l]) % mod * p[10000 - l] % mod;
    }

    bool
    is_greater(uint32_t l1, uint32_t r1, uint32_t l2, uint32_t r2, const vector<uint64_t> &h1,
               const vector<uint64_t> &h2,
               const string &s1, const string &s2) {
        uint32_t l = 0, r = min(r1 - l1, r2 - l2) + 1;
        while (l != r) {
            uint32_t m = (l + r) / 2 + (l + r) % 2;
            if (hash_substr(l1, l1 + m - 1, h1) == hash_substr(l2, l2 + m - 1, h2)) l = m;
            else r = m - 1;
        }
        if (l <= min(r1 - l1, r2 - l2)) return s1[l1 + l] > s2[l2 + l];
        return r1 - l1 > r2 - l2;
    }

    string Sol(const vector<string> &strs) {
        p.assign(1e5 + 1, 1);
        for (uint32_t i = 1; i < p.size(); ++i) p[i] = p[i - 1] * k % mod;
        unordered_map<uint64_t, uint32_t> cnt_on_hash;
        uint32_t n = strs.size();
        vector<vector<uint64_t>> hs(n);
        unordered_set<uint64_t> now_hashes;
        for (uint32_t si = 0; si < n; ++si) {
            now_hashes.clear();
            auto &s = strs[si];
            auto &h = hs[si];
            h.assign(s.size() + 1, 0);
            for (uint32_t i = 0; i < s.size(); ++i) h[i + 1] = (h[i] + p[i] * (s[i] - 'a' + 1)) % mod;
            for (uint32_t i = 0; i < s.size(); ++i)
                for (uint32_t j = i + 1; j < s.size(); ++j)
                    now_hashes.insert(hash_substr(i, j, h));
            for (auto hash: now_hashes) {
                auto it = cnt_on_hash.find(hash);
                if (it == cnt_on_hash.end()) cnt_on_hash.emplace(hash, 1);
                else ++it->second;
            }
        }
        uint32_t best_si = 0, best_l = 0, best_r = 0;
        bool made = false;
        for (uint32_t si = 0; si < n; ++si) {
            auto &s = strs[si];
            auto &h = hs[si];
            for (uint32_t i = 0; i < s.size(); ++i)
                for (uint32_t j = best_r - best_l + i + 1; j < s.size(); ++j)
                    if (cnt_on_hash[hash_substr(i, j, h)] == n &&
                        is_greater(i, j, best_l, best_r, h, hs[best_si], s, strs[best_si]))
                        best_si = si, best_l = i, best_r = j, made = true;
        }
        bool ok = true;
        auto res = strs[best_si].substr(best_l, best_r - best_l + 1);
        for (const auto &s: strs)
            if (s.find(res) == string::npos) ok = false;
        if (ok)
            return strs[best_si].substr(best_l, best_r - best_l + 1);
        return "";
    }
}

namespace Test {
    random_device dev;
    uint32_t seed = dev();
    mt19937 rng(seed);

    template<typename T>
    T randint(T a, T b) {
        return uniform_int_distribution(a, b)(rng);
    }

    vector<string> gen() {
        int32_t k = randint(1, 3);
        vector<string> res(k);
        for (auto &s: res) {
            int32_t n = randint(1, 5);
            s.resize(n);
            for (auto &c: s) c = randint('a', 'z');
        }
        return res;
    }

    void Test() {
        while (true) {
            auto inp = gen();
            auto r1 = CleverSol::Sol(inp);
            auto r2 = StupidSol::Sol(inp);
            if (r1 != r2) {
                cout << inp.size() << "\n";
                for (const auto &s: inp) cout << s << "\n";
                cout << "\nclever:\n" << r1 << "\nstupid:\n" << r2 << "\n";
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t k;
    cin >> k;
    vector<string> strs(k);
    for (auto &s: strs) cin >> s;
    cout << CleverSol::Sol(strs) << "\n";
//    Test::Test();
    return 0;
}