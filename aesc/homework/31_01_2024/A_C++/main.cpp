#include <iostream>

using namespace std;

const long double eps = 1e-10;

int main() {
    long double x, y, z, a, b, c, q;
    uint32_t n;
    cin >> x >> y >> z >> n;
    for (uint32_t i = 0; i < n; ++i) {
        cin >> a >> b >> c >> q;
        x -= a * q, y -= b * q, z -= c * q;
    }
    cout << (x <= eps && y <= eps && z <= eps ? 1 : 0);
    return 0;
}
