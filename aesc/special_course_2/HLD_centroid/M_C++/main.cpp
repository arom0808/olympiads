#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

const int64_t maxn = 5e4, maxc = 2e6;

namespace st {
    struct Node {
        int64_t push = 0;
        pair<int64_t, int64_t> max_pos;
    };

    Node tree[maxc * 4];

    void init(int64_t id, int64_t l, int64_t r) {
        if (l >= r) return;
        if (r - l == 1) tree[id].max_pos.second = l;
        else {
            init(id * 2, l, (l + r) / 2);
            init(id * 2 + 1, (l + r) / 2, r);
            tree[id].max_pos = std::max(tree[id * 2].max_pos, tree[id * 2 + 1].max_pos);
        }
    }

    void assign() {
        init(1, 0, maxc);
    }

    void push_changes(int64_t id, int64_t l, int64_t r) {
        if (r - l <= 1 || tree[id].push == 0) return;
        tree[id * 2].max_pos.first += tree[id].push;
        tree[id * 2 + 1].max_pos.first += tree[id].push;
        tree[id * 2].push += tree[id].push;
        tree[id * 2 + 1].push += tree[id].push;
        tree[id].push = 0;
    }

    void _add(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b, int64_t val) {
        if (l >= r || b <= l || r <= a) return;
        push_changes(id, l, r);
        if (a <= l && r <= b) {
            tree[id].max_pos.first += val;
            tree[id].push += val;
        } else {
            _add(id * 2, l, (l + r) / 2, a, b, val);
            _add(id * 2 + 1, (l + r) / 2, r, a, b, val);
            tree[id].max_pos = std::max(tree[id * 2].max_pos, tree[id * 2 + 1].max_pos);
        }
    }

    pair<int64_t, int64_t> _max_pos(int64_t id, int64_t l, int64_t r, int64_t a, int64_t b) {
        if (l >= r || b <= l || r <= a) return {0, l};
        push_changes(id, l, r);
        if (a <= l && r <= b) return tree[id].max_pos;
        return std::max(_max_pos(id * 2, l, (l + r) / 2, a, b), _max_pos(id * 2 + 1, (l + r) / 2, r, a, b));
    }

    void add(int64_t a, int64_t b, int64_t val) {
        _add(1, 0, maxc, a, b, val);
    }

    pair<int64_t, int64_t> max_pos(int64_t a, int64_t b) {
        return _max_pos(1, 0, maxc, a, b);
    }
}

struct Action {
    int64_t x, y1, y2;
    bool type;

    bool operator<(const Action &other) const {
        if (x != other.x) return x < other.x;
        return type < other.type;
    }
};

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    st::assign();
    int64_t n;
    cin >> n;
    vector<Action> acts(n * 2);
    for (int64_t i = 0, x1, x2, y1, y2; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        acts[i * 2] = {x1, y1, y2, true};
        acts[i * 2 + 1] = {x2 + 1, y1, y2, false};
    }
    sort(acts.begin(), acts.end());
    pair<int64_t, int64_t> best_res;
    int64_t best_x = 0;
    for (auto [x, y1, y2, type]: acts) {
        st::add(y1, y2 + 1, type ? 1 : -1);
        auto tr = st::max_pos(y1, y2 + 1);
        if (tr > best_res) best_res = tr, best_x = x;
    }
    cout << best_res.first << "\n";
    cout << best_x << " " << best_res.second << "\n";
    return 0;
}
