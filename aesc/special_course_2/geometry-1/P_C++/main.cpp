#include <iostream>

using namespace std;

int main() {
    int64_t ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    auto a = -bx, b = -by, c = ax * bx + ay * by;
    cout << a << " " << b << " " << c;
    return 0;
}