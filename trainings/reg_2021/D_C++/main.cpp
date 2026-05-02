#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int32_t maxn = 1e5;
int32_t n;
int32_t const_d = -1;
pair<int32_t, int32_t> segs[maxn];
int32_t ans[maxn], zs[maxn];
vector<int32_t> temp_seg;
vector<int32_t> g[maxn * 2];

bool process_const_d_seg(int32_t seg_size) {
    for (int32_t i = 0, j = 1; j < temp_seg.size(); ++i, ++j) {
        if (const_d == -1) const_d = temp_seg[j] - temp_seg[i];
        else if (const_d != temp_seg[j] - temp_seg[i]) return false;
    }
    return true;
}

bool check_for_euler() {
    
}

bool try_d(int32_t d) {
    for (auto &row: g) row.clear();
    for (int32_t i = 0; i < n; ++i) {
        if (segs[i].first > d) zs[i * 2] = -1;
        else zs[i * 2] = d - segs[i].first;
        if (segs[i].second > d) zs[i * 2 + 1] = -2;
        else zs[i * 2 + 1] = segs[i].second;
    }
    sort(begin(zs), next(begin(zs), 2 * n));
    for (int32_t i = 0; i < n; ++i) {
        int32_t sp = (segs[i].first > d) ? -1 : d - segs[i].first, fp = (segs[i].second > d) ? -2 : segs[i].second;
        g[distance(begin(zs), lower_bound(begin(zs), next(begin(zs), 2 * n), sp))]
                .push_back(distance(begin(zs), lower_bound(begin(zs), next(begin(zs), 2 * n), sp)));
    }

}

bool sol() {
    cin >> n;
    for (int32_t i = 0, m, s; i < n; ++i) {
        cin >> m >> s;
        temp_seg.resize(m);
        for (auto &el: temp_seg) cin >> el;
        if (m > 1 && !process_const_d_seg(s)) return false;
        segs[i].first = temp_seg.front(), segs[i].second = s - temp_seg.back();
    }
    vector<int32_t> ds;
    if (const_d != -1) ds.push_back(const_d);
    else if (n == 1) ds.push_back(1);
    else {
        sort(begin(segs), next(begin(segs), n));
        int32_t l1 = segs[0].first, l2 = segs[1].first;
        sort(begin(segs), next(begin(segs), n), [](const pair<int32_t, int32_t> &a, const pair<int32_t, int32_t> &b) {
            return a.second > b.second;
        });
        int32_t r1 = segs[0].second, r2 = segs[1].second;
        ds = {l1 + r1, l1 + r2, l2 + r1, l2 + r2};
    }
    for (auto d: ds) {

    }
}


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    if (sol()) {

    } else cout << "No\n";
    return 0;
}
