#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int32_t maxn = 1e5, sqrtn = 320;

vector<pair<int32_t, int32_t> > g[maxn];

struct EulEL {
    int32_t vx, id;

    explicit EulEL(int32_t vx, int32_t id = -1): vx(vx), id(id) {
    }
};

vector<EulEL> euler;
int32_t eul_pos[maxn];

void euler_dfs(int32_t u = 0, int32_t p = -1) {
    eul_pos[u] = euler.size();
    euler.emplace_back(-1, -1);
    for (const auto [v,x]: g[u]) {
        if (v == p) continue;
        euler.emplace_back(x, v);
        euler_dfs(v, u);
        euler.emplace_back(x, v);
    }
}

struct Que {
    int32_t l, r, id, ans;
};

namespace SqrtArr {
    int32_t arr[maxn + 1];
    int32_t blocks[maxn / sqrtn + 1];
    bool used_edges[maxn + 1];

    void add_val(int32_t val) {
        if (euler[val].id == -1 || euler[val].vx > maxn) return;
        if (!arr[euler[val].vx]) ++blocks[euler[val].vx / sqrtn];
        arr[euler[val].vx] += -2 * used_edges[euler[val].id] + 1;
        used_edges[euler[val].id] ^= 1;
        if (!arr[euler[val].vx]) --blocks[euler[val].vx / sqrtn];
    }

    int32_t get_mex() {
        int32_t i = 0;
        while (blocks[i] == sqrtn) ++i;
        i *= sqrtn;
        while (arr[i]) ++i;
        return i;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n, q;
    cin >> n >> q;
    for (int32_t i = 1, u, v, x; i < n; ++i) {
        cin >> u >> v >> x, --u, --v;
        g[u].emplace_back(v, x), g[v].emplace_back(u, x);
    }
    euler_dfs();
    vector<Que> ques(q);
    for (int32_t i = 0; i < q; ++i) {
        auto &[a,b,id,ans] = ques[i];
        cin >> a >> b;
        a = eul_pos[a - 1], b = eul_pos[b - 1] + 1;
        if (a > b) swap(a, b);
        id = i;
    }
    sort(ques.begin(), ques.end(), [](const Que a, const Que &b) {
        if (a.l / sqrtn != b.l / sqrtn) return a.l < b.l;
        return a.r < b.r;
    });
    int32_t l = 0, r = 0;
    for (auto &[a,b,id,ans]: ques) {
        while (r < b) SqrtArr::add_val(r++);
        while (l > a) SqrtArr::add_val(--l);
        while (r > b) SqrtArr::add_val(--r);
        while (l < a) SqrtArr::add_val(l++);
        ans = SqrtArr::get_mex();
    }
    vector<int32_t> res(q);
    for (const auto [a,b,id,ans]: ques) res[id] = ans;
    for (const auto el: res) cout << el << "\n";
    return 0;
}
