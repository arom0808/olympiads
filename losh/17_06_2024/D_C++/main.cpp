#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Place {
    int32_t x, y;

    bool operator<(const Place &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    void swap(Place &other) {
        std::swap(x, other.x), std::swap(y, other.y);
    }
};

const int32_t maxhw = 1e6;
int32_t h, w, q;
Place positions[maxhw];
vector<vector<int32_t>> table;
Place &zero_pos = positions[0];
set<Place> may_positions;

int32_t max_val(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    int32_t res = -1;
    for (int32_t i = x1; i <= x2; ++i) {
        for (int32_t j = y1; j <= y2; ++j) {
            if (table[i][j] > res) res = table[i][j];
        }
    }
    return res;
}

int32_t get_res() {
    int32_t res = 0;
    if (h == 1) {
        int32_t left_used = 0, right_used = 0;
        for (int32_t i = 0; i < w; ++i) {
            if (i == 0) left_used = right_used = zero_pos.y;
            else {
                if (positions[i].y < left_used) left_used = positions[i].y;
                if (positions[i].y > right_used) right_used = positions[i].y;
            }
            if (right_used - left_used == i) ++res;
        }
        return res;
    } else {
        for (int32_t x1 = 0; x1 < h; ++x1) {
            for (int32_t x2 = x1; x2 < h; ++x2) {
                for (int32_t y1 = 0; y1 < w; ++y1) {
                    for (int32_t y2 = y1; y2 < w; ++y2) {
                        if (max_val(x1, y1, x2, y2) < (x2 - x1 + 1) * (y2 - y1 + 1)) ++res;
                    }
                }
            }
        }
        return res;
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> h >> w >> q;
    table.assign(h, vector<int32_t>(w, 0));
    for (int32_t i = 0; i < h * w; ++i) {
        cin >> positions[i].x >> positions[i].y;
        table[positions[i].x][positions[i].y] = i;
        if ((std::abs(positions[i].x - zero_pos.x) + 1) * (std::abs(positions[i].y - zero_pos.y) + 1) == i + 1)
            may_positions.insert(positions[i]);
    }
    for (int32_t i = 0, a, b; i < q; ++i) {
        cin >> a >> b;
        if ((std::abs(positions[a].x - zero_pos.x) + 1) * (std::abs(positions[a].y - zero_pos.y) + 1) ==
            a + 1)
            may_positions.erase(positions[a]);
        if ((std::abs(positions[b].x - zero_pos.x) + 1) * (std::abs(positions[b].y - zero_pos.y) + 1) ==
            b + 1)
            may_positions.erase(positions[b]);
        table[positions[a].x][positions[a].y] = b;
        table[positions[b].x][positions[b].y] = a;
        positions[a].swap(positions[b]);
        if ((std::abs(positions[a].x - zero_pos.x) + 1) * (std::abs(positions[a].y - zero_pos.y) + 1) ==
            a + 1)
            may_positions.insert(positions[a]);
        if ((std::abs(positions[b].x - zero_pos.x) + 1) * (std::abs(positions[b].y - zero_pos.y) + 1) ==
            b + 1)
            may_positions.insert(positions[b]);
        cout << get_res() << "\n";
    }
    return 0;
}
