#include <iostream>

using namespace std;

int main() {
    uint32_t p, n, m;
    cin >> p >> n >> m;
    p -= n * 5 + m * 10;
    uint32_t tmin = n * 3 + m * 4;
    uint32_t fmin = p / 3 + ((p % 3) > 0);
    cout << max(tmin, fmin);
    return 0;
}