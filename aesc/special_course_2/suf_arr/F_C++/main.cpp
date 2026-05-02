#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

using namespace std;

const int32_t maxa = 26;

struct Node {
    array<int32_t, maxa> nx{};
    int32_t pre = -1, suf = -1;

    Node() { nx.fill(-1); }
};

vector<Node> s;

int32_t add(int32_t a, int32_t x) {
    int32_t b = s.size();
    s.emplace_back();
    s[b].suf = 0, s[b].pre = a;
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
        s[c].suf = s[b].suf = d;
        for (; a != -1 && s[a].nx[x] == c; a = s[a].suf) s[a].nx[x] = d;
        break;
    }
    return s[s[b].pre].nx[x];
}

int32_t root, last;

void init() {
    root = last = 0;
    s.clear(), s.emplace_back();
}

vector<bool> used;
vector<uint64_t> dp, weight;

uint64_t make_dp(int32_t u = root) {
    if (used[u]) return dp[u];
    used[u] = true;
    for (auto v: s[u].nx) if (v != -1) dp[u] += make_dp(v);
    return dp[u];
}

string res;
uint64_t k;

void dfs(int32_t u = root, uint64_t pre_c = 0) {
    if (pre_c + weight[u] >= k) return;
    pre_c += weight[u];
    for (int32_t i = 0; i < maxa; ++i) {
        if (s[u].nx[i] == -1) continue;
        int32_t v = s[u].nx[i];
        if (k > pre_c + dp[v]) //TODO: check this
            pre_c += dp[v];
        else {
            res += 'a' + i;
            dfs(v, pre_c);
            return;
        }
    }
    res = "No such line.\n";
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str;
    cin >> str >> k;
    init();
    for (auto c: str) last = add(last, c - 'a');
    dp.assign(s.size(), 0), used.assign(s.size(), false);
    for (int32_t a = last; a != root && a != -1; a = s[a].suf) dp[a] = 1;
    make_dp();
    weight = dp;
    used.assign(s.size(), false);
    make_dp();
    weight[root] = 0;
    dfs();
    cout << res << "\n";
    return 0;
}
