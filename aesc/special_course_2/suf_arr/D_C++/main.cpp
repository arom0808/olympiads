#include <iostream>
#include <array>
#include <vector>
#include <cstdint>

using namespace std;

const int32_t alpha_size = 26;

struct Node {
    array<int32_t, alpha_size> nx{};
    int32_t suf = -1, pre = -1;

    Node() { nx.fill(-1); }
};

vector<Node> s;
int32_t root, last;

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
        s[d].pre = a;
        s[d].nx = s[c].nx;
        s[c].suf = s[b].suf = d;
        for (; a != -1 && s[a].nx[x] == c; a = s[a].suf) s[a].nx[x] = d;
        break;
    }
    return s[s[b].pre].nx[x];
}

void init() {
    root = last = 0;
    s.clear(), s.emplace_back();
}

vector<uint64_t> sz;

uint64_t dfs1(int32_t u = root) {
    if (sz[u] != 0) return sz[u];
    sz[u] = 1;
    for (int32_t v: s[u].nx) if (v != -1) sz[u] += dfs1(v);
    return sz[u];
}

uint64_t k;
string res;

void dfs2(int32_t u = root, uint64_t pre_c = 0) {
    if (pre_c + 1 == k) return;
    pre_c += 1;
    for (int32_t i = 0; i < alpha_size; ++i) {
        if (s[u].nx[i] == -1) continue;
        auto v = s[u].nx[i];
        if (k > pre_c + sz[v]) pre_c += sz[v];
        else {
            res += 'a' + i;
            dfs2(v, pre_c);
            return;
        }
    }
    for (int32_t i = alpha_size - 1; i >= 0; --i) {
        if (s[u].nx[i] == -1) continue;
        res += 'a' + i;
        dfs2(s[u].nx[i], 0);
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str;
    cin >> str >> k, ++k;
    init();
    for (auto c: str) last = add(last, c - 'a');
    sz.assign(s.size(), 0);
    dfs1();
    dfs2();
    cout << res << "\n";
    return 0;
}
