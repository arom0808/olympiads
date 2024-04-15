#include <iostream>
#include <vector>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    vector<uint32_t> mountains(n);
    for (auto &m: mountains) {
        cin >> m;
        --m;
    }
    vector<uint32_t> counts(n, 0);
    uint32_t unique_cnt = 0;
    for (uint32_t i = 0; i < 3; ++i) {
        if (counts[mountains[i]] == 1) --unique_cnt;
        ++counts[mountains[i]];
        if (counts[mountains[i]] == 1) ++unique_cnt;
    }
    uint32_t res = 0;
    if (unique_cnt == 3) ++res;
    bool dir = true;
    for (uint32_t from = 0, to = from + 2;;) {
        if (dir) {
            while (to + 1 < n) {
                ++to;
                if (counts[mountains[to]] == 1) --unique_cnt;
                ++counts[mountains[to]];
                if (counts[mountains[to]] == 1) ++unique_cnt;
                if (counts[mountains[from]] == 1 && counts[mountains[to]] == 1) res += unique_cnt - 2;
            }
        } else {
            while (to - 1 >= from + 2) {
                if (counts[mountains[to]] == 1) --unique_cnt;
                --counts[mountains[to]];
                if (counts[mountains[to]] == 1) ++unique_cnt;
                --to;
                if (counts[mountains[from]] == 1 && counts[mountains[to]] == 1) res += unique_cnt - 2;
            }
        }
        dir = !dir;
        if (counts[mountains[from]] == 1) --unique_cnt;
        --counts[mountains[from]];
        if (counts[mountains[from]] == 1) ++unique_cnt;
        ++from;
        if (from + 2 >= n) break;
        if (to + 1 < n) {
            ++to;
            if (counts[mountains[to]] == 1) --unique_cnt;
            ++counts[mountains[to]];
            if (counts[mountains[to]] == 1) ++unique_cnt;
        }
        if (counts[mountains[from]] == 1 && counts[mountains[to]] == 1) res += unique_cnt - 2;
    }
    cout << res;
    return 0;
}
