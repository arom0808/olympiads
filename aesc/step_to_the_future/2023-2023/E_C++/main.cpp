#include <iostream>

using namespace std;

int main() {
    uint32_t n, res = 0;
    cin >> n;
    for (uint32_t i = 0, t; i < n; ++i) {
        cin >> t;
        while (t) {
            if ((t % 12) % 3 == 0) ++res;
            t /= 12;
        }
    }
    cout << res;
    return 0;
}
