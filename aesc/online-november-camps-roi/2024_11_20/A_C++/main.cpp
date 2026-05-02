#include <iostream>
#include <vector>
#include <map>

using namespace std;
using ll = int64_t;

constexpr int maxn = 2e5 + 2;

namespace SNM {
    struct Node {
        int p, sz, cnt_interest;
    };

    Node tree[maxn * 10];
    vector<pair<int, int> > hist;
    int size;

    void init(int _size, int cnt_interest) {
        size = _size;
        tree[0] = {0, 1, 0};
        for (int i = 1; i <= cnt_interest; ++i) tree[i] = {i, 1, 1};
        for (int i = cnt_interest + 1; i < size; ++i) tree[i] = {i, 1, 0};
    }

    int get_root(int v) {
        while (tree[v].p != v) v = tree[v].p;
        return v;
    }

    void merge(int a, int b) {
        a = get_root(a), b = get_root(b);
        if (tree[a].sz < tree[b].sz && a) swap(a, b);
        hist.emplace_back(a, b);
        if (a == b) return;
        tree[b].p = a;
        tree[a].sz += tree[b].sz;
        tree[a].cnt_interest += tree[b].cnt_interest;
    }

    void revert() {
        if (hist.empty()) return;
        auto [a,b] = hist.back();
        hist.pop_back();
        if (a == b) return;
        tree[a].cnt_interest -= tree[b].cnt_interest;
        tree[a].sz -= tree[b].sz;
        tree[b].p = b;
    }
}

struct Req {
    int type, v, u;
    
};


int n, m, q;
Req reqs[maxn];
map<pair<int, int>, int> per_ids;
map<int, int> row_pers[maxn], col_pers[maxn];
pair<int, int> pers[maxn];
int cur_type[maxn];
int pers_cnt = 0;

int get_vert_id(int per_id, int dir) {
    return 1 + per_id * 4 + dir;
}

int inv_dir(int dir) {
    if (dir + 2 >= 4) return dir - 2;
    return dir + 2;
}

int get_nearest_by_dir(int pid, int dir) {
    if (dir == 0) {
        auto it = col_pers[pers[pid].second].upper_bound(pers[pid].first);
        if (it == col_pers[pers[pid].second].end()) return -1;
        return it->second;
    }
    if (dir == 2) {
        auto it = col_pers[pers[pid].second].lower_bound(pers[pid].first);
        if (it == col_pers[pers[pid].second].begin()) return -1;
        return prev(it)->second;
    }
    if (dir == 1) {
        auto it = row_pers[pers[pid].first].lower_bound(pers[pid].second);
        if (it == row_pers[pers[pid].first].begin()) return -1;
        return prev(it)->second;
    }
    auto it = row_pers[pers[pid].first].upper_bound(pers[pid].second);
    if (it == row_pers[pers[pid].first].end()) return -1;
    return it->second;
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 0; i < q; ++i) {
        cin >> reqs[i].a >> reqs[i].x >> reqs[i].y, --reqs[i].x, --reqs[i].y;
        if (per_ids.emplace({reqs[i].x, reqs[i].y}, pers_cnt).second) {
            pers[pers_cnt] = {reqs[i].x, reqs[i].y};
            row_pers[reqs[i].x].emplace(reqs[i].y, pers_cnt);
            col_pers[reqs[i].y].emplace(reqs[i].x, pers_cnt);
            ++pers_cnt;
        }
    }
    SNM::init(1 + m + per_ids.size() * 4, m);
    for (int pid = 0; pid < pers_cnt; ++pid) {
        SNM::merge(get_vert_id(pid, 0), get_vert_id(pid, 2));
        SNM::merge(get_vert_id(pid, 1), get_vert_id(pid, 3));
        for (int dir = 0; dir < 4; ++dir) {
            int nid = get_nearest_by_dir(pid, dir);
            int cmv = get_vert_id(pid, dir);
            if (nid == -1) {
                if (dir == 0) SNM::merge(cmv, 1 + pers[pid].second);
                else if (dir == 2) SNM::merge(cmv, 0);
                continue;
            }
            SNM::merge(cmv, get_vert_id(nid, inv_dir(dir)));
        }
    }
    for (int i = 0; i < q; ++i) {
        auto [a,x,y] = reqs[i];
        int pid = per_ids[{x, y}];
    }
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
