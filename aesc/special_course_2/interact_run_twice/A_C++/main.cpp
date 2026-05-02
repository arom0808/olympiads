#include <iostream>
#include <cstdint>

using namespace std;

int32_t ask(int32_t x) {
    cout << x << endl;
    int32_t r;
    cin >> r;
    return r;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    int32_t l = 1, r = n + 1;
    while (r - l != 1) {
        int32_t mid = (l + r) / 2;
        int32_t res = ask(mid);
        if (res == 0) exit(0);
        else if (res == 1) l = mid;
        else r = mid;
    }
    cout << l << "\n";
    return 0;
}
