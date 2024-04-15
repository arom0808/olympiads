#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    int32_t x, y;
    cin >> x >> y;
    auto fi = atan2(y, x);
    if (fi < 0) fi += 6.28318530717958647692;
    cout << fixed << setprecision(10) << fi;
    return 0;
}
