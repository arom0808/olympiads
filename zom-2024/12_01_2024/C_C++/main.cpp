#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Way {
    int32_t to, t, cond;
};

struct Vert {
    list<Way> ways;
    int64_t dc = 0, ds = 0, gc = 0, gs = 0;
};

void dfs1(vector<Vert> &verts, int64_t &ans, int32_t v, int32_t p = -1) {
    int64_t dc = 0, gc = 0;
    for (const auto &way: verts[v].ways) {
        if (way.to == p) continue;
        dfs1(verts, ans, way.to, v);
        if (way.cond) {
            verts[v].gc += verts[way.to].gc + verts[way.to].dc + 1;
            verts[v].gs += verts[way.to].gs + way.t * (verts[way.to].gc + verts[way.to].dc + 1);
            gc += verts[way.to].dc + verts[way.to].gc + 1;
        } else {
            verts[v].dc += verts[way.to].dc + 1;
            verts[v].ds += verts[way.to].ds + way.t * (verts[way.to].dc + 1);
            verts[v].gc += verts[way.to].gc;
            verts[v].gs += verts[way.to].gs;
            dc += verts[way.to].dc + 1, gc += verts[way.to].gc;
        }
    }
    for (const auto &way: verts[v].ways) {
        if (way.cond) gc -= verts[way.to].dc + verts[way.to].gc + 1;
        else dc -= verts[way.to].dc + 1, gc -= verts[way.to].gc;
        if (way.cond)
            ans += verts[way.to].dc * dc + (verts[way.to].gc + 1) * dc + verts[way.to].dc * gc +
                   (verts[way.to].gc + 1) * gc;
        else ans += verts[way.to].gc * dc + verts[way.to].dc * gc + verts[way.to].gc * gc;
        if (way.cond) gc += verts[way.to].dc + verts[way.to].gc + 1;
        else dc += verts[way.to].dc + 1, gc += verts[way.to].gc;
    }
}

int main() {
    int32_t n;
    cin >> n;
    vector<Vert> verts(n);
    for (uint32_t i = 0, a, b, c, d; i + 1 < n; ++i) {
        cin >> a >> b >> c >> d;
        verts[a - 1].ways.emplace_back(b - 1, c, d);
        verts[b - 1].ways.emplace_back(a - 1, c, d);
    }
    int64_t ans = 0;
    dfs1(verts, ans, 0);
    cout << ans;
    return 0;
}
