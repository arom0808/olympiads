#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    int64_t ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    auto a = by - ay, b = ax - bx, c = ax * ay + ay * bx - ay * ax - ax * by;
    cout << a << " " << b << " " << c;
    return 0;
}