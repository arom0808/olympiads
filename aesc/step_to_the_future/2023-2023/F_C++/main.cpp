#include <iostream>
#include <vector>

using namespace std;

int main() {
    uint32_t n, t;
    cin >> n >> t;
    vector<uint32_t> pols(n);
    for (auto &p: pols) cin >> p;
    uint32_t t1 = 0, t2 = 0, p1 = 0, p2 = n - 1;
    while (p1 <= p2) {
        if (t1 < t2) t1 += pols[p1++] + t;
        else t2 += pols[p2--] + t;
    }
    cout << max(t1, t2) - t;
    return 0;
}
