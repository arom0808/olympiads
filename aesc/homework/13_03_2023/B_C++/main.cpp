#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    uint64_t maxn = 0, el;
    for (uint32_t i = 0; i < n; ++i) {
        cin >> el;
        if (el > maxn + 1) break;
        maxn += el;
    }
    cout << maxn + 1;
    return 0;
}
