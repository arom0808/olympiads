#include <iostream>
#include <vector>

using namespace std;

bool is_ok(const vector<__int128> &ts, __int128 A, __int128 B, __int128 cycles_cnt) {
    if (A > B) {
        __int128 a_need_cnt = 0;
        for (auto t: ts) {
            if (t - cycles_cnt * A >= 0) return false;
            if (t - cycles_cnt * B < 0) continue;
            a_need_cnt += (t - cycles_cnt * B + 1) / (A - B) + (((t - cycles_cnt * B + 1) % (A - B)) != 0);
        }
        return a_need_cnt <= cycles_cnt;
    } else if (A < B) {
        __int128 max_a = 0;
        for (auto t: ts) {
            if (t - cycles_cnt * B >= 0) return false;
            if (t - cycles_cnt * A < 0) {
                max_a += cycles_cnt;
                continue;
            }
            max_a += cycles_cnt - ((t - cycles_cnt * A + 1) / (B - A) + (((t - cycles_cnt * A + 1) % (B - A)) != 0));
        }
        return max_a >= cycles_cnt;
    } else {
        for (auto t: ts) if (t - cycles_cnt * B >= 0) return false;
        return true;
    }
}

int main() {
    int64_t n, A, B;
    cin >> n >> A >> B;
    vector<__int128> ts(n);
    int64_t temp;
    for (auto &t: ts) {
        cin >> temp;
        t = temp;
    }
    __int128 l = 0, r = 1e10;
    while (l != r) {
        __int128 m = (l + r) / 2;
        if (is_ok(ts, A, B, m)) r = m;
        else l = m + 1;
    }
    temp = l;
    cout << temp;
    return 0;
}
