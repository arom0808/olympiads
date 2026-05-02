#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


constexpr int mod1 = 1e9 + 7, mod2 = 0;
constexpr int p = 101;
constexpr int maxn = 2e5, asz = 94, inf = 1e9;

template<uint32_t M>
struct HV {
    uint32_t val = 0;

    HV() = default;

    HV(uint32_t v) : val(v) {
        if (M) val %= M;
    }

    bool operator==(HV rhs) {
        return val == rhs.val;
    }

    HV operator*(HV rhs) {
        if (!M) return 1ull * val * rhs.val;
        return 1ull * val * rhs.val % M;
    }

    HV operator+(HV rhs) {
        if (val + rhs.val >= M) return val + rhs.val - M;
        return val + rhs.val;
    }

    HV operator-(HV rhs) {
        if (val < rhs.val) return val + M - rhs.val;
        return val - rhs.val;
    }
};


struct pHV {
    HV<mod1> v1;
    HV<mod2> v2;

    pHV() = default;

    pHV(HV<mod1> a, HV<mod2> b): v1(a), v2(b) {
    }

    pHV(uint32_t val) : v1(val), v2(val) {
    }

    pHV operator*(const pHV &rhs) {
        return {v1 * rhs.v1, v2 * rhs.v2};
    }

    pHV operator+(const pHV &rhs) {
        return {v1 + rhs.v1, v2 + rhs.v2};
    }

    pHV operator-(const pHV &rhs) {
        return {v1 - rhs.v1, v2 - rhs.v2};
    }

    bool operator==(const pHV &rhs) {
        return v1 == rhs.v1 && v2 == rhs.v2;
    }
};

pHV pps[maxn + 2];
pHV hashpf[asz][maxn + 1];
vector<int> poss_by_c[asz];
int cpp_by_c[asz];
vector<int> ans;

char t_transform[asz];
char next_tu = 0;

pHV hash_substr(char c, int from, int to) {
    return (hashpf[c][to] - hashpf[c][from]) * pps[maxn + 1 - to];
}

void solve() {
    pps[0] = 1;
    for (int i = 1; i <= maxn + 1; ++i) pps[i] = pps[i - 1] * p;
    string s1, s2;
    std::getline(cin, s1);
    for (auto &c: s1) c -= 33;
    for (int i = 0; i < s1.size(); ++i) {
        for (int j = 0; j < asz; ++j) {
            if (s1[i] == j) hashpf[j][i + 1] = hashpf[j][i] + pps[i];
            else hashpf[j][i + 1] = hashpf[j][i];
        }
    }
    for (int i = 0; i < s1.size(); ++i) poss_by_c[s1[i]].push_back(i);
    for (int i = 0; i < asz; ++i) poss_by_c[i].push_back(inf);

    std::getline(cin, s2);
    for (auto &c: s2) c -= 33;
    for (int i = 0; i < asz; ++i) t_transform[i] = -1;
    for (char &c: s2) {
        if (t_transform[c] == -1) t_transform[c] = next_tu++;
        c = t_transform[c];
    }
    pHV s2h;
    for (int i = 0; i < s2.size(); ++i) s2h = s2h + pps[i] * s2[i];
    s2h = s2h * pps[maxn + 1 - s2.size()];

    pair<int, int> tarr[asz];
    for (int spos = 0; spos + s2.size() <= s1.size(); ++spos) {
        for (int i = 0; i < asz; ++i) tarr[i] = {poss_by_c[i][cpp_by_c[i]], i};
        sort(tarr, tarr + asz);
        pHV ch;
        for (int i = 0; i < asz; ++i) ch = ch + hash_substr(tarr[i].second, spos, spos + s2.size()) * i;
        if (ch == s2h) ans.push_back(spos);
        ++cpp_by_c[s1[spos]];
    }
    cout << ans.size() << "\n";
    for (auto v: ans) cout << v + 1 << " ";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
