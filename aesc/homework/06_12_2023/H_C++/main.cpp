#include <iostream>

using namespace std;

int main() {
    int32_t n, res = 0;
    cin >> n;
    for (int32_t ten = 0; ten <= n; ten += 10)
        for (int32_t five = 0; five <= n - ten; five += 5)
            res += (n - ten - five) / 2 + 1;
    cout << res;
    return 0;
}
