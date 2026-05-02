#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

const int32_t maxn = 1e5;

namespace st {
    struct Node {
        pair<int32_t, int32_t> max_val_pos{-1, -1};
        int32_t push{0};
    };
    Node tree[maxn * 4];

    void init(int32_t id, int32_t l, int32_t r) {
        if (l >= r) return;
        if (r - l == 1) tree[id].max_val_pos = {0, l};
        else {
            init(id * 2, l, (l + r) / 2);
            init(id * 2 + 1, (l + r) / 2, r);
            tree[id].max_val_pos = std::max(tree[id * 2].max_val_pos, tree[id * 2 + 1].max_val_pos);
        }
    }

    void assign() {
        init(1, 0, maxn);
    }

    void push_changes(int32_t id) {
        if (!tree[id].push) return;
        if (id * 2 + 1 < maxn * 4) {
            tree[id * 2].max_val_pos.first += tree[id].push;
            tree[id * 2].push += tree[id].push;
            tree[id * 2 + 1].max_val_pos.first += tree[id].push;
            tree[id * 2 + 1].push += tree[id].push;
        }
        tree[id].push = 0;
    }

    void _add(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b, int32_t val) {
        if (l >= r || r <= a || b <= l) return;
        push_changes(id);
        if (a <= l && r <= b) {
            tree[id].max_val_pos.first += val, tree[id].push += val;
            return;
        }
        _add(id * 2, l, (l + r) / 2, a, b, val);
        _add(id * 2 + 1, (l + r) / 2, r, a, b, val);
        tree[id].max_val_pos = std::max(tree[id * 2].max_val_pos, tree[id * 2 + 1].max_val_pos);
    }

    pair<int32_t, int32_t> _get_max_val_pos(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || r <= a || b <= l) return {-1, -1};
        push_changes(id);
        if (a <= l && r <= b) return tree[id].max_val_pos;
        return std::max(_get_max_val_pos(id * 2, l, (l + r) / 2, a, b),
                        _get_max_val_pos(id * 2 + 1, (l + r) / 2, r, a, b));
    }

    inline void add(int32_t a, int32_t b, int32_t val) {
        _add(1, 0, maxn, a, b, val);
    }

    inline pair<int32_t, int32_t> get_max_val_pos(int32_t a, int32_t b) {
        return _get_max_val_pos(1, 0, maxn, a, b);
    }
}

struct Rect {
    int32_t x1, y1, x2, y2;
};

Rect rects[maxn];

struct Act {
    int32_t r_id;
    bool type; // true - start, false - finish
    inline int32_t pos() const {
        return type ? rects[r_id].x1 : rects[r_id].x2;
    }

    bool operator<(const Act &other) const {
        if (pos() != other.pos()) return pos() < other.pos();
        return !type && other.type;
    }
};

Act acts[maxn * 2];
int32_t all_xs[maxn * 2], all_ys[maxn * 2];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    st::assign();
    int32_t n;
    cin >> n;
    for (int32_t i = 0; i < n; ++i) {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        acts[i * 2] = {i, false}, acts[i * 2 + 1] = {i, true};
        all_xs[i * 2] = rects[i].x1, all_xs[i * 2 + 1] = ++rects[i].x2;
        all_ys[i * 2] = rects[i].y1, all_ys[i * 2 + 1] = rects[i].y2;
    }
    sort(begin(all_xs), next(begin(all_xs), n * 2));
    sort(begin(all_ys), next(begin(all_ys), n * 2));
    for (int32_t i = 0; i < n; ++i) {
        rects[i].x1 = distance(begin(all_xs), lower_bound(begin(all_xs), next(begin(all_xs), n * 2), rects[i].x1));
        rects[i].x2 = distance(begin(all_xs), lower_bound(begin(all_xs), next(begin(all_xs), n * 2), rects[i].x2));
        rects[i].y1 = distance(begin(all_ys), lower_bound(begin(all_ys), next(begin(all_ys), n * 2), rects[i].y1));
        rects[i].y2 = distance(begin(all_ys), lower_bound(begin(all_ys), next(begin(all_ys), n * 2), rects[i].y2));
    }
    sort(begin(acts), next(begin(acts), n * 2));
    pair<pair<int32_t, int32_t>, int32_t> max_res{{0, 0}, 0};
    for (int32_t i = 0; i < 2 * n; ++i) {
        auto act = acts[i];
        if (act.type) {
            st::add(rects[act.r_id].y1, rects[act.r_id].y2 + 1, 1);
            max_res = std::max(max_res, {st::get_max_val_pos(0, maxn), act.pos()});
        } else st::add(rects[act.r_id].y1, rects[act.r_id].y2 + 1, -1);
    }
    cout << max_res.first.first << "\n";
    cout << all_xs[max_res.second] << " " << all_ys[max_res.first.second] << "\n";
    return 0;
}
