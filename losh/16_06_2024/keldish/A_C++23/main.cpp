#include <iostream>
#include <cstdint>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int64_t n, a, b;
    cin >> n >> a >> b;
    int64_t k = b + 1 - a;
    if (k < 0) k = 0;
    if (k > b) k = b;
    if (k > n) k = n;
    if (k == 0)
        cout << n * a << "\n";
    else if (k == 1)
        cout << (n - 1) * a + b << "\n";
    else
        cout << (n - k) * a + (b + b - k + 1) * k / 2 << "\n";
    return 0;
}
