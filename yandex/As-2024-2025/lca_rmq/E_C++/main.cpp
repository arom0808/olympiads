#include <deque>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
using ll = long long;

constexpr int maxn = 1e7;
constexpr ll inf = 2e18l;

template<typename T>
T ceil(T a, T b) {
    return (a + b - 1) / b;
}

struct Rect {
    ll w, h;
};

struct MinStack {
    vector<pair<ll, ll> > st;

    ll min_val() const {
        if (st.empty()) return inf;
        return st.back().second;
    }

    void push(ll val) {
        st.emplace_back(val, std::min(min_val(), val));
    }

    void pop() {
        st.pop_back();
    }

    void erase_n_bottom(int n) {
        if (n >= st.size()) {
            st.clear();
            return;
        }
        for (int i = 0; i < st.size() - n; ++i) {
            st[i] = st[i + n];
            st[i].second = std::min(st[i].first, i ? st[i - 1].second : inf);
        }
        st.resize(st.size() - n);
    }

    ll operator[](int pos) const {
        return st[pos].first;
    }

    bool empty() const { return st.empty(); }

    size_t size() const { return st.size(); }
};

namespace MinDeque {
    MinStack st1, st2;

    size_t size() {
        return st1.size() + st2.size();
    }

    void push_back(ll val) {
        st2.push(val);
    }

    void push_from(ll val) {
        st1.push(val);
    }

    void pop_back() {
        if (st2.empty()) {
            for (int i = ceil<int>(st1.size(), 2) - 1; i >= 0; --i) st2.push(st1[i]);
            st1.erase_n_bottom(ceil<int>(st1.size(), 2));
        }
        st2.pop();
    }

    void pop_front() {
        if (st1.empty()) {
            for (int i = ceil<int>(st2.size(), 2) - 1; i >= 0; --i) st1.push(st2[i]);
            st2.erase_n_bottom(ceil<int>(st2.size(), 2));
        }
        st1.pop();
    }

    ll min_val() {
        return std::min(st1.min_val(), st2.min_val());
    }
}

ll n, m, k;
Rect rects[maxn];
ll w_pf[maxn];
ll dp[maxn + 1];

void solve() {
    cin >> n >> m >> k;
    ll ti, tw, th;
    for (int i = 0; i < k; ++i) {
        cin >> ti >> tw >> th;
        rects[ti - 1].w = tw, rects[ti - 1].h = th;
    }
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    for (int i = 0; i < n; ++i) {
        if (rects[i].w) continue;
        rects[i].w = ((rects[i - 1].w * a + b) % m) + 1;
        rects[i].h = ((rects[i - 1].h * c + d) % m) + 1;
    }
    for (int i = 0; i < n; ++i) w_pf[i + 1] = w_pf[i] + rects[i].w;
    ll l = 0;
    deque<pair<ll, int> > max_st;
    for (int i = 0; i < n; ++i) {
        while (w_pf[i + 1] - w_pf[l] > m) {
            if (!max_st.empty() && max_st.front().second == l) {
                max_st.pop_front();
                if (MinDeque::size()) MinDeque::pop_front();
            }
            ++l;
        }
        while (!max_st.empty() && max_st.back().first <= rects[i].h) {
            max_st.pop_back();
            if (MinDeque::size()) MinDeque::pop_back();
        }
        max_st.emplace_back(rects[i].h, i);
        if (max_st.size() > 1) MinDeque::push_back(dp[max_st[max_st.size() - 2].second + 1] + rects[i].h);
        dp[i + 1] = std::min(MinDeque::min_val(), dp[l] + max_st.front().first);
    }
    cout << dp[n] << "\n";
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
