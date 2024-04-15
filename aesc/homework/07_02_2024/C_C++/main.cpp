#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    int32_t arr[n];
    for (auto &el: arr) cin >> el;
    int32_t t = arr[n - 1];
    for (uint32_t i = 1; i < n; ++i) arr[n - i] = arr[n - i - 1];
    arr[0] = t;
    for (auto el: arr) cout << el << " ";
    return 0;
}
