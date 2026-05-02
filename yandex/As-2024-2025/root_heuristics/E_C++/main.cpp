#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

constexpr int32_t maxn = 1e5, alpha_size = 26;

int32_t g_poss[447][maxn + 1];
int32_t size_to_s_id[maxn + 1];
unordered_set<uint64_t> good_hs[447];
vector<int32_t> sizes;
string fzs;
vector<int32_t> z;

template<uint32_t M>
struct HV {
    using HVM = HV<M>;
    uint32_t val;

    HV(uint32_t val = 0): val(val) {
    }

    HVM operator+(HVM other) const {
        uint32_t res = val + other.val;
        return res >= M ? res - M : res;
    }

    HVM operator-(HVM other) const {
        return val < other.val ? M + val - other.val : val - other.val;
    }

    HVM operator*(HVM other) const {
        if (M == 0) return val * other.val;
        return 1ll * val * other.val % M;
    }
};

template<uint32_t P, uint32_t M>
struct SH {
    using HVM = HV<M>;
    vector<HVM> ps, hashes;

    SH(const string &s): ps(maxn), hashes(s.size() + 1) {
        ps[0] = 1;
        for (int32_t i = 1; i < ps.size(); ++i) ps[i] = ps[i - 1] * P;
        for (int32_t i = 0; i < s.size(); ++i) hashes[i + 1] = hashes[i] + ps[i] * s[i];
    }

    uint32_t substr_hash(int32_t l, int32_t r) {
        return ((hashes[r] - hashes[l]) * ps[ps.size() - r]).val;
    }

    uint32_t get_full_hash(const string &s) {
        HVM res = 0;
        for (int32_t i = 0; i < s.size(); ++i) res = res + ps[i] * s[i];
        return (res * ps[ps.size() - s.size()]).val;
    }
};

int main() {
    // freopen("test.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    string s;
    int32_t n;
    cin >> s >> n;
    for (auto &c: s) c -= 'a';
    vector<string> temp_strings(n);
    sizes.resize(n);
    for (int32_t i = 0; i < n; ++i) {
        cin >> temp_strings[i], sizes[i] = temp_strings[i].size();
        for (auto &c: temp_strings[i]) c -= 'a';
    }
    sort(sizes.begin(), sizes.end());
    sizes.erase(unique(sizes.begin(), sizes.end()), sizes.end());
    for (int32_t i = 0; i < sizes.size(); ++i) size_to_s_id[sizes[i]] = i;
    SH<31, 1000000007> ha(s);
    SH<31, 0> hb(s);
    for (const auto &ts: temp_strings)
        good_hs[size_to_s_id[ts.size()]].insert(((1ull * ha.get_full_hash(ts)) << 32) | hb.get_full_hash(ts));
    for (int32_t s_id = 0; s_id < sizes.size(); ++s_id)
        for (int32_t i = 0; i <= s.size() - sizes[s_id]; ++i)
            if (good_hs[s_id].contains(
                ((1ull * ha.substr_hash(i, i + sizes[s_id])) << 32) | hb.substr_hash(i, i + sizes[s_id])))
                ++g_poss[s_id][i + 1];
    for (auto &gp: g_poss) for (int32_t i = 1; i <= s.size(); ++i) gp[i] += gp[i - 1];
    int32_t q;
    cin >> q;
    for (int32_t i = 0, l, r; i < q; ++i) {
        cin >> l >> r, --l;
        int64_t ans = 0;
        for (int32_t s_id = 0; s_id < sizes.size(); ++s_id) {
            if (sizes[s_id] > r - l) break;
            ans += g_poss[s_id][r - sizes[s_id] + 1] - g_poss[s_id][l];
        }
        cout << ans << " ";
    }
    return 0;
}
