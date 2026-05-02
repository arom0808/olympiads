#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct MinStack {
    vector<pair<int, int> > st;

    int min_value() {
        return st.back().second;
    }

    void push(int x) {
        if (st.empty()) st.emplace_back(x, x);
        else st.emplace_back(x, std::min(st.back().second, x));
    }

    int pop() {
        int ans = st.back().first;
        st.pop_back();
        return ans;
    }

    int size() const {
        return st.size();
    }

    bool empty() const {
        return st.empty();
    }
};

struct MinDeque {
    MinStack front, back;

    static void pour(MinStack &from, MinStack &to) {
        int cnt = (from.size() + 1) / 2;
        for (int i = cnt - 1; i >= 0; --i) to.push(from.st[i].first);
        for (int i = 0; i + cnt < from.size(); ++i) from.st[i] = from.st[i + cnt];
        from.st.resize(from.size() - cnt);
        from.st[0].second = from.st[0].first;
        for (int i = 1; i < from.size(); ++i) from.st[i].second = std::min(from.st[i - 1].second, from.st[i].first);
    }

    void push_front(int x) {
        front.push(x);
    }

    void push_back(int x) {
        back.push(x);
    }

    void pop_front() {
        if (front.empty()) pour(back, front);
        front.pop();
    }

    void pop_back() {
        if (back.empty()) pour(front, back);
        back.pop();
    }

    int min_value() {
        if (front.empty()) return back.min_value();
        if (back.empty()) return front.min_value();
        return std::min(front.min_value(), back.min_value());
    }

    bool empty() const {
        return front.size() + back.size() == 0;
    }
};

constexpr int maxn = 5e5 + 10, maxlogn = 21;
int n;
vector<int> g[maxn];
int vals[maxn];
MinDeque vals_by_levels[maxlogn];
vector<int> vals_seq;
ll w = 0;

void dfs(int v, int p = -1) {
    if (p != -1) {
        ll min_cost = 1e18;
        for (int level = 0; !vals_by_levels[level].empty(); ++level) {
            int a = vals_by_levels[level].min_value(), b = vals[v];
            min_cost = std::min(min_cost, 1ll * (level + 1) * a + b);
        }
        w += min_cost;
    }
    for (int i = 1, level = 0; i - 1 < vals_seq.size(); i <<= 1, ++level) {
        int pos = vals_seq.size() - (i - 1) - 1;
        vals_by_levels[level].pop_back();
        vals_by_levels[level + 1].push_front(vals_seq[pos]);
    }
    vals_seq.push_back(vals[v]);
    vals_by_levels[0].push_back(vals[v]);
    for (auto u: g[v]) if (u != p) dfs(u, v);
    vals_seq.pop_back();
    vals_by_levels[0].pop_back();
    for (int i = 1, level = 0; i - 1 < vals_seq.size(); i <<= 1, ++level) {
        int pos = vals_seq.size() - (i - 1) - 1;
        vals_by_levels[level + 1].pop_front();
        vals_by_levels[level].push_back(vals_seq[pos]);
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> vals[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    int start_v = min_element(vals, vals + n) - vals;
    dfs(start_v);
    cout << w << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
