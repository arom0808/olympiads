#include <iostream>
#include <random>
#include <vector>
#include <unordered_set>

using namespace std;

const uint64_t k = 31, mod = 1e9 + 7;
vector<uint64_t> p;

uint64_t hash_substr(uint32_t l, uint32_t r, const vector<uint64_t> &h) {
    return (mod + h[r + 1] - h[l]) % mod * p[10000 - l] % mod;
}

bool
is_greater(uint32_t l1, uint32_t r1, uint32_t l2, uint32_t r2, const vector<uint64_t> &h1, const vector<uint64_t> &h2,
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    p.assign(1e5 + 1, 1);
    for (uint32_t i = 1; i < p.size(); ++i) p[i] = p[i - 1] * k % mod;
    uint32_t n;
    cin >> n;
    vector<string> strs(n);
    for (auto &s: strs) cin >> s;
    vector<vector<uint64_t>> hs(n);
    vector<unordered_set<uint64_t>> subhashes(n);
    for (uint32_t si = 0; si < n; ++si) {
        auto &subh = subhashes[si];
        auto &s = strs[si];
        auto &h = hs[si];
        h.assign(s.size() + 1, 0);
        for (uint32_t i = 0; i < s.size(); ++i) h[i + 1] = (h[i] + p[i] * (s[i] - 'a' + 1)) % mod;
        for (uint32_t i = 0; i < s.size(); ++i)
            for (uint32_t j = i; j < s.size(); ++j)
                subh.insert(hash_substr(i, j, h));
    }
    string str;
    uint64_t ch = 0;
    while (true) {
        bool added = false;
        for (char ta = 'z'; ta >= 'a'; --ta) {
            uint64_t nh = (ch + p[str.size()] * (ta - 'a' + 1)) % mod, tc = nh * p[10000] % mod;
            bool is_ex = true;
            for (auto &subhs: subhashes) {
                if (subhs.contains(tc)) continue;
                is_ex = false;
                break;
            }
            if (!is_ex) continue;
            str += ta, ch = nh, added = true;
            break;
        }
        if (!added) break;
    }
    cout << str;
//    uint32_t best_si = 0, best_l = 0, best_r = 0;
//    for (uint32_t si = 0; si < n; ++si) {
//        auto &s = strs[si];
//        auto &h = hs[si];
//        for (uint32_t i = 0; i < s.size(); ++i)
//            for (uint32_t j = best_r - best_l + i + 1; j < s.size(); ++j)
//                if (cnt_on_hash[hash_substr(i, j, h)] == n &&
//                    is_greater(i, j, best_l, best_r, h, hs[best_si], s, strs[best_si]))
//                    best_si = si, best_l = i, best_r = j;
//    }
//    cout << strs[best_si].substr(best_l, best_r - best_l + 1);
    return 0;
}
