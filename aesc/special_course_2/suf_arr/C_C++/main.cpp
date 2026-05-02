#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>

using namespace std;

struct Node {
    array<int32_t, 30> nx;
    int32_t suf, pre; // suf - suflink, pre - longest parent

    Node() {
        nx.fill(-1);
        suf = pre = -1;
    }
};

vector<Node> s;
int32_t root = -1, finish = -1;

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

void init(const string &str) {
    root = finish = 0;
    s.clear(), s.emplace_back();
    for (char c: str) finish = add(finish, c - 'a');
}

vector<bool> visited;
vector<int32_t> topsort;
vector<int64_t> dp;

void gen_topsort(int32_t u = root) {
    if (u == root) topsort.clear(), visited.clear(), visited.resize(s.size(), false);
    visited[u] = true;
    for (auto v: s[u].nx) if (v != -1 && !visited[v]) gen_topsort(v);
    topsort.push_back(u);
    if (u == root) reverse(topsort.begin(), topsort.end());
}

void gen_dp() {
    dp.assign(s.size(), 0);
    dp[root] = 1;
    for (auto u: topsort) for (auto v: s[u].nx) if (v != -1) dp[v] += dp[u];
}

int64_t get_res() {
    return accumulate(dp.begin(), dp.end(), 0ll) - 1;
}

int main() {
    string str;
    cin >> str;
    init(str);
    gen_topsort();
    gen_dp();
    cout << get_res() << "\n";
    return 0;
}
