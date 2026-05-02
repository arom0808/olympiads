#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using ll = long long;

map<ll, vector<pair<ll, ll> > > f_cache;

void merge_fs(const vector<pair<ll, ll> > &a, const vector<pair<ll, ll> > &b, vector<pair<ll, ll> > &c) {
    c.reserve(a.size() + b.size() + 1);
    int i1 = 0, i2 = 0;
    for (; i1 < a.size(); ++i1) {
        while (i2 < b.size() && b[i2].first >= a[i1].first) c.push_back(b[i2++]);
        if (!c.empty() && c.back().first == a[i1].first) c.back().second += a[i1].second;
        else c.push_back(a[i1]);
    }
    for (; i2 < b.size(); ++i2) c.push_back(b[i2]);
    c.shrink_to_fit();
}

const vector<pair<ll, ll> > &f(ll len) {
    if (f_cache.contains(len)) return f_cache[len];
    auto &res_vec = f_cache[len];
    if (len == 0) return res_vec;
    if (len == 1) {
        res_vec.emplace_back(1, 1);
        return res_vec;
    }
    res_vec.emplace_back(len, 1);
    merge_fs(f((len >> 1) - 1 + (len & 1)), f(len >> 1), res_vec);
    return res_vec;
}

ll get_cnt_in_len(ll len, ll cnt_len) {
    const auto &cv = f(len);
    if (cv.empty()) return 0;
    int l = -1, r = cv.size() - 1;
    while (r - l != 1) {
        int mid = (l + r) >> 1;
        if (cv[mid].first > cnt_len) l = mid;
        else r = mid;
    }
    if (cv[r].first == cnt_len) return cv[r].second;
    return 0;
}

constexpr ll maxm = 1e5 + 5;

struct Seg {
    ll start, end;
};

Seg raw_segs[maxm];
int segs_cnt = 0;
ll all_length[maxm * 90];
int all_length_cnt = 0;
int sic_by_len[maxm * 90];
int sic_by_len_starts[maxm * 90];
int sic_by_len_cur_starts[maxm * 90];
ll sic_by_len_pf[maxm * 90];
int sic_by_len_pf_starts[maxm * 90];
int sic_by_len_pf_cur_starts[maxm * 90];
ll gsegs_cnt[maxm * 90];
ll gsegs_cnt_pf[maxm * 90];
ll gsegs_cnt_pf_sz = 0;
ll start_hpos[maxm];

ll zip_length(ll len) {
    int l = -1, r = all_length_cnt - 1;
    while (r - l != 1) {
        int mid = (l + r) >> 1;
        if (all_length[mid] > len) l = mid;
        else r = mid;
    }
    return r;
}

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;
    ll pre_human = 0;
    for (ll i = 0; i < m; ++i) {
        cin >> start_hpos[i];
        if (start_hpos[i] - pre_human > 1) raw_segs[segs_cnt++] = Seg(pre_human + 1, start_hpos[i]);
        pre_human = start_hpos[i];
    }
    if (pre_human != n) raw_segs[segs_cnt++] = Seg(pre_human + 1, n + 1);
    for (ll i = 0; i < segs_cnt; ++i)
        for (const auto [l,c]: f(raw_segs[i].end - raw_segs[i].start))
            all_length[all_length_cnt++] = l;
    sort(all_length, all_length + all_length_cnt);
    all_length_cnt = unique(all_length, all_length + all_length_cnt) - all_length;
    reverse(all_length, all_length + all_length_cnt);
    // sic_by_len.resize(all_length_cnt);
    // sic_by_len_pf.resize(all_length_cnt);
    for (int i = 0; i < segs_cnt; ++i)
        for (const auto [l,c]: f(raw_segs[i].end - raw_segs[i].start))
            ++sic_by_len_starts[zip_length(l)];
    for (int i = 0; i < segs_cnt; ++i) sic_by_len_pf_starts[i] = sic_by_len_starts[i] + 1;
    for (int i = 1, pre_sum = 0; i <= all_length_cnt + 1; ++i) {
        int pv = sic_by_len_starts[i - 1];
        sic_by_len_starts[i - 1] = pre_sum;
        pre_sum += pv;
    }
    for (int i = 1, pre_sum = 0; i <= all_length_cnt + 1; ++i) {
        int pv = sic_by_len_pf_starts[i - 1];
        sic_by_len_pf_starts[i - 1] = pre_sum;
        pre_sum += pv;
    }
    for (int i = 0; i < all_length_cnt; ++i) sic_by_len_cur_starts[i] = sic_by_len_starts[i];
    for (int i = 0; i < all_length_cnt; ++i) {
        sic_by_len_pf[sic_by_len_pf_starts[i]] = 0;
        sic_by_len_pf_cur_starts[i] = sic_by_len_pf_starts[i] + 1;
    }
    for (int i = 0; i < segs_cnt; ++i) {
        for (const auto [l,c]: f(raw_segs[i].end - raw_segs[i].start)) {
            ll lid = zip_length(l);
            sic_by_len[sic_by_len_cur_starts[lid]++] = i;
            gsegs_cnt[lid] += c;
            // if (sic_by_len_pf[lid].empty()) sic_by_len_pf[lid].push_back(0);
            sic_by_len_pf[sic_by_len_pf_cur_starts[lid]] = sic_by_len_pf[sic_by_len_pf_cur_starts[lid] - 1] + c;
            ++sic_by_len_pf_cur_starts[lid];
        }
    }
    gsegs_cnt_pf_sz = all_length_cnt + 1;
    gsegs_cnt_pf[0] = 0;
    for (int i = 0; i < all_length_cnt; ++i) gsegs_cnt_pf[i + 1] = gsegs_cnt_pf[i] + gsegs_cnt[i];
    for (ll _ = 0, hid; _ < q; ++_) {
        cin >> hid;
        if (hid <= m) {
            cout << start_hpos[hid - 1] << "\n";
            continue;
        }
        hid -= m;
        ll lid = lower_bound(gsegs_cnt_pf, gsegs_cnt_pf + gsegs_cnt_pf_sz, hid) - gsegs_cnt_pf;
        --lid;
        hid -= gsegs_cnt_pf[lid];
        ll sid = lower_bound(sic_by_len_pf + sic_by_len_pf_starts[lid], sic_by_len_pf + sic_by_len_pf_starts[lid + 1], hid)
                 - (sic_by_len_pf + sic_by_len_pf_starts[lid]);
        --sid;
        hid -= sic_by_len_pf[sic_by_len_pf_starts[lid] + sid];
        --hid;
        sid = sic_by_len[sic_by_len_starts[lid] + sid];
        ll l = raw_segs[sid].start, r = raw_segs[sid].end;
        while (r - l != all_length[lid]) {
            ll mid = (r + l - 1) / 2;
            ll left_cnt = get_cnt_in_len(mid - l, all_length[lid]);
            if (hid < left_cnt) r = mid;
            else {
                l = mid + 1;
                hid -= left_cnt;
            }
        }
        ll mid = (r + l - 1) / 2;
        cout << mid << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
