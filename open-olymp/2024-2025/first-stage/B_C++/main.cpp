#include <iostream>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int maxn = 5e5;

struct Que {
    int id, l, r, p;

    bool operator<(const Que &other) const {
        return l > other.l;
    }
};

int n, m, g;

vector<int> specs[maxn];
vector<pair<int, int> > specs_borders[maxn];
pair<int, int> last_spec_used[maxn];
ordered_multiset<int> right_borders[maxn];
int next_left_id[maxn];
Que ques[maxn];
int ans[maxn];

void solve() {
    cin >> n >> m >> g;
    for (int i = 0, k; i < n; ++i) {
        cin >> k;
        specs[i].resize(k);
        specs_borders[i].resize(k, make_pair(-1, n));
        next_left_id[i] = k - 1;
        for (int j = 0; j < k; ++j) cin >> specs[i][j], --specs[i][j];
    }
    for (int i = 0; i < n; ++i) last_spec_used[i] = {-1, -1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < specs[i].size(); ++j) {
            int csp = specs[i][j];
            if (last_spec_used[csp].first != -1) {
                specs_borders[i][j].first = last_spec_used[csp].first;
                specs_borders[last_spec_used[csp].first][last_spec_used[csp].second].second = i;
            }
            last_spec_used[csp] = {i, j};
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < specs[i].size(); ++j)
            right_borders[i].insert(specs_borders[i][j].second);
    for (int i = 0; i < n; ++i) sort(specs_borders[i].begin(), specs_borders[i].end());
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        ques[i].id = i;
        cin >> ques[i].l >> ques[i].r >> ques[i].p, --ques[i].l, --ques[i].p;
    }
    sort(ques, ques + q);
    for (int i = 0; i < q; ++i) {
        int cp = ques[i].p;
        auto &crb = right_borders[cp];
        auto &csp = specs_borders[cp];
        while (next_left_id[cp] >= 0 && ques[i].l <= csp[next_left_id[cp]].first) {
            crb.erase(crb.find_by_order(crb.order_of_key(csp[next_left_id[cp]].second)));
            --next_left_id[cp];
        }
        ans[ques[i].id] = crb.size() - crb.order_of_key(ques[i].r);
    }
    for (int i = 0; i < q; ++i) cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    solve();
    return 0;
}
