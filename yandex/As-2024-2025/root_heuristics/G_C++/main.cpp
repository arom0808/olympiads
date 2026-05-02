#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int32_t inf = 1e9;

int32_t n, m;
map<int32_t, int32_t> el_cnt;
map<int32_t, vector<pair<int32_t, bool> > > cnt_el;
map<int32_t, vector<pair<int32_t, int32_t> > > banned;

void ban(const int32_t x, const bool unban = false) {
    int32_t pre_size = inf;
    vector<pair<int32_t, bool> >::iterator it;
    vector<pair<int32_t, bool> > *vec = nullptr;
    for (auto ban_y: banned[x]) {
        if (ban_y.first != pre_size) {
            pre_size = ban_y.first;
            vec = &cnt_el[ban_y.first];
            if (vec->front().first == ban_y.second) (it = vec->begin())->second = !unban;
            else it = vec->end();
        } else {
            if (it != vec->end() && next(it) != vec->end() && next(it)->first == ban_y.second)
                (it = next(it))->second = !unban;
            else it = vec->end();
        }
    }
}

void sol() {
    cin >> n >> m;
    el_cnt.clear(), cnt_el.clear(), banned.clear();
    for (int32_t i = 0, a; i < n; ++i) {
        cin >> a;
        if (auto [it,inserted] = el_cnt.emplace(a, 1); !inserted) ++it->second;
    }
    for (auto [el,cnt]: el_cnt) {
        if (auto it = cnt_el.find(cnt); it == cnt_el.end())
            cnt_el.emplace(
                cnt, vector<pair<int32_t, bool> >{{el, false}});
        else it->second.emplace_back(el, false);
    }
    for (auto &[cnt, els]: cnt_el) reverse(els.begin(), els.end());
    for (auto [x,cnt_x]: el_cnt) banned.emplace(x, vector<pair<int32_t, int32_t> >{{cnt_x, x}});
    for (int32_t i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        banned[x].emplace_back(el_cnt[y], y), banned[y].emplace_back(el_cnt[x], x);
    }
    for (auto &[x, ban_x]: banned) {
        sort(ban_x.rbegin(), ban_x.rend());
        ban_x.erase(unique(ban_x.begin(), ban_x.end()), ban_x.end());
    }
    int64_t best_ans = 0;
    for (const auto [x,cnt_x]: el_cnt) {
        ban(x);
        for (const auto &[cnt_y, ys]: cnt_el) {
            int32_t by = -1;
            for (const auto [y,ban_y]: ys) {
                if (ban_y) continue;
                by = y;
                break;
            }
            if (by != -1) best_ans = std::max<int64_t>(best_ans, 1ll * (x + by) * (cnt_x + cnt_y));
        }
        ban(x, true);
    }
    cout << best_ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t t;
    cin >> t;
    while (t--) sol();
    return 0;
}
