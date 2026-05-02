#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

constexpr int maxn = 2e5 + 10;

vector<int> g[maxn];
int n;
int sz[maxn];

int dfs_sz(int v, int p = -1) {
    // if (used[v]) return 0;
    sz[v] = 1;
    for (auto u: g[v]) if (u != p) sz[v] += dfs_sz(u, v);
    return sz[v];
}

int find_centroid(int v) {
    dfs_sz(v);
    int csz = sz[v] / 2;
    for (int found = 1, cp = -1; found;) {
        found = 0;
        for (auto u: g[v]) {
            if (u == cp || sz[u] <= csz) continue;
            cp = v, v = u, found = 1;
        }
    }
    return v;
}

vector<int> del_vec;
vector<int> quest_vec;
map<pair<int, vector<int> >, bool> cache;
int sz_pf[maxn];
int now_cnt;

void dfs_quest_add(int v, int p) {
    quest_vec.push_back(v);
    for (auto u: g[v]) if (u != p) dfs_quest_add(u, v);
}

void dfs_del_add(int v, int p) {
    del_vec.push_back(v);
    for (auto u: g[v]) if (u != p) dfs_del_add(u, v);
}

void delete_by_vec() {
    now_cnt -= del_vec.size();
    sort(del_vec.begin(), del_vec.end());
    for (int i = 0; i < n; ++i)
        erase_if(g[i], [](int x) { return binary_search(del_vec.begin(), del_vec.end(), x); });
    for (auto v: del_vec) g[v].clear();
}

bool make_question(int x) {
    auto it = cache.find(make_pair(x, quest_vec));
    if (it != cache.end()) return it->second;
    cout << "? " << quest_vec.size() << " " << x + 1;
    for (auto v: quest_vec) cout << " " << v + 1;
    cout << "\n";
    cout.flush();
    int res;
    cin >> res;
    cache.emplace(make_pair(x, quest_vec), res);
    return res;
}

bool checked[maxn];

void solve() {
    cin >> n;
    now_cnt = n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    int v = 0;
    while (true) {
        if (now_cnt == 1) {
            cout << "! " << v + 1 << "\n";
            cout.flush();
            break;
        }
        v = find_centroid(v);
        bool quest_ans;
        if (!checked[v]) {
            checked[v] = true;
            quest_vec = g[v];
            quest_ans = make_question(v);
            if (quest_ans) {
                cout << "! " << v + 1 << "\n";
                cout.flush();
                break;
            }
        }
        dfs_sz(v);
        sz_pf[0] = 0;
        for (int i = 0; i < g[v].size(); ++i) sz_pf[i + 1] = sz_pf[i] + sz[g[v][i]];
        int fpos = 0;
        while (sz_pf[fpos] < sz[v] / 2 && fpos + 1 < g[v].size()) ++fpos;
        if (fpos) {
            quest_vec.clear();
            for (int i = 0; i < fpos; ++i) dfs_quest_add(g[v][i], v);
            quest_ans = make_question(v);
            if (!quest_ans) {
                del_vec.clear();
                for (int i = fpos; i < g[v].size(); ++i) dfs_del_add(g[v][i], v);
                delete_by_vec();
                continue;
            }
        }
        quest_vec.clear();
        quest_vec.push_back(g[v][fpos]);
        quest_ans = make_question(v);
        if (!quest_ans) {
            del_vec.clear();
            for (int i = 0; i < g[v].size(); ++i) if (i != fpos) dfs_del_add(g[v][i], v);
            del_vec.push_back(v);
            v = g[v][fpos];
            delete_by_vec();
            continue;
        }
        del_vec.clear();
        for (int i = 0; i <= fpos; ++i) dfs_del_add(g[v][i], v);
        delete_by_vec();
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // #ifdef LOCAL
    //     freopen("input.txt", "r",stdin);
    //     freopen("output.txt", "w",stdout);
    // #endif
    solve();
    return 0;
}
