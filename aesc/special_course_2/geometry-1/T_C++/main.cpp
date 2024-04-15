#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    long double a1, b1, c1, a2, b2, c2;
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
    auto x0 = -(c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
    auto y0 = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    cout << fixed << setprecision(10) << x0 << " " << y0;
    return 0;
}
