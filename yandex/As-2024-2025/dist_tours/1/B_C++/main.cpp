#include <iostream>
#include <numeric>


using namespace std;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t a, b;
    cin >> a >> b;
    if (a == 1 && b == 1) return 0;
    int32_t temp_gcd = std::gcd(a, b);
    a /= temp_gcd, b /= temp_gcd;
    while (true) {
        int32_t agcd = std::gcd(a - 1, b), bgcd = std::gcd(a, b - 1);
        int32_t ax = (a - 1) / agcd, ay = b / agcd, bx = a / bgcd, by = (b - 1) / bgcd;
        if (a % 2 == 0) cout << "A\n", a = ax, b = ay;
        else cout << "B\n", a = bx, b = by;
        cout.flush();
        if (a == 1 && b == 1) return 0;
        agcd = std::gcd(a - 1, b), bgcd = std::gcd(a, b - 1);
        ax = (a - 1) / agcd, ay = b / agcd, bx = a / bgcd, by = (b - 1) / bgcd;
        char c;
        cin >> c;
        if (c == 'A') a = ax, b = ay;
        else a = bx, b = by;
        if (a == 1 && b == 1) return 0;
    }
    return 0;
}
