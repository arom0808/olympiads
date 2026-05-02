#include <iostream>

using namespace std;
using ll = int64_t;

constexpr int maxn = 1e7;
constexpr ll inf = 1e18;



namespace MinStack {
    pair<ll, ll> st[maxn];
    int size = 0;

    ll min_val() {
        if (!size) return inf;
        return st[size - 1].second;
    }

    void push(ll val) {
        st[size++] = {val, std::min(val, min_val())};
    }

    ll pop() {
        if (!size) return inf;
        return st[--size].first;
    }
}

namespace SNM {
    struct Node {
        ll max_ov, min_dv;
        int size;
        Node *p = nullptr;

        void init(ll val) {
            max_ov = val;
            min_dv = inf;
            size = 1;
            p = this;
        }
    };

    Node tree[maxn];

    void init(int size) {
        for (int i = 0; i < size; ++i) tree[i].init();
    }
}

void solve() {
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
