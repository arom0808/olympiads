#include <iostream>

using namespace std;

int main() {
    int32_t x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    int32_t s = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    cout << static_cast<double>(s) / 2;
    return 0;
}
