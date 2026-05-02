#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n;
    cin >> n;
    vector<pair<int64_t, int64_t> > arr(n);
    for (auto &[a,b]: arr) cin >> a >> b;
    sort(arr.begin(), arr.end());
    int64_t sum = 0;
    multiset<int64_t> vs;
    for (const auto [a,b]: arr) {
        sum += b;
        vs.insert(sum - a);
    }
    sum = 0;
    int64_t best_res = 0;
    for (int32_t start_i = 0; start_i < n; ++start_i) {
        if (auto cr = arr[start_i].first + (*vs.rbegin()) - sum; cr > best_res) best_res = cr;
        sum += arr[start_i].second;
        vs.erase(vs.find(sum - arr[start_i].first));
    }
    cout << best_res << "\n";
    return 0;
}
