#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

constexpr int maxn = 1e4;

namespace ST {
    struct Node {
        vector<int> els;
    };

    Node tree[maxn * 4];
    int size;

    void _build(int v, int l, int r, const vector<vector<int> > &arr) {
        if (r - l == 1) {
            tree[v].els = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        _build(v * 2, l, mid, arr);
        _build(v * 2 + 1, mid, r, arr);
    }

    int _num_exists(int v, int l, int r, int a, int b, int fn, int tn) {
        if (l >= b || a >= r) return 0;
        if (a <= l && r <= b) {
            auto fit = lower_bound(tree[v].els.begin(), tree[v].els.end(), fn);
            auto sit = upper_bound(tree[v].els.begin(), tree[v].els.end(), tn);
            return sit - fit;
        }
        return _num_exists(v * 2, l, (l + r) / 2, a, b, fn, tn) + _num_exists(v * 2 + 1, (l + r) / 2, r, a, b, fn, tn);
    }

    void build(const vector<vector<int> > &arr) {
        size = arr.size();
        _build(1, 0, size, arr);
    }

    int num_exists(int a, int b, int fn, int tn) {
        return _num_exists(1, 0, size, a, b, fn, tn);
    }
}

vector<pair<int, int> > segs;
int jans[maxn], sans[maxn];


bool isin(int i, int j) {
    return segs[j].first <= segs[i].first && segs[i].second <= segs[j].second;
}

int zipped_val(const vector<int> &fzn, int val) {
    return distance(fzn.begin(), lower_bound(fzn.begin(), fzn.end(), val));
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n;
    cin >> n;
    segs.resize(n);
    vector<int> all_coords;
    all_coords.reserve(2 * n);
    for (auto &[s,e]: segs) cin >> s >> e, all_coords.push_back(s), all_coords.push_back(e);
    sort(all_coords.begin(), all_coords.end());
    all_coords.erase(unique(all_coords.begin(), all_coords.end()), all_coords.end());
    for (auto &[s,e]: segs) s = zipped_val(all_coords, s), e = zipped_val(all_coords, e);
    for (int i = 0; i < n; ++i) cin >> sans[i];
    for (int i = 0; i < n; ++i) cin >> jans[i];
    vector<vector<int> > segs_ends(all_coords.size());
    for (auto [s,e]: segs) segs_ends[s].push_back(e);
    ST::build(segs_ends);
    for (int i = 0; i < n; ++i) {
        if (!isin(i, sans[i] - 1) && ) {
            cout << "WA\n";
            continue;
        }
        auto [ss, se] = segs[i];
        auto [fs, fe] = segs[sans[i] - 1];
        bool better_found = false;
        if (ss - fs > 0) {
            if (ST::num_exists(fs + 1, ss + 1, se, fe) > 1)
                better_found = true;
            better_found = better_found || ST::num_exists(fs + 1, ss + 1, se, fe);
        }
        if (fe - se > 0) {
            if (ST::num_exists(fs, ss + 1, se, fe - 1) > 1)
                better_found = true;
            // better_found = better_found || ST::num_exists(fs, ss + 1, se, fe - 1);
        }
        if (better_found) cout << "WA\n";
        else cout << "OK\n";
    }
    // for (int i = 0; i < n; ++i) {
    // list<int> fathers;
    // for (int j = 0; j < n; ++j) {
    // if (i == j) continue;
    // if (!isin(i, j)) continue;
    // bool ok = true;
    // for (auto k: fathers) if (i != k && j != k && isin(k, j)) ok = false;
    // if (!ok) continue;
    // erase_if(fathers, [i,j](int k) {
    // if (i == j || i == k || j == k) return false;
    // return isin(j, k);
    // });
    // fathers.push_back(j);
    // }
    // if (fathers.empty()) fathers.push_back(-1);
    // if (find(fathers.begin(), fathers.end(), sans[i] - 1) != fathers.end()) cout << "OK\n";
    // else cout << "WA\n";
    // }
    return 0;
}
