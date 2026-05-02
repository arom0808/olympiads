#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;


const int32_t maxn = 5e5;

namespace st {
    bool deleted[maxn];

    struct Node {
        vector<pair<int32_t, int32_t>> data;

        void add(int32_t x, int32_t q_id) {
            data.emplace_back(q_id, x);
        }

        pair<int32_t, int32_t> get_last() {
            while (!data.empty() && deleted[data.back().first]) data.pop_back();
            if (!data.empty()) return data.back();
            return {-1, -1};
        }
    };

    int32_t que_cnt = 0, size;
    Node nodes[maxn * 4];

    void assign(int32_t _size) {
        size = _size;
    }

    void _add(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b, int32_t x, int32_t q_id) {
        if (l >= r || r <= a || b <= l) return;
        if (a <= l && r <= b) {
            nodes[id].add(x, q_id);
        } else {
            _add(id * 2, l, (l + r) / 2, a, b, x, q_id);
            _add(id * 2 + 1, (l + r) / 2, r, a, b, x, q_id);
        }
    }

    int32_t _get(int32_t id, int32_t l, int32_t r, int32_t pos, int32_t best_id, int32_t best_val) {
        if (l >= r || r <= pos || pos < l) return -1;
        auto t_v = nodes[id].get_last();
        if (t_v.first > best_id) best_id = t_v.first, best_val = t_v.second;
        if (r - l == 1) {
            return best_val;
        } else {
            if (pos < (l + r) / 2) return _get(id * 2, l, (l + r) / 2, pos, best_id, best_val);
            return _get(id * 2 + 1, (l + r) / 2, r, pos, best_id, best_val);
        }
    }

    inline void add(int32_t a, int32_t b, int32_t x) {
        _add(1, 0, size, a, b, x, que_cnt++);
    }

    inline void del(int32_t q_id) {
        deleted[q_id] = true;
    }

    inline int32_t get(int32_t pos) {
        return _get(1, 0, size, pos, -1, -1);
    }
};

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m;
    cin >> n >> m;
    st::assign(n);
    char c;
    int32_t l, r, x, q_id;
    for (int32_t i = 0; i < m; ++i) {
        cin >> c;
        if (c == 'A') {
            cin >> l >> r >> x, --l;
            st::add(l, r, x);
        } else if (c == 'G') {
            cin >> x, --x;
            cout << st::get(x) << "\n";
        } else {
            cin >> q_id, --q_id;
            st::del(q_id);
        }
    }
    return 0;
}
