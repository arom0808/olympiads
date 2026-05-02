#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

using namespace std;

const int32_t maxm = 10;

struct Node {
    array<int32_t, maxm> nx{};
    int32_t suf = -1, pre = -1;
    int32_t in_c = -1;

    Node() { nx.fill(-1); }
};

vector<Node> s;

int32_t add(int32_t a, int32_t x) {
    int32_t b = s.size();
    s.emplace_back();
    s[b].suf = 0, s[b].pre = a, s[b].in_c = x;
    for (; a != -1; a = s[a].suf) {
        if (s[a].nx[x] == -1) {
            s[a].nx[x] = b;
            continue;
        }
        int32_t c = s[a].nx[x];
        if (s[c].pre == a) {
            s[b].suf = c;
            break;
        }
        int32_t d = s.size();
        s.emplace_back();
        s[d].suf = s[c].suf;
        s[d].nx = s[c].nx;
        s[d].pre = a;
        s[d].in_c = x;
        s[c].suf = s[b].suf = d;
        for (; a != -1 && s[a].nx[x] == c; a = s[a].suf) s[a].nx[x] = d;
        break;
    }
//    s[s[s[b].pre].nx[x]].term = 1;
    return s[s[b].pre].nx[x];
}

int32_t root, last;

void init() {
    root = last = 0;
    s.clear(), s.emplace_back();
}

int32_t n, m;
vector<bool> used1;
vector<uint64_t> dp1, dp2;
//vector<int32_t> topsort;

uint64_t make_dp1(int32_t u = root) {
    if (used1[u]) return dp1[u];
    used1[u] = true;
    for (auto v: s[u].nx) if (v != -1) dp1[u] += make_dp1(v);
    return dp1[u];
}

uint64_t make_dp2(int32_t u) {
    if (dp2[u] != -1) return dp2[u];
    dp2[u] = 0;
    if (s[u].pre != -1) dp2[u] = make_dp2(s[u].pre) + 1;
    return dp2[u];
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    init();
    for (int32_t i = 0, c; i < n; ++i) cin >> c, last = add(last, c - 1);
    dp1.assign(s.size(), 0), used1.assign(s.size(), false), dp2.assign(s.size(), -1);
//    for (int32_t i = 0; i < s.size(); ++i) dp1[i] = s[i].term;
    for (int32_t a = last; a != -1 && a != root; a = s[a].suf) dp1[a] = 1;
    make_dp1();
    for (int32_t i = 0; i < s.size(); ++i) make_dp2(i);
    uint64_t mid = 0, mres = 0;
    for (int32_t i = 0; i < s.size(); ++i) if (dp1[i] * dp2[i] > mres) mres = dp1[i] * dp2[i], mid = i;
    vector<int32_t> res;
    for (int32_t a = mid; s[a].in_c != -1; a = s[a].pre) res.push_back(s[a].in_c);
    cout << mres << "\n" << res.size() << "\n";
    for (int32_t i = res.size() - 1; i >= 0; --i) cout << res[i] + 1 << " ";
    return 0;
}
