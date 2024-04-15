#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    long double x0, y0, a, b, c;
    cin >> x0 >> y0 >> a >> b >> c;
    cout << fixed << setprecision(10) << abs(a * x0 + b * y0 + c) / sqrt(a * a + b * b);
    return 0;
}
