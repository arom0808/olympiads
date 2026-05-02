#include <iostream>
#include <vector>

using namespace std;
const int32_t maxn = 35;
int32_t n, ans = 0;
int32_t cur_set[maxn];

bool check_set() {
    for (int32_t i = 0; i < n; ++i) {
        if (!cur_set[i]) continue;
        for (int32_t j = i; j < n; ++j) if (cur_set[j] && cur_set[(i + j) % n]) return false;
    }
    return true;
}

void rec(int32_t num) {
    if (num == n) {
        ++ans;
        return;
    }
    rec(num + 1);
    cur_set[num] = true;
    if (check_set()) rec(num + 1);
    cur_set[num] = false;
}

int main() {
    cin >> n;
    rec(0);
    cout << ans << "\n";
    return 0;
}
