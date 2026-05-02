#include <iostream>
#include <cstdint>

using namespace std;

int main() {
    uint64_t k, a, x, b, y;
    cin >> k >> a >> x >> b >> y;
    cout << std::max((k >= a ? (k - a) * x : 0) + (k >= a + b ? (k - a - b) * y : 0),
                     (k >= b ? (k - b) * y : 0) + (k >= a + b ? (k - a - b) * x : 0));
    return 0;
}
