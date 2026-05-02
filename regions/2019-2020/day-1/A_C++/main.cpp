#include <iostream>
#include <cstdint>

using namespace std;

pair<uint64_t, uint64_t> solve_xmpy(uint64_t xmy, uint64_t xpy) {
    uint64_t y = (xpy - xmy) / 2;
    return {xmy + y, y};
}

int main() {
    ios::sync_with_stdio(false);
    uint64_t n;
    cin >> n;
    if (n == 0) {
        cout << "Yes\n1 1\n";
    } else if (n & 1 && n > 1) {
        auto [x,y] = solve_xmpy(1, n);
        cout << "Yes\n" << x << " " << y << "\n";
    } else if (n % 4 == 0 && n > 4) {
        auto [x,y] = solve_xmpy(2, n / 2);
        cout << "Yes\n" << x << " " << y << "\n";
    } else { cout << "No\n"; }
    return 0;
}
