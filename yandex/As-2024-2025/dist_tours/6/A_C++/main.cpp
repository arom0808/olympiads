#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
using ll = long long;

constexpr ll maxn = 1e5 + 2;

struct Seg {
    ll start = 0, len = 0;

    bool operator<(const Seg &rhs) const {
        return start < rhs.start;
    }
};

ll first_m_poss[maxn], sorted_used_m[maxn];
ll n, m;
vector<Seg> orig_segs;
ll min_div_size = 1e18;


// struct SegTrans {
// ll to1 = 0, cnt1 = 0, to2 = 0, cnt2 = 0, to3 = 0, cnt3 = 0;
// };
// map<ll, SegTrans> seg_trans_cache;
//
// map<ll, ll> temp_upd_map;
//
// void upd_trans(ll seg_len) {
//     auto it = seg_trans_cache.find(seg_len);
//     if (it == seg_trans_cache.end()) {
//
//     }
// }

namespace mSTC {
    struct Node {
        map<ll, ll> cnts;
        int l, r;

        void init(ll len) {
            cnts.emplace(len, 1);
            l = -1, r = -1;
        }
    };

    Node tree[maxn * 50];
    int used_nodes_cnt = 0;

    int get_new_node(ll len) {
        tree[used_nodes_cnt].init(len);
        return used_nodes_cnt++;
    }

    void upd_node(int v) {
        auto &cnts = tree[v].cnts;
        while (!cnts.empty() && prev(cnts.end())->first >= min_div_size) {
            ll csz = prev(cnts.end())->first;
            ll s1, s2;
            if (csz & 1) s1 = s2 = csz / 2;
            else s1 = csz / 2 - 1, s2 = csz / 2;
            ll cnt = prev(cnts.end())->second;
            cnts.erase(prev(cnts.end()));
            if (s1) cnts[s1] += cnt;
            if (s2) cnts[s2] += cnt;
        }
    }

    ll _get_ans_for_k(ll v, ll l, ll r, ll k, ll nlen) {
        upd_node(v);
        if (r - l == nlen) return (l + r - 1) / 2;
        ll mid = (l + r - 1) / 2;
        ll lcnt = 0;
        if (mid - l >= nlen) {
            if (tree[v].l == -1) tree[v].l = get_new_node(mid - l);
            upd_node(tree[v].l);
            auto it = tree[tree[v].l].cnts.find(nlen);
            if (it != tree[tree[v].l].cnts.end()) lcnt = it->second;
            if (k < lcnt) return _get_ans_for_k(tree[v].l, l, mid, k, nlen);
        }
        if (r - mid - 1 >= nlen) {
            if (tree[v].r == -1) tree[v].r = get_new_node(r - mid - 1);
            upd_node(tree[v].r);
            return _get_ans_for_k(tree[v].r, mid + 1, r, k - lcnt, nlen);
        }
        return -1;
    }
}

struct mST {
    ll start_pos, len;
    int root;

    void init(ll sp, ll l) {
        start_pos = sp, len = l;
        root = mSTC::get_new_node(len);
    }

    ll get_ans_for_k(ll k, ll nlen) {
        return mSTC::_get_ans_for_k(root, start_pos, start_pos + len, k, nlen);
    }
};

namespace ST {
    struct Node {
        map<ll, ll> cnts;
        mST subtree;
    };

    Node tree[maxn * 4];
    int sz;

    void upd_node(int v) {
        auto &cnts = tree[v].cnts;
        while (!cnts.empty() && prev(cnts.end())->first >= min_div_size) {
            ll csz = prev(cnts.end())->first;
            ll s1, s2;
            if (csz & 1) s1 = s2 = csz / 2;
            else s1 = csz / 2 - 1, s2 = csz / 2;
            ll cnt = prev(cnts.end())->second;
            cnts.erase(prev(cnts.end()));
            if (s1) cnts[s1] += cnt;
            if (s2) cnts[s2] += cnt;
        }
    }

    void _init(int v, int l, int r) {
        if (r - l == 1) {
            tree[v].subtree.init(orig_segs[l].start, orig_segs[l].len);
            tree[v].cnts.emplace(orig_segs[l].len, 1);
            return;
        }
        int mid = (l + r) / 2;
        _init(v * 2, l, mid);
        _init(v * 2 + 1, mid, r);
        tree[v].cnts = tree[v * 2].cnts;
        for (auto [len, cnt]: tree[v * 2 + 1].cnts) tree[v].cnts[len] += cnt;
    }

    void init() {
        sz = orig_segs.size();
        _init(1, 0, sz);
    }

    ll cnt_for_next_step() {
        upd_node(1);
        return prev(tree[1].cnts.end())->second;
    }

    ll next_len() {
        upd_node(1);
        return prev(tree[1].cnts.end())->first;
    }

    ll _get_ans_for_k(int v, int l, int r, ll k, ll nlen) {
        upd_node(v);
        if (r - l == 1) return tree[v].subtree.get_ans_for_k(k, nlen);
        int mid = (l + r) / 2;
        upd_node(v * 2);
        auto lit = tree[v * 2].cnts.find(nlen);
        ll lcnt = 0;
        if (lit != tree[v * 2].cnts.end()) lcnt = lit->second;
        if (k < lcnt) return _get_ans_for_k(v * 2, l, mid, k, nlen);
        return _get_ans_for_k(v * 2 + 1, mid, r, k - lcnt, nlen);
    }

    ll get_ans_for_k(ll k) {
        return _get_ans_for_k(1, 0, sz, k, next_len());
    }
}

void solve() {
    int q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; ++i) cin >> first_m_poss[i], sorted_used_m[i] = first_m_poss[i];
    sort(sorted_used_m, sorted_used_m + m);
    if (sorted_used_m[0] != 1) orig_segs.emplace_back(1, sorted_used_m[0] - 1);
    for (int i = 1; i < m; ++i)
        orig_segs.emplace_back(sorted_used_m[i - 1] + 1, sorted_used_m[i] - sorted_used_m[i - 1] - 1);
    if (sorted_used_m[m - 1] != n) orig_segs.emplace_back(sorted_used_m[m - 1] + 1, n - sorted_used_m[m - 1]);
    ST::init();
    ll pk = 0;
    for (int i = 0; i < q; ++i) {
        ll k;
        cin >> k, --k;
        if (k < m) cout << first_m_poss[k] << "\n";
        else {
            if (pk == 0) pk = m;
            while (k - pk >= ST::cnt_for_next_step()) {
                pk += ST::cnt_for_next_step();
                min_div_size = ST::next_len();
            }
            cout << ST::get_ans_for_k(k - pk) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r", stdin);
#endif
    solve();
    return 0;
}