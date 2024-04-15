#include <iostream>
#include <cmath>

using namespace std;
using ld = long double;
using ll = long long;

inline bool isin(ld r, ld centre_x, ld centre_y, ll x, ll y) {
    return (centre_x - x) * (centre_x - x) + (centre_y - y) * (centre_y - y) <= r * r;
}

int main() {
    ld r, centre_x, centre_y;
    cin >> r >> centre_x >> centre_y;
    ll start_left_x = floor(centre_x), start_right_x = ceil(centre_x);
    if (start_left_x == start_right_x) ++start_right_x;
    ll left_to_add = start_left_x, right_to_add = start_right_x, start_y = static_cast<ll>(centre_y - r) - 3,
            finish_y = static_cast<ll>(centre_y + r) + 3, layer_cnt = 0, res = 0;
    for (ll y = start_y; y <= finish_y; ++y) {
        while (isin(r, centre_x, centre_y, left_to_add, y)) {
            ++layer_cnt;
            --left_to_add;
        }
        while (isin(r, centre_x, centre_y, right_to_add, y)) {
            ++layer_cnt;
            ++right_to_add;
        }
        while (left_to_add < start_left_x && !isin(r, centre_x, centre_y, left_to_add + 1, y)) {
            --layer_cnt;
            ++left_to_add;
        }
        while (right_to_add > start_right_x && !isin(r, centre_x, centre_y, right_to_add - 1, y)) {
            --layer_cnt;
            --right_to_add;
        }
        res += layer_cnt;
    }
    cout << res;
    return 0;
}
