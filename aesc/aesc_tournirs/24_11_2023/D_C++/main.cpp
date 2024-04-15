#include <iostream>
#include <vector>
#include <deque>
#include <numeric>
#include <limits>

using namespace std;


const uint32_t inf = numeric_limits<uint32_t>::max();

struct RawWay {
    uint32_t u, v;
    bool crush;
};

struct Way {
    uint32_t to;
    bool crush;

    bool operator<(const Way &other) const { return to < other.to; }
};

struct Vert {
    uint32_t val;
};

bool dfs1(const vector<vector<Way>> &ways, const vector<Vert> &verts, uint32_t &res, uint32_t v, uint32_t p = inf) {
    bool r = verts[v].val > 0;
    for (auto way: ways[v]) {
        if (way.to == p) continue;
        bool tr = dfs1(ways, verts, res, way.to, v);
        if (tr && way.crush) ++res;
        r |= tr;
    }
    return r;
}

int main() {
    uint32_t g, n, m;
    cin >> g >> n >> m;
    vector<RawWay> raw_ways(n - 1);
    for (auto &[u, v, crush]: raw_ways) {
        cin >> u >> v;
        --u;
        --v;
    }
    string temp_str;
    cin >> temp_str;
    for (uint32_t i = 0; i + 1 < n; ++i) raw_ways[i].crush = temp_str[i] == '1';
    vector<vector<Way>> ways(n);
    for (const auto &[u, v, crush]: raw_ways) {
        ways[u].emplace_back(v, crush);
        ways[v].emplace_back(u, crush);
    }
    vector<Vert> verts(n);
    for (auto &[val]: verts) cin >> val;
    for (uint32_t _ = 0, rt, p, w; _ < m; ++_) {
        cin >> rt;
        if (rt == 1) {
            cin >> p;
            raw_ways[p - 1].crush = !raw_ways[p - 1].crush;
            ways[raw_ways[p - 1].v][raw_ways[p - 1].u].crush = raw_ways[p - 1].crush;
            ways[raw_ways[p - 1].u][raw_ways[p - 1].v].crush = raw_ways[p - 1].crush;
        } else if (rt == 2) {
            cin >> p >> w;
            deque<pair<uint32_t, uint32_t>> que;
            que.emplace_back(p - 1, inf);
            while (!que.empty()) {
                auto [v, par] = que.front();
                que.pop_front();
                verts[v].val += w;
                for (auto way: ways[v]) {
                    if (way.to == par || way.crush) continue;
                    que.emplace_back(way.to, v);
                }
            }
        } else if (rt == 3) {
            cin >> p;
            deque<pair<uint32_t, uint32_t>> que;
            que.emplace_back(p - 1, inf);
            while (!que.empty()) {
                auto [v, par] = que.front();
                que.pop_front();
                if (v != p - 1) {
                    verts[p - 1].val += verts[v].val;
                    verts[v].val = 0;
                }
                for (auto way: ways[v]) {
                    if (way.to == par || way.crush) continue;
                    que.emplace_back(way.to, v);
                }
            }
        } else if (rt == 4) {
            cin >> p;
            cout << verts[p - 1].val << "\n";
        } else if (rt == 5) {
            cin >> p;
            deque<pair<uint32_t, uint32_t>> que;
            que.emplace_back(p - 1, inf);
            uint32_t res = 0;
            while (!que.empty()) {
                auto [v, par] = que.front();
                que.pop_front();
                res += verts[v].val;
                for (auto way: ways[v]) {
                    if (way.to == par || way.crush) continue;
                    que.emplace_back(way.to, v);
                }
            }
            cout << res << "\n";
        } else if (rt == 6) {
            cin >> p;
            deque<pair<uint32_t, uint32_t>> que;
            que.emplace_back(p - 1, inf);
            while (!que.empty()) {
                auto [v, par] = que.front();
                que.pop_front();
                verts[v].val = 0;
                for (auto way: ways[v]) {
                    if (way.to == par || way.crush) continue;
                    que.emplace_back(way.to, v);
                }
            }
        } else {
            uint32_t res = 0;
            for (uint32_t i = 0; i < n; ++i) {
                if (verts[i].val > 0) {
                    dfs1(ways, verts, res, i);
                    break;
                }
            }
            cout << res << "\n";
        }
    }

    return 0;
}

//class DSU {
//private:
//    vector<uint32_t> link, _size;
//
//    uint32_t find(uint32_t v) {
//        while (link[v] != v) v = link[v];
//        return v;
//    }
//
//public:
//    void unite(uint32_t a, uint32_t b) {
//        a = link[a] = find(a);
//        b = link[b] = find(b);
//        if (a == b) return;
//        if (_size[a] < _size[b]) {
//            link[a] = b;
//            _size[b] += _size[a];
//        } else {
//            link[b] = a;
//            _size[a] += _size[b];
//        }
//    }
//
//    uint32_t get(uint32_t v) { return link[v] = find(v); }
//
//    [[nodiscard]] uint32_t size(uint32_t v) { return _size[link[v] = find(v)]; }
//
//    explicit DSU(uint32_t els_count) : link(els_count), _size(els_count, 1) {
//        iota(link.begin(), link.end(), 0);
//    }
//};