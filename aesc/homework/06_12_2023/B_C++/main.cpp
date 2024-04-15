#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    uint32_t n;
    long double x0, a, b = 0;
    cin >> n >> x0;
    for (uint32_t i = 0; i <= n; ++i) {
        cin >> a;
        b = a + b * x0;
    }
    cout << fixed << setprecision(3) << b;
    return 0;
}
