#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
public:
    struct Node {
        Node *l = nullptr, *r = nullptr;
        int64_t cnt_non_zero = 0, sum = 0, mod = 0;
    };

    Node root;


};

struct PrUg {
    bool type;
    int64_t x, y0, y1;

    bool operator<(const PrUg &other) const {
        return x < other.x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t k, n;
    cin >> k >> n;
    int64_t x = 0, y = 0;
    vector<PrUg> prugs;
    prugs.reserve(n * 2 + 2);
    prugs.emplace_back(false, 0, 0, k), prugs.emplace_back(true, k, 0, k);
    char temp_c;
    for (int32_t i = 0, a; i < n; ++i) {
        cin >> temp_c >> a;
        if (temp_c == 'N') prugs.emplace_back(false, x, y, y + a + k), prugs.emplace_back(true, x + k, y, y + a + k);
        else if (temp_c == 'S')
            prugs.emplace_back(false, x, y - a, y + k), prugs.emplace_back(true, x + k, y - a, y + k);
        else if (temp_c == 'W') prugs.emplace_back(false, x - a, y, y + k), prugs.emplace_back(true, x + k, y, y + k);
        else prugs.emplace_back(false, x, y, y + k), prugs.emplace_back(true, x + a + k, y, y + k);
    }
    sort(prugs.begin(), prugs.end());
    return 0;
}
