#include <iostream>

using namespace std;

int main() {
    long double x, y;
    cin >> x >> y;
    cout << static_cast<int64_t>((x + 1e-10) / y);
    return 0;
}
