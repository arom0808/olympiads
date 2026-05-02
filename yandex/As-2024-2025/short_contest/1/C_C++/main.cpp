#include <iostream>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int64_t n;
    cin >> n;
    multiset<int64_t> bottom, top;
    int64_t all_sum = 0;
    for (int64_t i = 0, a, b; i < n; ++i) {
        cin >> a >> b;
        all_sum += std::max(a, b);
        if (a > b) top.insert(std::abs(a - b));
        else bottom.insert(std::abs(a - b));
    }
    while (!top.empty()) {
        bottom.insert(*top.rbegin());
        top.erase(prev(top.end()));
        if (!top.empty()) top.erase(prev(top.end()));
    }
    cout << all_sum - (*bottom.begin()) << "\n";
    return 0;
}
