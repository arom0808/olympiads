#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()

using namespace std;

struct DSU {
private:
    int n, m;
    vector<int> par, sizes;
    vector<set<pair<int, int>>> crosses;
    int find(int v) {
        if (par[v] == v) return v;
        return par[v] = find(par[v]);
    }
public:
    DSU() = default;
    DSU(int _n, int _m) {
        n = _n, m = _m;
        par.resize(n * m);
        iota(all(par), 0);
        sizes.assign(n * m, 1);
        crosses.assign(n * m, {});
    }

    int conv(int i, int j) {
        return i * m + j;
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (sizes[u] < sizes[v]) swap(u, v);
        if (crosses[u].size() < crosses[v].size()) crosses[u].swap(crosses[v]);
        sizes[u] += sizes[v]; par[v] = u;
        for (auto el: crosses[v]) crosses[u].insert(el);
    }

    bool not_empty(int v) {
        return !crosses[find(v)].empty();
    }

    void add(int v, pair<int, int> p) {
        crosses[find(v)].insert(p);
    }
    void del(int v, pair<int, int> p) {
        crosses[find(v)].erase(p);
    }
};

const vector<pair<int, int>> paths = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

int n, m, pls;
vector<vector<int>> field;
vector<vector<bool>> used;

DSU d;

bool is_correct(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

void dfs(int i, int j, int num, int& cnt, int& dc) {
    cnt++;
    used[i][j] = true;
    if (field[i][j] == (3 - num) || field[i][j] == -(3 - num)) ++dc;
    for (auto [di, dj]: paths) {
        int i_new = i + di, j_new = j + dj;
        if (!is_correct(i_new, j_new) || used[i_new][j_new] || field[i_new][j_new] == -100 || field[i_new][j_new] == -(3 - num)) continue;
        dfs(i_new, j_new, num, cnt, dc);
    }
}

int count_available(int num, int& dc) {
    used.assign(n, vector<bool>(m, false));
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field[i][j] == num && !used[i][j]) dfs(i, j, num, cnt, dc); 
        }
    }
    return cnt;
}

tuple<int, int, int> score;

pair<int, int> validate(int num, vector<pair<int, int>> q) {
    if (q.size() == 0) {
        int dc = 0;
        int winner = count_available(3 - num, dc);
        int loser = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (field[i][j] == num || field[i][j] == -num) ++loser;
            }
        }
        loser -= dc;
        score = { winner, loser, n * m - winner - loser };
        auto& [f, s, x] = score;
        if (f < s) swap(f, s);
        if (winner == loser) return { -1, 0 };
        return { (winner > loser) ? 3 - num: num, 0 };
    }
    for (auto [i, j]: q) {
        if (!is_correct(i, j)) return { 3 - num, 1 };
        if (field[i][j] != 0 && field[i][j] != 3 - num) {
            return { 3 - num, 1 };
        }
        bool corr = false;
        vector<pair<int, int>> towers_player, towers_opponent, cross_player;
        for (auto [di, dj]: paths) {
            int i_new = i + di, j_new = j + dj;
            if (!is_correct(i_new, j_new)) continue;
            if (field[i_new][j_new] == num) {
                corr = true;
                cross_player.emplace_back(i_new, j_new);
            }
            else if (field[i_new][j_new] == -num) {
                towers_player.emplace_back(i_new, j_new);
                if (d.not_empty(d.conv(i_new, j_new))) {
                    corr = true;
                }
            }
            else if (field[i_new][j_new] == -(3 - num)) {
                towers_opponent.emplace_back(i_new, j_new);
            }
        }
        if (!corr) {
            return { 3 - num, 1 };
        } 
        if (field[i][j] == 0) {
            field[i][j] = num;
            for (auto [it, jt]: towers_player) {
                d.add(d.conv(it, jt), { i, j });
            }
        }
        else {
            field[i][j] = -num;
            for (auto [it, jt]: towers_opponent) {
                d.del(d.conv(it, jt), { i, j });
            }
            for (auto [it, jt]: towers_player) {
                d.unite(d.conv(it, jt), d.conv(i, j));
            }
            for (auto [it, jt]: cross_player) {
                d.add(d.conv(i, j), { it, jt });
            }
        }
    }
    return { 0, -1 };
}

int main() {
    // freopen("log.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    cin >> n >> m >> pls; d = DSU(n, m);
    field.assign(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> field[i][j];
        }
    }
    int id, k;
    while (cin >> id >> k) {
        vector<pair<int, int>> q;
        for (int i = 0; i < k; ++i) {
            int x, y; cin >> x >> y;
            --x, --y;
            q.emplace_back(x, y);
        }
        auto [res, info] = validate(id, q);
        cout << res << ' ' << info;
        if (info == 0) {
            auto [w, l, nt] = score;
            cout << ' ' << w << ' ' << l << ' ' << nt;
        }
        cout << endl;
    }
}
