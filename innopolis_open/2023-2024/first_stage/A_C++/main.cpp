#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n, q, x;
    cin >> n >> q >> x;
    x *= 100;
    vector<pair<int64_t, int64_t>> types(q, pair<int64_t, int64_t>(0, 0));
    for (int64_t i = 0; i < q; ++i) types[i].first = i;
    for (int64_t i = 0, t, m, k; i < n; ++i) {
        cin >> t >> m >> k;
        types[t - 1].second += m * k;
    }
    sort(types.begin(), types.end(), [](const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b) {
        return a.second > b.second;
    });
    for (int64_t i = 0; i < q; ++i) {
        x -= types[i].second;
        if (x <= 0) {
            cout << i + 1;
            return 0;
        }
    }
    cout << "-1";
    return 0;
}
