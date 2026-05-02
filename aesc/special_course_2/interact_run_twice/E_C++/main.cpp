#include <iostream>
#include <cstdint>

using namespace std;

int64_t ask(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
    cout << "? " << x1 + 1 << " " << y1 + 1 << " " << x2 << " " << y2 << endl;
    int64_t res;
    cin >> res;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int64_t n;
    cin >> n;
    int64_t s = ask(0, 0, n, n);
    int64_t l = 0, r = n - 1;
    while (r != l) {
        int64_t m = (l + r) / 2;
        if (ask(0, 0, m + 1, n) < s) l = m + 1;
        else r = m;
    }
    int64_t rb = l;
    l = 0, r = n - 1;
    while (r != l) {
        int64_t m = (l + r) / 2;
        if (ask(0, 0, n, m + 1) < s) l = m + 1;
        else r = m;
    }
    int64_t bb = l;
    int64_t ls = ask(rb, 0, rb + 1, n);
    cout << "! " << rb - s / ls + 2 << " " << bb - ls + 2 << " " << rb + 1 << " " << bb + 1 << endl;
    return 0;
}
