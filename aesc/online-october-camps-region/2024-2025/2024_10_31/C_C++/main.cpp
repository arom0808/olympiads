#pragma GCC optimize("Ofast,O3")

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

constexpr int maxn = 1e5, block_size = 500;

int arr[maxn];
int cnt_by_id[maxn];
int ans[maxn];
list<int> ids_by_cnt[maxn + 1];
list<int>::iterator l_it_by_id[maxn + 1];
list<pair<int, int> > cnts, s_cnts;
list<pair<int, int> >::iterator cnts_its[maxn + 1];
bool where_cnt_it[maxn + 1];

int n, q;

struct Que {
    int l, r, id;
};

void change(int c_id, int pre_cnt, int now_cnt) {
    ids_by_cnt[now_cnt].splice(ids_by_cnt[now_cnt].end(), ids_by_cnt[pre_cnt], l_it_by_id[c_id]);
    l_it_by_id[c_id] = prev(ids_by_cnt[now_cnt].end());
    auto p_it = cnts_its[pre_cnt];
    if (where_cnt_it[now_cnt]) {
        auto nit = now_cnt > pre_cnt ? next(p_it) : p_it;
        cnts.splice(nit, s_cnts, cnts_its[now_cnt]);
        where_cnt_it[now_cnt] = false;
        cnts_its[now_cnt] = prev(nit);
        cnts_its[now_cnt]->second = 1;
    } else ++cnts_its[now_cnt]->second;
    --p_it->second;
    if (!p_it->second) {
        s_cnts.splice(s_cnts.end(), cnts, cnts_its[pre_cnt]);
        cnts_its[pre_cnt] = prev(s_cnts.end());
        where_cnt_it[pre_cnt] = true;
    }
}

void add(int c_id) {
    change(c_id, cnt_by_id[c_id], cnt_by_id[c_id] + 1);
    ++cnt_by_id[c_id];
}

void erase(int c_id) {
    change(c_id, cnt_by_id[c_id], cnt_by_id[c_id] - 1);
    --cnt_by_id[c_id];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    vector<int> svals(begin(arr), next(begin(arr), n));
    sort(svals.begin(), svals.end());
    svals.erase(unique(svals.begin(), svals.end()), svals.end());
    for (int i = 0; i < n; ++i) arr[i] = distance(svals.begin(), lower_bound(svals.begin(), svals.end(), arr[i]));
    cin >> q;
    vector<Que> ques(q);
    for (int i = 0; i < q; ++i) cin >> ques[i].l >> ques[i].r, --ques[i].l, ques[i].id = i;
    sort(ques.begin(), ques.end(), [](const Que &a, const Que &b) {
        int a_block = a.l / block_size, b_block = b.l / block_size;
        if (a_block != b_block) return a_block < b_block;
        if (a_block & 1) return a.r > b.r;
        return a.r < b.r;
    });
    cnts.emplace_back(0, static_cast<int>(svals.size()));
    cnts_its[0] = cnts.begin();
    where_cnt_it[0] = false;
    for (int i = 1; i <= n; ++i) {
        where_cnt_it[i] = true;
        s_cnts.emplace_back(i, 0);
        cnts_its[i] = prev(s_cnts.end());
    }
    for (int i = 0; i < static_cast<int>(svals.size()); ++i) {
        ids_by_cnt[0].push_back(i);
        l_it_by_id[i] = prev(ids_by_cnt[0].end());
    }
    int l = 0, r = 0;
    for (auto [cl,cr, id]: ques) {
        while (l > cl) add(arr[--l]);
        while (r < cr) add(arr[r++]);
        while (l < cl) erase(arr[l++]);
        while (r > cr) erase(arr[--r]);
        ans[id] = *ids_by_cnt[cnts.rbegin()->first].begin();
    }
    for (int i = 0; i < q; ++i) cout << svals[ans[i]] << "\n";
    return 0;
}
