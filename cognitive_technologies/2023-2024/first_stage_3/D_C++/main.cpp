#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Coord {
    int32_t x = 0, y = 0;
};

inline int32_t sq(int32_t a) { return a * a; }

int main() {
    int32_t t;
    cin >> t;
    vector<Coord> coords(6);
    vector<int32_t> square_sides(6), square_diags(3), sq_dists(6);
    for (int32_t _ = 0; _ < t; ++_) {
        for (auto &c: coords) cin >> c.x >> c.y;
        for (int32_t i = 0; i < 6; ++i)
            square_sides[i] = sq(coords[i].x - coords[(i + 1) % 6].x) + sq(coords[i].y - coords[(i + 1) % 6].y);
        int32_t min_side = *min_element(square_sides.begin(), square_sides.end()),
                max_side = *max_element(square_sides.begin(), square_sides.end());
        if (sq(100) * max_side > sq(111) * min_side) {
            cout << "0";
            continue;
        }
        for (int32_t i = 0; i < 3; ++i)
            square_diags[i] = sq(coords[i].x - coords[i + 3].x) + sq(coords[i].y - coords[i + 3].y);
        int32_t min_diag = *min_element(square_diags.begin(), square_diags.end()),
                max_diag = *max_element(square_diags.begin(), square_diags.end());
        if (sq(100) * max_diag > sq(111) * min_diag) {
            cout << "0";
            continue;
        }
        int32_t min_x, max_x, min_y, max_y;
        for (auto c: coords) {
            if (c.x < min_x) min_x = c.x;
            if (c.x > max_x) max_x = c.x;
            if (c.y < min_y) min_y = c.y;
            if (c.y > max_y) max_y = c.y;
        }
        bool found = false;
        for (int32_t x = min_x; x <= max_x; ++x) {
            for (int32_t y = min_y; y <= max_y; ++y) {
                bool isin = true;
                for (int32_t i = 0; i < 6; ++i) {
                    int32_t a = (coords[(i + 1) % 6].x - coords[i].x) * (coords[(i + 2) % 6].y - coords[i].y) -
                                (coords[(i + 1) % 6].y - coords[i].y) * (coords[(i + 2) % 6].x - coords[i].x);
                    int32_t b = (coords[(i + 1) % 6].x - coords[i].x) * (y - coords[i].y) -
                                (coords[(i + 1) % 6].y - coords[i].y) * (x - coords[i].x);
                    if (signbit(a) != signbit(b)) {
                        isin = false;
                        break;
                    }
                }
                if (!isin) continue;
                for (int32_t i = 0; i < 6; ++i) sq_dists[i] = sq(coords[i].x - x) + sq(coords[i].y - y);
                int32_t min_dist = *min_element(sq_dists.begin(), sq_dists.end()),
                        max_dist = *max_element(sq_dists.begin(), sq_dists.end());
                if (sq(100) * max_dist <= sq(111) * min_dist) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        cout << (found ? "1" : "0");
    }
    return 0;
}
