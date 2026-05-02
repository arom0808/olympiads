#include <iostream>
#include <random>
#include <vector>
#include <map>
#include <cstdint>

using namespace std;

template<uint64_t M>
class Hash {
public:
    uint64_t value;

    inline Hash operator+(Hash<M> other) const {
        return (*this) + other.value;
    }

    inline Hash &operator+=(Hash other) {
        return (*this) += other.value;
    }

    Hash &operator+=(uint64_t o_val) {
        value += o_val;
        if (value >= M) value -= M;
        return *this;
    }

    Hash operator+(uint64_t o_val) const {
//        if (M == 0) return Hash<M>(value + o_val);
        if (value + o_val >= M) return Hash<M>(value + o_val - M);
        return Hash<M>(value + o_val);
    }

    inline Hash operator-(Hash<M> other) const {
        return (*this) - other.value;
    }

    Hash operator-(uint64_t o_val) const {
//        if (M == 0) return Hash<M>(value - o_val);
        if (value < o_val) return Hash<M>(value + M - o_val);
        return Hash<M>(value - o_val);
    }

    inline Hash operator*(Hash<M> other) const {
        return (*this) * other.value;
    }

    Hash operator*(uint64_t o_val) const {
        if (M == 0) return Hash<M>(value * o_val);
        return Hash<M>(value * o_val % M);
    }

    bool operator<(Hash<M> other) const {
        return value < other.value;
    }
};

template<uint64_t M>
class Hasher {
public:
    random_device dev;
    mt19937_64 rng;
    uniform_int_distribution<uint64_t> dist;
    map<Hash<M>, Hash<M>> hm;

    Hasher() : rng(dev()), dist(0, M - 1) {}

    Hash<M> operator()(Hash<M> val) {
        auto it = hm.find(val);
        if (it != hm.end()) return it->second;
        return hm.emplace(val, Hash<M>(dist(rng))).first->second;
    }
};

template<uint64_t M>
Hash<M> tree_hash(const vector<vector<int32_t>> &g, Hasher<M> &hasher, int32_t v, int32_t p = -1) {
    if (g[v].empty()) return Hash<M>(0);
    Hash<M> res(0);
    for (auto u: g[v]) if (u != p) res += hasher(tree_hash(g, hasher, u, v));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, r1, r2;
    cin >> n;
    cin >> r1 >> r2, --r1, --r2;
    vector<vector<int32_t>> g1(n), g2(n);
    for (int32_t i = 1, a, b; i < n; ++i) {
        cin >> a >> b, --a, --b;
        g1[a].push_back(b), g1[b].push_back(a);
    }
    for (int32_t i = 1, a, b; i < n; ++i) {
        cin >> a >> b, --a, --b;
        g2[a].push_back(b), g2[b].push_back(a);
    }
    const uint64_t m1 = 1e9 + 7, m2 = 0;
    Hasher<m1> hasher1;
    Hasher<m2> hasher2;
    uint64_t h11 = tree_hash(g1, hasher1, r1).value, h12 = tree_hash(g1, hasher2, r1).value;
    uint64_t h21 = tree_hash(g2, hasher1, r2).value, h22 = tree_hash(g2, hasher2, r2).value;
    if (h11 == h21 && h12 == h22) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
