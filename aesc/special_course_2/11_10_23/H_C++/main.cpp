#include <iostream>
#include <map>
#include <cstdint>
#include <array>

using namespace std;
struct Elem {
    map<int32_t, int32_t> points; //y, cnt
    int32_t max_value = -1;
    int32_t left = 0, right = 0;
};
const int32_t my_size = 1e9 + 2;
array<Elem, 6000000> elems;
int32_t root_id = 0;
int32_t next_elem_id = 1;

void _add(int32_t el_id, int32_t l, int32_t r, int32_t x, int32_t y) {
    if (x < l || x >= r || l >= r) return;
    auto &el = elems[el_id];
    if (y > el.max_value) el.max_value = y;
    if (r - l == 1) {
        auto it = el.points.find(y);
        if (it != el.points.end()) ++it->second;
        else el.points.emplace(y, 1);
        return;
    }
    if (x < (r + l) / 2 && l < (r + l) / 2) {
        if (!el.left) el.left = next_elem_id++;
        _add(el.left, l, (r + l) / 2, x, y);
    }
    if (x >= (r + l) / 2 && (r + l) / 2 < r) {
        if (!el.right) el.right = next_elem_id++;
        _add(el.right, (r + l) / 2, r, x, y);
    }
}

void _remove(int32_t el_id, int32_t l, int32_t r, int32_t x, int32_t y) {
    if (x < l || x >= r || l >= r) return;
    auto &el = elems[el_id];
    if (r - l == 1) {
        auto it = el.points.find(y);
        if (it != el.points.end() && (--it->second) == 0) el.points.erase(it);
        if (!el.points.empty()) el.max_value = el.points.rbegin()->first;
        else el.max_value = -1;
    } else {
        if (x < (r + l) / 2 && l < (r + l) / 2 && el.left) _remove(el.left, l, (r + l) / 2, x, y);
        if (x >= (r + l) / 2 && (r + l) / 2 < r && el.right) _remove(el.right, (r + l) / 2, r, x, y);
        el.max_value = max(el.left ? elems[el.left].max_value : -1, el.right ? elems[el.right].max_value : -1);
    }
}

pair<int32_t, int32_t> _find(int32_t el_id, int32_t l, int32_t r, int32_t x, int32_t y) {
    if (x + 1 >= r || l >= r) return {-1, -1};
    auto &el = elems[el_id];
    if (el.max_value <= y) return {-1, -1};
    if (r - l == 1) return {l, el.points.upper_bound(y)->first};
    if (x + 1 < (l + r) / 2 && l < (l + r) / 2 && el.left) {
        auto r1 = _find(el.left, l, (l + r) / 2, x, y);
        if (r1.first >= 0) return r1;
    }
    if (el.right) return _find(el.right, (l + r) / 2, r, x, y);
    return {-1, -1};
}

inline void add(int32_t x, int32_t y) {
    _add(root_id, 0, my_size, x, y);
}

inline void remove(int32_t x, int32_t y) {
    _remove(root_id, 0, my_size, x, y);
}

inline pair<int32_t, int32_t> find(int32_t x, int32_t y) {
    return _find(root_id, 0, my_size, x, y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, x, y;
    string temp;
    cin >> n;
    for (int32_t i = 0; i < n; ++i) {
        cin >> temp >> x >> y;
        if (temp == "add") add(x, y);
        else if (temp == "remove") remove(x, y);
        else {
            auto res = find(x, y);
            if (res.first < 0) cout << "-1\n";
            else cout << res.first << " " << res.second << "\n";
        };
    }
    return 0;
}
