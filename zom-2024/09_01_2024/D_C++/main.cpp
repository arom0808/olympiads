#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int32_t c6 = 1e6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int32_t n, q, k, w;
    cin >> n >> q >> k >> w;
    vector<int32_t> nums(n);
    vector<set<int32_t>> positions(c6 + 1);
    for (int32_t i = 0; i < n; ++i) {
        cin >> nums[i];
        positions[nums[i]].insert(i);
    }
    vector<int32_t> next_k(n, n), next_k_m_1(n, n);

    int32_t s = 0;
    for (int32_t i = 0, t, a, b; i < q; ++i) {
        cin >> t >> a >> b;
        if (t == 1) {

        } else {

        }
    }
    for (auto &req: reqs) if (req.type) cout << req.ans << "\n";
    return 0;
}
