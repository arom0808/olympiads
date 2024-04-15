#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    uint32_t n, m;
    cin >> n >> m;
    bool is_n_2 = false;
    for (uint32_t i = 0; i < 1000; ++i) if (n == i * i - 1) is_n_2 = true;
    if (is_n_2 && n % 2 == 0) {
        cout << n / 2 << "\n";
        for (uint32_t i = 0; i < n / 2; ++i) cout << 2 << "\n" << i + 1 << " " << (n - i) << "\n";
        return 0;
    }
    if (n <= 5) {
        cout << n << "\n";
        for (uint32_t i = 0; i < n; ++i) cout << 1 << "\n" << i + 1 << "\n";
        return 0;
    }
    if (n == 6 || n == 8 || n == 10 || n == 12 || n == 16 || n == 18 || n == 22 || n == 24 || n == 26 || n == 28 ||
        n == 30) {
        cout << n / 2 << "\n";
        for (uint32_t i = 0; i < n / 2; ++i) cout << 2 << "\n" << i + 1 << " " << n - i << "\n";
        return 0;
    }
    if (n == 7 || n == 9 || n == 11 || n == 13 || n == 17 || n == 19 || n == 25 || n == 27 || n == 29 || n == 31) {
        cout << n / 2 + 1 << "\n";
        for (uint32_t i = 0; i < n / 2; ++i) cout << 2 << "\n" << i + 1 << " " << n - i - 1 << "\n";
        cout << 1 << "\n" << n << "\n";
        return 0;
    }
    if (n == 14) {
        cout << n / 2 + 1 << "\n";
        cout << 1 << "\n" << 1 << "\n";
        for (uint32_t i = 2; i < 8; ++i) cout << 2 << "\n" << i << " " << 16 - i << "\n";
        cout << 1 << "\n" << 8 << "\n";
    }
    if (n == 15) {
        cout << n / 2 + 1 << "\n";
        cout << 1 << "\n" << 8 << "\n";
        for (uint32_t i = 0; i < n / 2; ++i) cout << 2 << "\n" << i + 1 << " " << n - i << "\n";
    }
    if (n == 20) {
        --n;
        cout << n / 2 + 2 << "\n";
        for (uint32_t i = 0; i < n / 2; ++i) cout << 2 << "\n" << i + 1 << " " << n - i - 1 << "\n";
        cout << 1 << "\n" << n << "\n";
        ++n;
        cout << 1 << "\n" << n << "\n";
        return 0;
    }
    if (n == 21) {
        cout << n / 4 + 1 << "\n";
        for (uint32_t i = 0; i < n / 2; i += 2)
            cout << 4 << "\n" << i + 1 << " " << i + 2 << " " << n - i << " " << n - i - 1 << "\n";
        cout << 1 << "\n" << 11 << "\n";
    }
    if (n == 23) {
        cout << n / 4 + 3 << "\n";
        for (uint32_t i = 0; i < n / 2 - 1; i += 2)
            cout << 4 << "\n" << i + 1 << " " << i + 2 << " " << n - i << " " << n - i - 1 << "\n";
        cout << 1 << "\n" << 11 << "\n";
        cout << 1 << "\n" << 12 << "\n";
        cout << 1 << "\n" << 13 << "\n";
    }
    if (n == 32) {
        --n;
        cout << n / 2 + 2 << "\n";
        for (uint32_t i = 0; i < n / 2; ++i) cout << 2 << "\n" << i + 1 << " " << n - i - 1 << "\n";
        cout << 1 << "\n" << n << "\n";
        ++n;
        cout << 1 << "\n" << n << "\n";
    }
}
