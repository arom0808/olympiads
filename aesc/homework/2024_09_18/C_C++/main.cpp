#include <iostream>
#include <vector>

using namespace std;

int32_t n, k;
vector<int32_t> ans;

void rec(int32_t level = 0, int32_t last_num = 0) {
    if (level == k) {
        for (auto el: ans) cout << el << " ";
        cout << "\n";
        return;
    }
    for (int32_t add_num = last_num + 1; add_num + (k - level - 1) <= n; ++add_num) {
        ans.push_back(add_num);
        rec(level + 1, add_num);
        ans.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> k;
    rec();
    return 0;
}
