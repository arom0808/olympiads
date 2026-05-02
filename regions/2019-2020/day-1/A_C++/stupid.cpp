#include <iostream>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    uint64_t n;
    cin >> n;
    if (n == 0) {
        cout << "Yes\n1 1\n";
        return 0;
    }
    for (uint64_t i = 1; i * i < n; ++i) {
        uint64_t xpy = n / i;
        if (xpy * i == n && !((xpy - i) & 1)) {
            uint64_t y = (xpy - i) / 2;
            uint64_t x = i + y;
            cout << "Yes\n" << x << " " << y << "\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}
