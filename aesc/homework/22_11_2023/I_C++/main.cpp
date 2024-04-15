#include <iostream>

using std::int32_t;
using std::cin;
using std::cout;

int main() {
    int32_t n;
    cin >> n;
    int32_t m = n;
    while (m > 0) {
        cout << n - m << " " << m << "\n";
        m = (m - 1) & n;
    }
    cout << n - m << " " << m;
    return 0;
}