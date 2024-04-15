#include <iostream>

using uint32_t = unsigned int;
using std::cin;
using std::cout;

int main() {
    uint32_t n, a, b;
    cin >> n >> a >> b;
    cout << (a == b ? n : n - 1) << "\n" << (a + b < n ? n - a - b : 0);
    return 0;
}
